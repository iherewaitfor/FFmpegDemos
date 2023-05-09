#Cmake 最低版本号要求
cmake_minimum_required(VERSION 2.8)

# 项目信息
project (examples)

# 设置子系统为窗口程序
#set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS" ) 

#项目使用UNICODE版本。win中的各种API将使用UNICODE版本。
#add_definitions("-DUNICODE" "-D_UNICODE")

# 添加子目录
add_subdirectory(demuxing_decoding)

# 添加子目录
add_subdirectory(scaling_video)
