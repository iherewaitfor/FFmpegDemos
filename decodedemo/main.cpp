#include <iostream>
#include <Windows.h>
#include "demuxing_decoding.h"
#include "scaling_video.h"



int main(LPWSTR lpCmdLine)
{
    int nArgs = 0;
    LPWSTR* szArglist = NULL;
    szArglist = CommandLineToArgvW(GetCommandLineW(), &nArgs);
    std::wcout << L"Hello World" << std::endl;
    std::wcout << L"the argc " << nArgs;
    const wchar_t* argv_0 = szArglist[0];
    std::wcout << L"the argv[0] " << argv_0 << std::endl;
    if (nArgs > 2) {
        const wchar_t* argv_1 = szArglist[1];
        std::wcout << L"the argv[1] " << argv_1 <<std::endl;
        DemuxingDecoding* demuxingDecoding = new DemuxingDecoding(argv_1);
        VideoInfo videoInfo;
        if (demuxingDecoding->getVideoInfo(videoInfo)) {
            printf("pixFormat: %d \n", videoInfo.pix_fmt);
            printf("width: %d \n", videoInfo.width);
            printf("height: %d\n", videoInfo.height);
            std::wcout << L"pixFormat:" << videoInfo.pix_fmt << std::endl;
            std::wcout << L"width:" << videoInfo.width << std::endl;
            std::wcout << L"height:" << videoInfo.height << std::endl;
        }
        FrameData frameData;
        int framecount = 0;
        while (demuxingDecoding->getNetxtFrame(frameData)) {
            std::wcout << L"framecount= " << ++framecount << std::endl;
            static int  i = 0;
            if (++i== 3) {
                FILE* dst_file;
                dst_file = fopen("a.rgba", "wb");
                ScalingVideo* scalingVideo = new ScalingVideo(frameData.width, frameData.height, frameData.pix_fmt,
                    800, 600, AV_PIX_FMT_RGBA);
                scalingVideo->scaleVideo(frameData.dst_data, frameData.dst_linesizes, 0, frameData.height);
                /* write scaled image to file */
                fwrite(scalingVideo->dst_data[0], 1, scalingVideo->dst_bufsize, dst_file);
            }

        }

        
        const wchar_t* argv_2 = szArglist[2];
        std::wcout << L"the argv[2] " << argv_2;
    }
    return 0;
}