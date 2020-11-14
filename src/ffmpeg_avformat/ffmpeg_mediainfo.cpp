//
// Created by andrew on 2020/11/8.
//

#include <iostream>
#include <string>
extern "C" {
#include <libavformat/avformat.h>
#include <libavutil/log.h>
#include <libavutil/dict.h>
}
using namespace std;

// 声明一下 因为原函数是在.c中声明的结构体
struct AVDictionary {
    int count;
    AVDictionaryEntry *elems;
};

// 打印媒体信息的简单示例
void my_av_input_dump_format(AVFormatContext *ic, int index,
                    const char *url, int is_output){

    string pSrt = (is_output != 0) ? "output":"input";
    cout << "音视频输入输出类型：" << pSrt <<endl;
    cout << "index = " << index << endl;
    if(is_output){
        cout << "fromat name:" << ic->oformat->name << endl;
    }else
        cout << "fromat name:" << ic->iformat->name << endl;
    // url
    cout << "from :" << url << endl;

    //ic->metadata
    int i = 0;
    i =  ic->metadata->count;
    for (i = 0; i < ic->metadata->count; i++){
        cout << "    " <<ic->metadata->elems[i].key << ":" <<ic->metadata->elems[i].value << endl;
    }
}

int main(int argc, char *argv[]){

//    设置日志等级
    av_log_set_level(AV_LOG_DEBUG);
    if(argc< 2)
    {
        av_log(NULL, AV_LOG_ERROR, "you should input media file!\n");
        return -1;
    }
//    所有获取音视频信息都要首先注册
    av_register_all();
    int errCode = -1;
    AVFormatContext *pFmtCtx = NULL;
    const char *pSrcName = argv[1];
    if((errCode = avformat_open_input(&pFmtCtx, pSrcName, NULL, NULL)) < 0){
        av_log(NULL, AV_LOG_ERROR, "avformat open input failed.\n");
        exit(1);
    }
    //官方接口
//    av_dump_format(pFmtCtx, 0, pSrcName, 0);
    my_av_input_dump_format(pFmtCtx, 0, pSrcName, 0);
    //释放资源
    avformat_close_input(&pFmtCtx);

    return 0;
}