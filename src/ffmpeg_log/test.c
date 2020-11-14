//
// Created by andrew on 2020/10/31.
//

//
// Created by andrew on 2020/10/31.
//
#include <stdio.h>
#include <libavutil/log.h>


extern void av_log_set_level(int level);
int main(int argc, char *argv[])
{
    av_log_set_level(AV_LOG_DEBUG);
//     set_av_log_level(AV_LOG_DEBUG);

    av_log(NULL, AV_LOG_DEBUG,"Hello world!\n");


    return 0;
}
