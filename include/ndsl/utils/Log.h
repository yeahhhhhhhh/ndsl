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

#define LOG(level, path, format, ...) ndsl_log_into_sink(level,path, format, ##__VA_ARGS__)

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

////
// @brief
// 日志sink
//
enum
{
    LOG_SINK_FILE = 1,
    LOG_SINK_SYSLOG = 2,
};

void set_ndsl_log_sinks(int sink = 1);
void set_ndsl_log_level(int level);
void ndsl_log_into_sink(int level,const char* path, const char *format, ...);

#if defined(__cplusplus)
}
#    endif

#endif // __NDSL_UTILS_LOG_H__