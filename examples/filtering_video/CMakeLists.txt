#Cmake 最低版本号要求
cmake_minimum_required(VERSION 3.10)

# 项目信息
project (filtering_video) # 可以使用${PROJECT_NAME}引用项目名称

# 查找目录下的所有源文件
# 并将名称保存到DIR_SRCS变量
aux_source_directory(. DIR_SRCS)
include_directories(../../ffmpeg-5.1.2/include/)

# 设置子系统为窗口程序
# set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS" ) 

#项目使用UNICODE版本。win中的各种API将使用UNICODE版本。
#add_definitions("-DUNICODE" "-D_UNICODE")
link_directories(${PROJECT_SOURCE_DIR}/../../ffmpeg-5.1.2/lib)


# 指定生成目标
add_executable(${PROJECT_NAME} ${DIR_SRCS})

set_target_properties(${PROJECT_NAME} PROPERTIES
					ARCHIVE_OUTPUT_DIRECTORY "${TARGET_OUT_DIR}"
					RUNTIME_OUTPUT_DIRECTORY "${TARGET_OUT_DIR}"
					LIBRARY_OUTPUT_DIRECTORY "${TARGET_OUT_DIR}")

# 添加链接库
target_link_libraries(${PROJECT_NAME} avcodec.lib avdevice.lib avfilter.lib avformat.lib avutil.lib postproc.lib swresample.lib swscale.lib )

COPY_FILES("${PROJECT_NAME}" "${FFMPEG_DLLS}" "${FFMPEG_DLLS_DIR}"  "${TARGET_OUT_DIR}")