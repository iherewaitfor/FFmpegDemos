# demuxing_decoding 解封装解码
本例子的功能是把一个视频文件，进行解封装，解码，把把解码后的视频数据和音频数据分别写到一个文件时去。

# Demuxing解封装

 	Demuxers read a media file and split it into chunks of data (packets). A packet contains one or more encoded frames which belongs to a single elementary stream. In the lavf API this process is represented by the avformat_open_input() function for opening a file, av_read_frame() for reading a single packet and finally avformat_close_input(), which does the cleanup.

```C++
int avformat_open_input(AVFormatContext **ps, const char *url,
                        const AVInputFormat *fmt, AVDictionary **options);
```


# 参考
[https://ffmpeg.org/doxygen/5.1/index.html](https://ffmpeg.org/doxygen/5.1/index.html)

[https://ffmpeg.org/doxygen/5.1/group__libavf.html](https://ffmpeg.org/doxygen/5.1/group__libavf.html)