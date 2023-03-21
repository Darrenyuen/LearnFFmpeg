//
// Created by darrenyuan on 2023/3/20.
//
extern "C"
{
#include "include/libavformat/avformat.h"
}
#include "log_util.h"

static AVFormatContext *avFormatContext = nullptr;

#ifdef __cplusplus
extern "C" {
#endif
void init()
{
    avFormatContext = avformat_alloc_context();
}

//void decode(const char *url)
//{
//    if (avformat_open_input(&avFormatContext, url, nullptr, nullptr) != 0)
//    {
//        LOGI("LOG_TAG", "avformat_open_input");
//    }
//}
#ifdef __cplusplus
}
#endif