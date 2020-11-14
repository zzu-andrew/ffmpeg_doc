cmake_minimum_required(VERSION 3.2)
project(ffmpeg_doc)

set(CMAKE_CXX_STANDARD 14)

add_subdirectory(FFmpeg)

set(CMAKE_C_FLAGS_PROFILE "-p -g -O2" CACHE STRING "")
set(CMAKE_CXX_FLAGS_PROFILE "-p -g -O2" CACHE STRING "")

# IO操作
add_executable(ffmpeg_io_write ffmpeg_io/ffmpeg_write_file.cpp)
target_link_libraries(ffmpeg_io_write
        PUBLIC avutil
        PUBLIC avformat
        PUBLIC avcodec)
add_executable(ffmpeg_io_read ffmpeg_io/ffmpeg_read_file.cpp)
target_link_libraries(ffmpeg_io_read
        PUBLIC avutil
        PUBLIC avformat
        PUBLIC avcodec)
#媒体信息，并进行打印
add_executable(ffmpeg_mediainfo ffmpeg_avformat/ffmpeg_mediainfo.cpp)
target_link_libraries(ffmpeg_mediainfo
        PUBLIC avutil
        PUBLIC avformat
        PUBLIC avcodec)




add_executable(ffmpeg_io ffmpeg_avformat/ffmpeg_io.cpp)
add_executable(ffmpeg_avformat ffmpeg_avformat/ffmpeg_avformat.cpp)
add_executable(ffmpeg_log ffmpeg_log/ffmpeg_log.cpp)
add_executable(extrac_audio extrac_audio/extrac_audio.cpp)
add_executable(extrac_video extrac_video/extrac_video.cpp)

#target_link_directories(ffmpeg_log
 #       PUBLIC "./../lib")
target_link_libraries(ffmpeg_avformat
        PUBLIC avutil
        PUBLIC avformat)
target_link_libraries(ffmpeg_io
        PUBLIC avutil
        PUBLIC avformat)
target_link_libraries(ffmpeg_log
        PUBLIC avutil)
target_link_libraries(extrac_audio
        PUBLIC avutil
        PUBLIC avformat
        PUBLIC avcodec)
target_link_libraries(extrac_video
        PUBLIC avutil
        PUBLIC avformat
        PUBLIC avcodec)

#target_include_directories(${FILE_DESC_TEST} PUBLIC ./../lib)
