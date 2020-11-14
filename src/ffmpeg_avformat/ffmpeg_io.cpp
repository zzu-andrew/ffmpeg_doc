//
// Created by andrew on 2020/10/31.
//

#include <iostream>
extern "C" {
#include <libavformat/avformat.h>
#include <libavutil/log.h>
#include <stdio.h>
}

using namespace std;

int main(int argc, char *argv[]) {
//    ------------------- 文件操作 -------------------
    int ret = -1;
    av_log_set_level(AV_LOG_DEBUG);
    // 创建文件
    system("echo test > test.txt");
    //    文件改名
    ret = avpriv_io_move("test.txt", "mytest.txt");
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "Failed to mv test.txt\n");
        return -1;
    }
    // 删除文件
    ret = avpriv_io_delete("./mytest.txt");
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "failed to delete mytest.txt ret= %d\n", ret);
        return -1;
    }
    // ------------------------------ 文件夹操作 --------------------------
    // avio_open_dir  avio_read_dir avio_close_dir
    AVIODirContext *ctx = NULL;
    AVIODirEntry *entry = NULL;

    ret = avio_open_dir(&ctx, "./", NULL);
    if (ret < 0) {
        av_log(NULL, AV_LOG_ERROR, "failed open . dir\n");
        return -1;
    }

    while (1) {
        ret = avio_read_dir(ctx, &entry);
        if (ret < 0) {
            av_log(NULL, AV_LOG_ERROR, "cant read dir\n");
            goto failed_exit;
        }
        if (!entry)
        {
            break;
        }
        av_log(NULL, AV_LOG_INFO, "%s\n", entry->name);
        avio_free_directory_entry(&entry);
    }

failed_exit:
    avio_close_dir(&ctx);
    cout << "avformat demo" << endl;
    return 0;
}