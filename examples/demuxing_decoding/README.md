# demuxing_decoding 解封装解码
本例子的功能是把一个视频文件，进行解封装，解码，把把解码后的视频数据和音频数据分别写到一个文件时去。

# Demuxing解封装

 	Demuxers read a media file and split it into chunks of data (packets). A packet contains one or more encoded frames which belongs to a single elementary stream. In the lavf API this process is represented by the avformat_open_input() function for opening a file, av_read_frame() for reading a single packet and finally avformat_close_input(), which does the cleanup.

```C++
int avformat_open_input(AVFormatContext **ps, const char *url,
                        const AVInputFormat *fmt, AVDictionary **options);
```
# 资源的申请和释放
## 资源申请
- AVFormatContext *fmt_ctx
- AVCodecContext *video_dec_ctx
- AVFrame * frame
- AVPacket *pkt
- uint8_t *video_dst_data[4] = {NULL}; //image缓存

申请AVFormatContext
``` c++
    /* open input file, and allocate format context */
    //使用avformat_close_input进行资源释放
    if (avformat_open_input(&fmt_ctx, src_filename, NULL, NULL) < 0) {
```

申请AVCodecContext
```C++
AVCodecContext **dec_ctx;

AVStream *st;
const AVCodec *dec = NULL;

st = fmt_ctx->streams[AVMEDIA_TYPE_VIDEO];
dec = avcodec_find_decoder(st->codecpar->codec_id);
 //avcodec_alloc_context3申请解码器空间， 使用avcodec_free_context进行翻译
*dec_ctx = avcodec_alloc_context3(dec);
avcodec_parameters_to_context(*dec_ctx, st->codecpar);
avcodec_open2(*dec_ctx, dec, NULL) ;  //初始化解码器
```

申请AVFrame
```C++
frame = av_frame_alloc(); //使用av_frame_free释放
//avcodec_receive_frame(dec, frame)  拿到解码后的帧，可以读取到视频帧数据。
```
申请AVPacket
```C++
pkt = av_packet_alloc(); //申请空间
//avcodec_send_packet(dec, pkt);把编码的包送去解码。
//av_packet_unref(): Wipe the packet.Unreference the buffer referenced by the packet and 
//reset the remaining packet fields to their default values.
//av_packet_unref(pkt);  每次用完packet
//av_packet_free(&pkt);释放资源 
```
申请视频帧缓存。根据格式不同，使用的数据不同。如AV_PIX_FMT_YUV420P、AV_PIX_FMT_RGBA.
```C++
int av_image_alloc(uint8_t *pointers[4], int linesizes[4],
                   int w, int h, enum AVPixelFormat pix_fmt, int align);
```

## 释放
```C++
    avcodec_free_context(&video_dec_ctx); // AVCodecContext * 
    avcodec_free_context(&audio_dec_ctx); //AVCodecContext * 
    avformat_close_input(&fmt_ctx);       //AVFormatContext *fmt_ctx
    if (video_dst_file)
        fclose(video_dst_file);
    if (audio_dst_file)
        fclose(audio_dst_file);
    av_packet_free(&pkt);               //AVPacket *
    av_frame_free(&frame);              //AVFrame *
    av_free(video_dst_data[0]);         //uint8_t *video_dst_data[4]
```

# 参考
[https://ffmpeg.org/doxygen/5.1/index.html](https://ffmpeg.org/doxygen/5.1/index.html)

[https://ffmpeg.org/doxygen/5.1/group__libavf.html](https://ffmpeg.org/doxygen/5.1/group__libavf.html)