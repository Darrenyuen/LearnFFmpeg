//
// Created by darrenyuan on 2023/3/20.
//
#include <cstring>

#include "com_example_learnffmpeg_config_ConfigInfo.h"

extern "C" {
#include "include/libavcodec/version.h"
#include "include/libavcodec/avcodec.h"
#include "include/libavformat/version.h"
#include "include/libavutil/version.h"
#include "include/libavfilter/version.h"
#include "include/libswresample/version.h"
#include "include/libswscale/version.h"
}

#ifdef __cplusplus
extern "C" {
#endif

JNIEXPORT jstring JNICALL Java_com_example_learnffmpeg_config_ConfigInfo_getConfigInfo
        (JNIEnv *jniEnv, jclass jclazz) {
    char strBuffer[1024 * 4] = {0};
    strcat(strBuffer, "libavcodec : ");
    strcat(strBuffer, AV_STRINGIFY(LIBAVCODEC_VERSION));
    strcat(strBuffer, "\nlibavformat : ");
    strcat(strBuffer, AV_STRINGIFY(LIBAVFORMAT_VERSION));
    strcat(strBuffer, "\nlibavutil : ");
    strcat(strBuffer, AV_STRINGIFY(LIBAVUTIL_VERSION));
    strcat(strBuffer, "\nlibavfilter : ");
    strcat(strBuffer, AV_STRINGIFY(LIBAVFILTER_VERSION));
    strcat(strBuffer, "\nlibswresample : ");
    strcat(strBuffer, AV_STRINGIFY(LIBSWRESAMPLE_VERSION));
    strcat(strBuffer, "\nlibswscale : ");
    strcat(strBuffer, AV_STRINGIFY(LIBSWSCALE_VERSION));
//    strcat(strBuffer, "\navcodec_configure : \n");
//    strcat(strBuffer, avcodec_configuration());
    strcat(strBuffer, "\navcodec_license : ");
    strcat(strBuffer, avcodec_license());
    return jniEnv->NewStringUTF(strBuffer);
}

#ifdef __cplusplus
};
#endif

