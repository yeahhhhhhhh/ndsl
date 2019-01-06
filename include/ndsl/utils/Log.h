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
////
// @brief
// 日志源
//
enum
{
    LOG_SOURCE_EPOLL = 1,
    LOG_SOURCE_THREADPOLL = 2,
    LOG_SOURCE_EVENTLOOP = 4,
    LOG_SOURCE_THREAD = 8,
    LOG_SOURCE_V8ENGINE = 16,
    //LOG_SOURCE_CHANNEL  ,
   // LOG_SOURCE_UDPCHANEEL  , 
   // LOG_SOURCE_TCPCHANNEL  ,
   // LOG_SOURCE_UNIXCHANNEL  ,
  //  LOG_RDMA_CHANNEL  ,
  //  LOG_SOURCE_TIMEFDCHANNEL  ,
   // LOG_SOURCE_SIGNALFDCHANNEL ,
  ///  LOG_SOURCE_DNSCHANNEL  ,
  //  LOG_SOURCE_FILECHANNEL,
   // LOG_SOURCE_TCPACCETPOR  ,
  //  LOG_SOURCE_TCPCONNECTION  ,
  //  LOG_SOURCE_UNIXCONNECTION  ,
  //  LOG_SOURCE_TIMEWHEEL  ,
 ///   LOG_SOURCE_SEMAPHORE  ,
  //  LOG_SOURCE_NAMESERVICE  ,
  //  LOG_SOURCE_CONNECTION  ,
  //  LOG_SOURCE_MULTIPLEXER  ,
  ///  LOG_SOURCE_ENTITY  ,
  ///  LOG_SOURCE_SOCKETOP  ,
  //  LOG_SOURCE_SPLITE3  ,
 //   LOG_SOURCE_XML  ,
  //  LOG_SOURCE_ENDIAN  ,
 ///   LOG_SOURCE_TIMESTAMP  ,
  //  LOG_SOURCE_ERROR  ,
  //  LOG_SOURCE_PLUGIN   ,
  //  LOG_SOURCE_ADDRESS4  ,
  //  LOGZ_SOURCE_GUID  
};
void set_ndsl_log_sinks(int sinks);
void ndsl_log_into_sink(int level,int source, const char *format, ...);

#if defined(__cplusplus)
}
#    endif

#endif // __NDSL_UTILS_LOG_H__