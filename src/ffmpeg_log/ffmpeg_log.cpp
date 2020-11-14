//
// Created by andrew on 2020/10/31.
//
#include <iostream>
extern "C"{
#include <libavutil/log.h>
}

using namespace std;

int main(int argc, char *argv[])
{
    av_log_set_level(AV_LOG_DEBUG);
    av_log(NULL, AV_LOG_DEBUG,"Hello world!\n");

    return 0;
}