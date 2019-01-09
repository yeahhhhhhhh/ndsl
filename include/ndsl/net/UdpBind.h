////
// @file UdpBind.h
// @brief
// 
//
// @author lanry
// @email luckylanry@163.com
//
#ifndef __NDSL_NET_UDPBIND_H__
#define __NDSL_NET_UDPBIND_H__
#include <cstring>
#include "UdpChannel.h"
#include "EventLoop.h"

namespace ndsl {
namespace net {

class UdpEndpoint;
class UdpBind
{
  private:
    int sockfd_;
    EventLoop *pLoop_;
    UdpChannel *pUdpChannel_;
	  using Callback = void (*)(void *); //callbak function pointer type
    Callback cb_;

    // 用于保存用户回调信息
    struct Info
    {
        UdpEndpoint *pUdpInfo_;
        struct sockaddr *addr_;
        socklen_t *addrlen_;
        Callback cb_;
        void *param_;
        bool inUse_; // 判断当前结构体是否有数据
    } info;

  public:
    UdpBind(EventLoop *pLoop);
    ~UdpBind();

    static int handleRead(void *);
    int start(); // 开始

  private:
    int create();
};

} // namespace net
} // namespace ndsl

#endif // __NDSL_NET__UDPBIND_H__
