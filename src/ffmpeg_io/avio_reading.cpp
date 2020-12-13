//
// Created by andrew on 2020/12/13.
//

#include <iostream>

extern "C" {
#include <libavformat/avformat.h>
#include <libavutil/log.h>
#include <libavcodec/avcodec.h>
#include <libavformat/avio.h>
#include <libavutil/file.h>
#include <cstdio>
}

using namespace std;

// 为mmap buffer定义一个结构体指针用户管理数据
struct buffer_data {
    uint8_t *ptr;
    size_t size; // size left in the buffer
};

static int ReadPacket(void *pOpaque, uint8_t *pBuff, int bufferSize) {

    auto *bd = (struct buffer_data *) pOpaque;
//    #define FFMIN(a,b) ((a) > (b) ? (b) : (a))
    bufferSize = FFMIN(bufferSize, bd->size);
    if (!bufferSize) {
        cout << "ptr = " << bd->ptr << "size = " << bd->size << endl;
    }
//    将音视频数据内部的data复制到buff中
    memcpy(pBuff, bd->ptr, bufferSize);
    bd->ptr += bufferSize;
    bd->size -= bufferSize;
    return bufferSize;
}

int main(int argc, char *argv[]) {

    AVIOContext *pAvioCtx = nullptr;
    uint8_t *pAvioCtxBuffer = nullptr;
    size_t avioCtxBufferSize = 4096;
    struct buffer_data bufferData = {nullptr, 0};
    // 贯穿全局的context信息
    AVFormatContext *pFmtCtx = nullptr;
    //  设置日志等级
    av_log_set_level(AV_LOG_DEBUG);
    if (argc != 2) {
        cout << "please input a reading file" << "argc = " << argc << endl;
        return -1;
    }

    char *inputFileName = argv[1];
    // 将文件进行内存映射
    /*
     * mmap()  creates  a new mapping in the virtual address space of the calling process.  The starting address for the new mapping is specified in addr.  The length argument specifies the length of
       the mapping (which must be greater than 0).

       If addr is NULL, then the kernel chooses the (page-aligned) address at which to create the mapping; this is the most portable method of creating a new mapping.  If addr is not NULL,  then  the
       kernel  takes  it  as  a  hint  about  where  to  place  the  mapping;  on  Linux,  the  kernel  will  pick  a  nearby  page  boundary  (but  always  above  or  equal to the value specified by
       /proc/sys/vm/mmap_min_addr) and attempt to create the mapping there.  If another mapping already exists there, the kernel picks a new address that may or may not depend on the hint.   The  ad‐
       dress of the new mapping is returned as the result of the call.
     * */
    uint8_t *buffer = nullptr;
    size_t buffer_size = 0;
    int ret = av_file_map(inputFileName, &buffer, &buffer_size, 0, nullptr);
    if (ret < 0) {
        cout << "av_file_map failed" << "ret = " << ret << endl;
        goto end;
    }

    // 记录 @av_file_map 中获取的文件内存映射的内容和长度
    bufferData.ptr = buffer;
    bufferData.size = buffer_size;

    // Allocate an AVFormatContext.

    pFmtCtx = avformat_alloc_context();
    if (!pFmtCtx) {
        ret = AVERROR(ENOMEM);
        goto end;
    }

    pAvioCtxBuffer = (uint8_t *) av_malloc(avioCtxBufferSize);
    if (!pAvioCtxBuffer) {
        ret = AVERROR(ENOMEM);
        goto end;
    }

    pAvioCtx = avio_alloc_context(pAvioCtxBuffer, avioCtxBufferSize, 0, &bufferData, &ReadPacket,
                                  nullptr,nullptr);
    if (!pAvioCtx) {
        ret = AVERROR(ENOMEM);
        goto end;
    }
    // 调用  avformat_open_input 之前，要是使用文件的音视频处理，这里需要提前进行初始化，然后再调用、
    // avformat_open_input 打开对应的文件
    pFmtCtx->pb = pAvioCtx;
    ret = avformat_open_input(&pFmtCtx, nullptr, nullptr, nullptr);
    if (ret < 0) {
        cerr << "Could not open input!" << endl;
        goto end;
    }

    ret = avformat_find_stream_info(pFmtCtx, nullptr);
    if (ret < 0) {
        cerr << "Could not find stream information!" << endl;
        goto end;
    }

    av_dump_format(pFmtCtx, 0, inputFileName, 0);


    cout << "avio reading demo success" << endl;
end:
    avformat_close_input(&pFmtCtx);
    if (pAvioCtxBuffer && !pAvioCtx)
        av_freep(pAvioCtxBuffer);
    if (pAvioCtx)
        av_freep(&pAvioCtx->buffer);
    avio_context_free(&pAvioCtx);

    av_file_unmap(buffer, buffer_size);
    return 0;
}