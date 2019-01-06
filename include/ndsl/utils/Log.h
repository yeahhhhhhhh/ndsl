////
// @file Log.h
// @brief
// log头文件
//
// @author zhangsiqi
// @email 1575033031@qq.com
//
#ifndef __NDSL_UTILS_LOG_H__
#define __NDSL_UTILS_LOG_H__

#if defined(__cplusplus)
extern "C" {
#endif

#define LOG(level, source,format, ...) ndsl_log_into_sink(level,source, format, ##__VA_ARGS__)

////
// @brief
// 日志级别
//
enum
{
    LOG_DEBUG_LEVEL = 0,
    LOG_INFO_LEVEL = 1,
    LOG_WARN_LEVEL = 2,
    LOG_ERROR_LEVEL = 3
};

void set_ndsl_log_sinks(int sinks);
void ndsl_log_into_sink(int level,int source, const char *format, ...);

#if defined(__cplusplus)
}
#    endif

#endif // __NDSL_UTILS_LOG_H__