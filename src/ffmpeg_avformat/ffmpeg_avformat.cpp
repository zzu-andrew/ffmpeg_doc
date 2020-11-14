//
// Created by andrew on 2020/11/1.
//
#include <iostream>

extern "C" {
#include <libavutil/log.h>
#include <libavformat/avformat.h>
}


int main(int argc, char *argv[]) {

    AVFormatContext *fmt_ctx = NULL;
    av_log_set_level(AV_LOG_INFO);
    /*所有进行操作前，先执行以下，否则需要自己制定类型*/
    av_register_all();
    /*Open an input stream and read the header*/
    int ret = avformat_open_input(&fmt_ctx, "/work/test/test.mp4", NULL, NULL);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "can't open file.\n");
        return -1;
    }
    /*
     * Print detailed information about the input or output format
     * */
    av_dump_format(fmt_ctx, 0, "/work/test/test.mp4", 0);
    /*Close an opened input AVFormatContext*/
    avformat_close_input(&fmt_ctx);

    return 0;
}
