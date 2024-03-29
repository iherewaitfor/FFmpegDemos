- [FFMpegs Examples示例文档](#ffmpegs-examples示例文档)
  - [How to Build 如何构建](#how-to-build-如何构建)
- [解封装及解码 demuxing\_decoding](#解封装及解码-demuxing_decoding)
- [纯视频编码](#纯视频编码)
- [封装及编码 muxing](#封装及编码-muxing)
- [过滤视频 filtering\_vidoe\_sharedmemory](#过滤视频-filtering_vidoe_sharedmemory)


# FFMpegs Examples示例文档
该库下有ffmpegs的核心功能api使用的示例说明。包括 
- 解封装及解码demuxing_decoding
- 视频编码encoding
- 视频拉伸scaling_video
- 视频过滤器使用filtering_video_sharedmemory
## How to Build 如何构建
先安装cmake，进入源码目录新建build目录。然后在build 目录中进入命令行。然后执行命令
```
cmake .. -G "Visual Studio 17 2022"
```
。然后打开生成的sln文件，将你希望构建的项目设置为启动项即可。 cmake使用可参考本github项目[cmakevisualstudio](https://github.com/iherewaitfor/cmakevisualstudio)

如果你安装的是其他版本的Visual Studio，可以通过以下命令，查看对应的Visual Studio版本。
```
cmake -G help
```

```
 Visual Studio 17 2022        = Generates Visual Studio 2022 project files.
                                 Use -A option to specify architecture.
  Visual Studio 16 2019        = Generates Visual Studio 2019 project files.
                                 Use -A option to specify architecture.
  Visual Studio 15 2017 [arch] = Generates Visual Studio 2017 project files.
                                 Optional [arch] can be "Win64" or "ARM".
  Visual Studio 14 2015 [arch] = Generates Visual Studio 2015 project files.
                                 Optional [arch] can be "Win64" or "ARM".
  Visual Studio 12 2013 [arch] = Generates Visual Studio 2013 project files.
                                 Optional [arch] can be "Win64" or "ARM".
  Visual Studio 11 2012 [arch] = Deprecated.  Generates Visual Studio 2012
                                 project files.  Optional [arch] can be
                                 "Win64" or "ARM".
  Visual Studio 9 2008 [arch]  = Generates Visual Studio 2008 project files
```

比如你安装的是Visual studio 2017，需要构建Win64项目,可以将构建命令改成
```
cmake .. -G "Visual Studio 15 2017 Win64"
```


由于本项目引用了64位的ffmpeg库，所以项目都用64位构建。需要构建32位，把对应的ffmpeg-5.12库换成对应的32位的，然后参考cmakevisualstudio,生成32位的即可。
如
```
cmake .. -G "Visual Studio 17 2022" -A win32
```

# 解封装及解码 demuxing_decoding

本示例展示如何进行解封装及解码。
具体说明请查看文件
[demuxing_decoding README.md](https://github.com/iherewaitfor/FFmpegDemos/tree/main/examples/demuxing_decoding)

# 纯视频编码


# 封装及编码 muxing

 本示例展示如何进行解封装及解码。
详解查看[muxing项目README.md](https://github.com/iherewaitfor/FFmpegDemos/blob/main/examples/muxing/README.md)

示例代码[https://github.com/iherewaitfor/FFmpegDemos/tree/main/examples/muxing](https://github.com/iherewaitfor/FFmpegDemos/tree/main/examples/muxing)

# 过滤视频 filtering_vidoe_sharedmemory
本示例，展示了如何过滤视频，并把过滤后视频帧写到共享内存中。可通过其他进程从共享内存中读取，并渲染到窗口上。
详解查看[filtering_video_sharedmemory的README.md](https://github.com/iherewaitfor/FFmpegDemos/blob/main/examples/filtering_video_sharedmemory/README.md)
示例代码[https://github.com/iherewaitfor/FFmpegDemos/tree/main/examples/filtering_video_sharedmemory](https://github.com/iherewaitfor/FFmpegDemos/tree/main/examples/filtering_video_sharedmemory)

