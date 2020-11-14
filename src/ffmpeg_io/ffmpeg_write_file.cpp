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

    AVIOContext *avioCtx = NULL;
    int errCode = -1;
    /*
     * Create and initialize a AVIOContext for accessing the
     * resource indicated by url.
     * */
    if ((errCode = avio_open(&avioCtx, pSrcFileName, AVIO_FLAG_WRITE)) < 0) {
        av_log(NULL, AV_LOG_ERROR, "Coud not open file %s\n", pSrcFileName);
        exit(3);
    }
    string strBuff = "hello world!\n";

    avio_write(avioCtx, (const unsigned char *)(strBuff.c_str()), strBuff.length());

    avio_close(avioCtx);

    char tempBuff[128];
    snprintf(tempBuff, sizeof(tempBuff), "cat %s", pSrcFileName);

    system(tempBuff);
    snprintf(tempBuff, sizeof(tempBuff), "rm %s", pSrcFileName);

    system(tempBuff);
    return 0;
}