- [封装及编码muxing and encoding](#封装及编码muxing-and-encoding)
- [编译及运行](#编译及运行)
  - [构建编译 请参考](#构建编译-请参考)
  - [运行](#运行)
- [容器操作](#容器操作)
  - [生成容器](#生成容器)
  - [给容器添加流](#给容器添加流)
  - [打开/关闭容器对应的文件](#打开关闭容器对应的文件)
  - [向容器添加音视频帧](#向容器添加音视频帧)
  - [把容器内数据全部写到文件](#把容器内数据全部写到文件)
- [编码器 AVCodecContext](#编码器-avcodeccontext)
  - [获取编码器](#获取编码器)
  - [编码操作](#编码操作)
- [相关资源创建和释放](#相关资源创建和释放)
  - [AVFrame](#avframe)
  - [AVPacket](#avpacket)
- [视频帧相关内存操作](#视频帧相关内存操作)


# 封装及编码muxing and encoding
本例子的功能是讲解如何 封装及编码 并输出文件。其中的视频数据和音频数据为程序生成。实际应用中，一般从设备采集视频帧和音频帧源数据。

整体流程:

生成容器-->生成编码器-->生成AVFrame并填充数据-->送编码器编码-->取出编码后的AVPacket-->填充到容器.



图解核心逻辑请参考：
[ffmpega数据结构及操作图](https://kdocs.cn/l/cp88RyxsqkMM)

![编解码](../images/demuxing_decoding_decode.png)

图：编解码

![容器核心数据](../images/demuxing_decoding_avformat.png)

图：容器核心数据


![容器操作](../images/muxing_avformat.png)

图：容器操作

![编码器核心逻辑](../images/muxing_encoding.png)

图：编码器核心逻辑

![相关数据结构](../images/demuxing_decoding_datastructs.png)

图：相关数据结构

# 编译及运行
## 构建编译 请参考
[demuxing_decoding的构建和编译](https://github.com/iherewaitfor/FFmpegDemos/blob/main/examples/demuxing_decoding/README.md#%E7%BC%96%E8%AF%91%E5%92%8C%E8%BF%90%E8%A1%8C-how-to-run)

## 运行
muxing.exe outputfile
```
muxing.exe data.mp4
```
生成的data.mp4可以直接用播放器播放。该文件包括音频流和视频流。
# 容器操作

## 生成容器
生成容器，并给容器填充相关的参数。
filename为容器对应的文件。
``` C++
    const AVOutputFormat *fmt;
    AVFormatContext *oc;
    /* allocate the output media context */
    avformat_alloc_output_context2(&oc, NULL, NULL, filename);
    fmt = oc->oformat;

     /* Write the stream header, if any. */
    ret = avformat_write_header(oc, &opt);
```
## 给容器添加流
给容器添加流，并指定流的id。
```C++
    ost->st = avformat_new_stream(oc, NULL);
    ost->st->id = oc->nb_streams-1;
```
从编码器上获取流的参数，填充到容器对应的流中（音频流/视频流）。

```C++
    /* copy the stream parameters to the muxer */
    ret = avcodec_parameters_from_context(ost->st->codecpar, c);
```
## 打开/关闭容器对应的文件
打开容器对应的文件，以便后续写文件。
写完所有数据后，需要关闭文件。

```c++
    avio_open(&oc->pb, filename, AVIO_FLAG_WRITE);
    /* Close the output file. */
    avio_closep(&oc->pb);
```


## 向容器添加音视频帧
pkt为编码后的音视频AVPacket.
```C++
    av_interleaved_write_frame(fmt_ctx, pkt);
```
## 把容器内数据全部写到文件
把容器里的流的尾部写到文件。
```C++
    av_write_trailer(oc);
```
# 编码器 AVCodecContext

编码上下文：
AVCodecContext、AVCode、

获取步骤：

- 1、avcodec_find_encoder(codec_id)，取得AVCodec
- 2、avcodec_alloc_context3 ，取得AVCodecContext对象并填充参数
- 3、avcodec_open2，初始化AVCodec

编码操作：

- avcodec_send_frame(enc_ctx, frame)，送AVFramet数据给编码器
- avcodec_receive_packet(enc_ctx, pkt)，从编码器读AVPacket
- av_packet_unref

## 获取编码器
取得编码器AVCodec和编码器上下文AVFormatContext。

给具体的编码器对象填充参数。


```C++
    /* find the encoder */
    *codec = avcodec_find_encoder(codec_id);

    c = avcodec_alloc_context3(*codec);

```

填充视频编码器参数

```C++
        c->codec_id = codec_id;

        c->bit_rate = 400000;
        /* Resolution must be a multiple of two. */
        c->width    = 352;
        c->height   = 288;
        /* timebase: This is the fundamental unit of time (in seconds) in terms
         * of which frame timestamps are represented. For fixed-fps content,
         * timebase should be 1/framerate and timestamp increments should be
         * identical to 1. */
        ost->st->time_base = (AVRational){ 1, STREAM_FRAME_RATE };
        c->time_base       = ost->st->time_base;

        c->gop_size      = 12; /* emit one intra frame every twelve frames at most */
        c->pix_fmt       = STREAM_PIX_FMT;
        if (c->codec_id == AV_CODEC_ID_MPEG2VIDEO) {
            /* just for testing, we also add B-frames */
            c->max_b_frames = 2;
        }
        if (c->codec_id == AV_CODEC_ID_MPEG1VIDEO) {
            /* Needed to avoid using macroblocks in which some coeffs overflow.
             * This does not happen with normal video, it just happens here as
             * the motion of the chroma plane does not match the luma plane. */
            c->mb_decision = 2;
        }
```

打开编码器

注意AVDictionary是
```C++
    AVDictionary *opt = NULL;

    av_dict_copy(&opt, opt_arg, 0);

    /* open the codec */
    ret = avcodec_open2(c, codec, &opt);
    av_dict_free(&opt);
```

## 编码操作
把AVFrame送到编码器，然后从编码器取编码后的AVPcket
```C++
    // send the frame to the encoder
    ret = avcodec_send_frame(c, frame);
    ret = avcodec_receive_packet(c, pkt);
```
完成所有帧的编码操作后，释放编码器
```C++
    avcodec_free_context(&ost->enc);
```

# 相关资源创建和释放 
## AVFrame
AVFrame核心成员如下。完整的AVFrame请参考[AVFrame源码](http://ffmpeg.org/doxygen/trunk/frame_8h_source.html)
```C++
    uint8_t *data[8]  数据
    int linesize[8]    行宽
    int width
    int height
    int format
```
申请和释放
```C++
    frame = av_frame_alloc();
    av_frame_free(frame);
```
其他操作

```C++
    /* allocate the buffers for the frame data */
    av_frame_get_buffer(frame, align);//申请内存缓存
    av_frame_make_writable();  //让对象可写,用于填充数据，填充data字段
```
## AVPacket
AVPacket部分成员如下。详细请参考[AVPacket源码](http://ffmpeg.org/doxygen/trunk/packet_8h_source.html)

```C++
    AVBufferRef *buf;//  带引用数据
    uint8_t *data;  //  无引用数据
    int   size ;    //  无引用数据大小
    int64_t pts;    //  显示时间戳
    int64_t dts;    //  解压时间戳
    int stream_index;
    AVPacketSideData *side_data;
    int side_data_elems;
```
AVPacket申请和释放 
```C++
    av_packet_alloc();
    av_packet_free(&ost->tmp_pkt);
```
# 视频帧相关内存操作
视频帧内存操作
```C++
av_image_alloc();       //申请内存
av_image_copy();        //复制内存
av_free()               //释放内存
```


