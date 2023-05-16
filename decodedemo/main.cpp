#include <iostream>
#include <Windows.h>
#include "demuxing_decoding.h"

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
        FrameData frameData;
        int framecount = 0;
        while (demuxingDecoding->getNetxtFrame(frameData)) {
            std::wcout << L"framecount= " << ++framecount << std::endl;
        }
        const wchar_t* argv_2 = szArglist[2];
        std::wcout << L"the argv[2] " << argv_2;
    }
    return 0;
}