//
// Created by andrew on 2020/11/8.
//

//
// Created by andrew on 2020/11/7.
//

#include <iostream>

extern "C" {
#include <libavutil/log.h>
#include <libavformat/avio.h>
}

using namespace std;

int main(int argc, char *argv[]) {
    char tempBuff[128];
    //  设置日志等级
    av_log_set_level(AV_LOG_DEBUG);
    if (argc < 2) {
        av_log(NULL, AV_LOG_ERROR, "The count of parameter should be more than two!\n");
        exit(1);
    }

    char *pSrcFileName = argv[1];
    if (NULL == pSrcFileName) {
        av_log(NULL, AV_LOG_ERROR, "invalid src filename.\n");
        exit(2);
    }

    // 创建一个文件
    snprintf(tempBuff, sizeof(tempBuff), "echo \"hello world!\n \" > %s", pSrcFileName);
    system(tempBuff);

    AVIOContext *avioCtx = NULL;
    int errCode = -1;
    /*
     * Create and initialize a AVIOContext for accessing the
     * resource indicated by url.
     * */
    if ((errCode = avio_open(&avioCtx, pSrcFileName, AVIO_FLAG_READ)) < 0) {
        av_log(NULL, AV_LOG_ERROR, "Coud not open file %s\n", pSrcFileName);
        exit(3);
    }
    unsigned char strBuff[1024];
    avio_read(avioCtx, strBuff, sizeof(strBuff));

    avio_close(avioCtx);

    av_log(NULL, AV_LOG_DEBUG, "read file content:%s", strBuff);
    memset(tempBuff, 0, sizeof(tempBuff));
    snprintf(tempBuff, sizeof(tempBuff), "rm %s", pSrcFileName);
    system(tempBuff);
    return 0;
}