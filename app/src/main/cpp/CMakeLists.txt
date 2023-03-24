# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.18.1)

# Declares and names the project.

project("ffmpeg")
# 声明一个jnilibs变量
set(jnilibs ${CMAKE_SOURCE_DIR}/../jniLibs)

#message(Android abi is ${ANDROID_ABI}, jni dir is  ${jnilibs})
include_directories(
        include
)

# 指定链接器在哪些目录中查找库文件
link_directories(
        ${jnilibs}/${ANDROID_ABI}
)

# 组合${jnilibs}/${ANDROID_ABI}的库文件
set(third-party-libs
        avformat
        avcodec
        avfilter
        swresample
        swscale
        avutil
        )

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.
file(GLOB COMMON_SRC_LIST
        ${CMAKE_CURRENT_SOURCE_DIR}/*.cpp)

add_library( # Sets the name of the library.
        ffmpeg

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        ${COMMON_SRC_LIST})

get_filename_component(HINT_PATH ${ANDROID_C_COMPILER} DIRECTORY)
#set(ANDROID_ABI arm64-v8a)
message(Android abi is ${ANDROID_ABI}, jni dir is  ${jnilibs})
message(SANITIZE:${SANITIZE}, CMAKE_ANDROID_ARCH:${CMAKE_ANDROID_ARCH}, CMAKE_ANDROID_ARCH_ABI:${CMAKE_ANDROID_ARCH_ABI})

if(SANITIZE)
    # For asan and ubsan, we need to copy some files from the NDK into our APK.
    get_filename_component(HINT_PATH ${ANDROID_C_COMPILER} DIRECTORY)
    set(ARCH_STR ${CMAKE_ANDROID_ARCH})
    if ("${CMAKE_ANDROID_ARCH_ABI}" STREQUAL "arm64-v8a")
        set(ARCH_STR "aarch64")
    elseif ("${CMAKE_ANDROID_ARCH_ABI}" STREQUAL "armeabi")
        set(ARCH_STR "arm")
    elseif ("${CMAKE_ANDROID_ARCH_ABI}" STREQUAL "armeabi-v7a")
        set(ARCH_STR "arm")
    elseif ("${CMAKE_ANDROID_ARCH_ABI}" STREQUAL "x86")
        set(ARCH_STR "i686")
    elseif ("${CMAKE_ANDROID_ARCH_ABI}" STREQUAL "x86_64")
        set(ARCH_STR "x86_64")
    endif()

    if(${SANITIZE} STREQUAL "hwasan")
        message("Using hwasan")

        target_compile_options(ffmpeg PUBLIC -fsanitize=hwaddress -fno-omit-frame-pointer)
        target_link_options(ffmpeg PUBLIC -fsanitize=hwaddress)
    elseif(${SANITIZE} STREQUAL "asan")
        message("Using asan")

        target_compile_options(ffmpeg PUBLIC -fsanitize=address -fno-omit-frame-pointer)
        target_link_options(ffmpeg PUBLIC -fsanitize=address)

        # Grab libclang_rt.asan-${ARCH_STR}-android.so from the NDK.
        file(GLOB ASAN_GLOB "${HINT_PATH}/../lib64/clang/*/lib/linux")
        find_file(ASAN
                NAMES libclang_rt.asan-${ARCH_STR}-android.so
                PATHS ${ASAN_GLOB})
        get_filename_component(ASAN_NAME ${ASAN} NAME)
        set(ASAN_NAME ${CMAKE_SOURCE_DIR}/../../asan/jniLibs/${CMAKE_ANDROID_ARCH_ABI}/${ASAN_NAME})
        message(ASAN_NAME:${ASAN_NAME})
        add_custom_command(
                TARGET ffmpeg PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy ${ASAN} ${ASAN_NAME})

        # Grab the asan wrapper script from the NDK.
        find_file(WRAP
                NAMES asan.sh
                HINTS ${HINT_PATH}/../../../../../wrap.sh)
        set(WRAP_NAME ${CMAKE_SOURCE_DIR}/../../asan/resources/lib/${CMAKE_ANDROID_ARCH_ABI}/wrap.sh)
        add_custom_command(
                TARGET ffmpeg PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy ${WRAP} ${WRAP_NAME})
    elseif(${SANITIZE} STREQUAL "ubsan")
        message("Using ubsan")

        target_compile_options(ffmpeg PUBLIC -fsanitize=undefined -fno-sanitize-recover=undefined)
        target_link_options(ffmpeg PUBLIC -fsanitize=undefined -fno-sanitize-recover=undefined)

        # Grab libclang_rt.ubsan_standalone-${ARCH_STR}-android.so from the NDK.
        file(GLOB UBSAN_GLOB "${HINT_PATH}/../lib64/clang/*/lib/linux")
        find_file(UBSAN
                NAMES libclang_rt.ubsan_standalone-${ARCH_STR}-android.so
                PATHS ${UBSAN_GLOB})
        get_filename_component(UBSAN_NAME ${UBSAN} NAME)
        set(UBSAN_NAME ${CMAKE_SOURCE_DIR}/../../ubsan/jniLibs/${CMAKE_ANDROID_ARCH_ABI}/${UBSAN_NAME})
        add_custom_command(
                TARGET ffmpeg PRE_BUILD
                COMMAND ${CMAKE_COMMAND} -E copy ${UBSAN} ${UBSAN_NAME})
    endif()
endif()

#add_library(
#        avformat
#        STATIC
#        IMPORTED
#)
#set_target_properties(
#        avformat
#        PROPERTIES IMPORTED_LOCATION
#        ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libavformat.a
#)
#
#add_library(
#        avcodec
#        STATIC
#        IMPORTED
#)
#set_target_properties(
#        avcodec
#        PROPERTIES IMPORTED_LOCATION
#        ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libavcodec.a
#)
#
##add_library(
##        avfilter
##        STATIC
##        IMPORTED
##)
##set_target_properties(
##        avformat
##        PROPERTIES IMPORTED_LOCATION
##        ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libavfilter.a
##)
#
#add_library(
#        swresample
#        STATIC
#        IMPORTED
#)
#set_target_properties(
#        swresample
#        PROPERTIES IMPORTED_LOCATION
#        ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libswresample.a
#)
#
#add_library(
#        swscale
#        STATIC
#        IMPORTED
#)
#set_target_properties(
#        swscale
#        PROPERTIES IMPORTED_LOCATION
#        ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libswscale.a
#)

#add_library(
#        avutil
#        STATIC
#        IMPORTED
#)
#set_target_properties(
#        avutil
#        PROPERTIES IMPORTED_LOCATION
#        ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libavutil.a
#)

add_library(
        avformat
        SHARED
        IMPORTED
)
set_target_properties(
        avformat
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libavformat.so
)

add_library(
        avutil
        SHARED
        IMPORTED
)

set_target_properties(
        avutil
        PROPERTIES IMPORTED_LOCATION
        ${jnilibs}/${ANDROID_ABI}/libavutil.so)

add_library(
        avcodec
        SHARED
        IMPORTED
)
set_target_properties(
        avcodec
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libavcodec.so
)

add_library(
        avfilter
        SHARED
        IMPORTED
)
set_target_properties(
        avfilter
        PROPERTIES IMPORTED_LOCATION
        ${jnilibs}/${ANDROID_ABI}/libavfilter.so)

add_library(
        swresample
        SHARED
        IMPORTED
)
set_target_properties(
        swresample
        PROPERTIES IMPORTED_LOCATION
        ${CMAKE_SOURCE_DIR}/../jniLibs/${ANDROID_ABI}/libswresample.so
)

add_library(
        swscale
        SHARED
        IMPORTED
)
set_target_properties(
        swscale
        PROPERTIES IMPORTED_LOCATION
        ${jnilibs}/${ANDROID_ABI}/libswscale.so)


# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        ffmpeg

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib}
        ${third-party-libs}
        )