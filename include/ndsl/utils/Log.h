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

#define LOG(level, source, format, ...)                                        \
    ndsl_log_into_sink(level, source, format, ##__VA_ARGS__)

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
// 日志源
//
enum
{
    LOG_SOURCE_EPOLL = 1,
    LOG_SOURCE_THREADPOOL = 2,
    LOG_SOURCE_EVENTLOOP = 4,
    LOG_SOURCE_THREAD = 8,
    LOG_SOURCE_V8ENGINE = 16,
    LOG_SOURCE_CHANNEL = 32,
    LOG_SOURCE_UDPCHANEEL = 64,
    LOG_SOURCE_TCPCHANNEL = 128,
    LOG_SOURCE_UNIXCHANNEL = 256,
    LOG_RDMA_CHANNEL = 1024,
    LOG_SOURCE_TIMEFDCHANNEL = 2048,
    LOG_SOURCE_SIGNALFDCHANNEL = 4096,
    LOG_SOURCE_DNSCHANNEL = 8192,
    LOG_SOURCE_FILECHANNEL = 16384,
    LOG_SOURCE_TCPACCETPOR = 32768,
    LOG_SOURCE_TCPCONNECTION = 65536,
    LOG_SOURCE_UNIXCONNECTION = 131072,
    LOG_SOURCE_TIMEWHEEL = 262144,
    LOG_SOURCE_SEMAPHORE = 524288,
    LOG_SOURCE_NAMESERVICE = 1048576,
    LOG_SOURCE_CONNECTION = 2097152,
    LOG_SOURCE_MULTIPLEXER = 4194304,
    LOG_SOURCE_ENTITY = 8388608,
    LOG_SOURCE_SOCKETOP = 16777216,
    LOG_SOURCE_SPLITE3 = 33554432,
    LOG_SOURCE_XML = 67108864,
    LOG_SOURCE_ENDIAN = 134217728,
    LOG_SOURCE_TIMESTAMP = 268435456,
    LOG_SOURCE_ERROR = 536870912,
    LOG_SOURCE_PLUGIN = 1073741824,
    LOG_SOURCE_ADDRESS4 = 2147483648,
    LOGZ_SOURCE_GUID = 4294967296
};
void set_ndsl_log_sinks(int sinks);
void ndsl_log_into_sink(int level, int source, const char *format, ...);

#if defined(__cplusplus)
}
#endif

#endif // __NDSL_UTILS_LOG_H__