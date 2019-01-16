////
// @file Dns.h
// @brife
// 异步，带缓存Dns
//
// @author hideinbed
// @email 2364464666@qq.com
//
#ifndef __NDSL_NET_DNS_H_
#define __NDSL_NET_DNS_H_
#include "./BaseChannel.h"

namespace ndsl {
namespace net {
////
// @brief
// dns任务
//
struct ResolveTask;

// Dns
class Dns
{
  private:
    BaseChannel _M_udp; // udp 套接字
    
}
} // namespace net
} // namespace ndsl
#endif // __NDSL_NET_DNS_H_