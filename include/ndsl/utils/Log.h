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

#include <stdint.h>

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
<<<<<<< HEAD

    const uint64_t LOG_SOURCE_EPOLL = 1;
    const uint64_t LOG_SOURCE_THREADPOLL = 1 << 1;
    const uint64_t LOG_SOURCE_EVENTLOOP = 1 << 2;
    const uint64_t LOG_SOURCE_THREAD = 1 << 3;
    const uint64_t LOG_SOURCE_V8ENGINE = 1 << 4;
    const uint64_t LOG_SOURCE_CHANNEL = 1 << 5;
    const uint64_t LOG_SOURCE_UDPCHANEEL = 1 << 6;
    const uint64_t LOG_SOURCE_TCPCHANNEL = 1 << 7;
    const uint64_t LOG_SOURCE_UNIXCHANNEL = 1 << 8;
    const uint64_t LOG_RDMA_CHANNEL = 1 << 9;
    const uint64_t LOG_SOURCE_TIMEFDCHANNEL = 1 << 10;
    const uint64_t LOG_SOURCE_SIGNALFDCHANNEL = 1 << 11;
    const uint64_t LOG_SOURCE_DNSCHANNEL = 1 << 12;
    const uint64_t LOG_SOURCE_FILECHANNEL = 1 << 13;
    const uint64_t LOG_SOURCE_TCPACCETPOR = 1 << 14;
    const uint64_t LOG_SOURCE_TCPCONNECTION = 1 << 15;
    const uint64_t LOG_SOURCE_UNIXCONNECTION = 1 << 16;
    const uint64_t LOG_SOURCE_TIMEWHEEL = 1 << 17;
    const uint64_t LOG_SOURCE_SEMAPHORE = 1 << 18;
    const uint64_t LOG_SOURCE_NAMESERVICE = 1 << 19;
    const uint64_t LOG_SOURCE_CONNECTION = 1 << 20;
    const uint64_t LOG_SOURCE_MULTIPLEXER = 1 << 21;
    const uint64_t LOG_SOURCE_ENTITY = 1 << 22;
    const uint64_t LOG_SOURCE_SOCKETOP = 1 << 23;
    const uint64_t LOG_SOURCE_SPLITE3 = 1 << 24;
    const uint64_t LOG_SOURCE_XML = 1 << 25;
    const uint64_t LOG_SOURCE_ENDIAN = 1 << 26;
    const uint64_t LOG_SOURCE_TIMESTAMP = 1 << 27;
    const uint64_t LOG_SOURCE_ERROR = 1 << 28;
    const uint64_t LOG_SOURCE_PLUGIN = 1 << 29;
    const uint64_t LOG_SOURCE_ADDRESS4 = 1 << 30;
    const uint64_t LOG_SOURCE_GUID = 1 << 31;
    const uint64_t LOG_SOURCE_ALL = 0XFFFFFFFF;

////
// @brief
// 添加日志源
//

uint64_t log_add_source();

=======
enum
{
    LOG_SOURCE_EPOLL = 1,
    LOG_SOURCE_THREADPOOL = 1 << 1,
    LOG_SOURCE_EVENTLOOP = 1 << 2,
    LOG_SOURCE_THREAD = 1 << 3,
    LOG_SOURCE_V8ENGINE = 1 << 4,
    LOG_SOURCE_CHANNEL = 1 << 5,
    LOG_SOURCE_UDPCHANEEL = 1 << 6,
    LOG_SOURCE_TCPCHANNEL = 1 << 7,
    LOG_SOURCE_UNIXCHANNEL = 1 << 8,
    LOG_RDMA_CHANNEL = 1 << 9,
    LOG_SOURCE_TIMEFDCHANNEL = 1 << 10,
    LOG_SOURCE_SIGNALFDCHANNEL = 1 << 11,
    LOG_SOURCE_DNSCHANNEL = 1 << 12,
    LOG_SOURCE_FILECHANNEL = 1 << 13,
    LOG_SOURCE_TCPACCETPOR = 1 << 14,
    LOG_SOURCE_TCPCONNECTION = 1 << 15,
    LOG_SOURCE_UNIXCONNECTION = 1 << 16,
    LOG_SOURCE_TIMEWHEEL = 1 << 17,
    LOG_SOURCE_SEMAPHORE = 1 << 18,
    LOG_SOURCE_NAMESERVICE = 1 << 19,
    LOG_SOURCE_CONNECTION = 1 << 20,
    LOG_SOURCE_MULTIPLEXER = 1 << 21,
    LOG_SOURCE_ENTITY = 1 << 22,
    LOG_SOURCE_SOCKETOP = 1 << 23,
    LOG_SOURCE_SPLITE3 = 1 << 24,
    LOG_SOURCE_XML = 1 << 25,
    LOG_SOURCE_ENDIAN = 1 << 26,
    LOG_SOURCE_TIMESTAMP = 1 << 27,
    LOG_SOURCE_ERROR = 1 << 28,
    LOG_SOURCE_PLUGIN = 1 << 29,
    LOG_SOURCE_ADDRESS4 = 1 << 30,
    LOG_SOURCE_GUID = 1 << 31,
    LOG_SOURCE_EVENTLOOPTHREAD = 1 << 1,
    LOG_SOURCE_EVENTLOOPTHREADPOOL = 1 << 3
};
>>>>>>> master

////
// @brief
// 输出选项
//
enum
{
    LOG_OUTPUT_TER = 0,
    LOG_OUTPUT_FILE = 1
};

void set_ndsl_log_sinks(int sinks, int file_or_ter);
void ndsl_log_into_sink(int level, int source, const char *format, ...);

#if defined(__cplusplus)
}
#endif

#endif // __NDSL_UTILS_LOG_H__