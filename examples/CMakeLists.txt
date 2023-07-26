#Cmake 最低版本号要求
cmake_minimum_required(VERSION 3.10)

# 项目信息
project (examples)

# 设置子系统为窗口程序
#set ( CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} /SUBSYSTEM:WINDOWS" ) 

#项目使用UNICODE版本。win中的各种API将使用UNICODE版本。
#add_definitions("-DUNICODE" "-D_UNICODE")
set(TARGET_OUT_DIR "${CMAKE_BINARY_DIR}/$<CONFIGURATION>")


# Copy a list of files from one directory to another. Relative files paths are maintained.
# The path component of the source |file_list| will be removed.
macro(COPY_FILES target file_list source_dir target_dir)
  foreach(FILENAME ${file_list})
    set(source_file ${source_dir}/${FILENAME})
    get_filename_component(target_name ${FILENAME} NAME)
    set(target_file ${target_dir}/${target_name})

    string(FIND ${source_file} "$<CONFIGURATION>" _pos)
    if(NOT ${_pos} EQUAL -1)
      # Must test with an actual configuration directory.
      string(REPLACE "$<CONFIGURATION>" "Release" existing_source_file ${source_file})
      if(NOT EXISTS ${existing_source_file})
        string(REPLACE "$<CONFIGURATION>" "Debug" existing_source_file ${source_file})
      endif()
    else()
      set(existing_source_file ${source_file})
    endif()

    if(IS_DIRECTORY ${existing_source_file})
      add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${source_file}" "${target_file}"
        VERBATIM
        )
    else()
      add_custom_command(
        TARGET ${target}
        POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${source_file}" "${target_file}"
        VERBATIM
        )
    endif()
  endforeach()
endmacro()

set (FFMPEG_DLLS
	avcodec-59.dll
	avdevice-59.dll
	avfilter-8.dll
	avformat-59.dll
	avutil-57.dll
	postproc-56.dll
	swresample-4.dll
	swscale-6.dll
)
set (FFMPEG_DLLS_DIR "${PROJECT_SOURCE_DIR}/../ffmpeg-5.1.2/bin")
# 添加子目录
add_subdirectory(demuxing_decoding)
add_subdirectory(scaling_video)
add_subdirectory(encode_video)
add_subdirectory(muxing)
add_subdirectory(filtering_video)
add_subdirectory(filtering_video_sharedmemory)