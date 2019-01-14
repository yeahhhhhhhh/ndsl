////
// @file UdpEndpoint.h
// @brief
// 
//
// @author lanry
// @email luckylanry@163.com
//
#ifndef __NDSL_NET_UDPENDPOINT_H__
#define __NDSL_NET_UDPENDPOINT_H__
#include <queue>
#include <sys/socket.h>
#include "../utils/Error.h"
#include "UdpChannel.h"
#include "EventLoop.h"

namespace ndsl{
namespace net{

using Callback = void (*)(void *); // Callback 函数指针原型

class  UdpEndpoint
{
  public:
    UdpEndpoint(EventLoop *pLoop);
    ~ UdpEndpoint();

    int sockfd_;
    EventLoop *pLoop_;
    UdpChannel *pUdpChannel_;

    Callback cb_;
    void *param_;
    
  private:
    // 用户调用sendto/recvfrom函数的参数
    typedef struct SInfo
    {
        const void *sendBuf_;               // 用户的发送缓冲区
        void *recvBuf_;                     // 用户的接收缓冲区
        size_t len_;                        // 缓冲区的大小
        int flags_;                         // sendto和recvfrom的参数
        struct sockaddr *dest_addr_;        // 接收数据的用户主机地址
        struct sockaddr *src_addr_;         // 发送数据的用户主机地址
        socklen_t addrlen_;                 // 地址结构的长度
        Callback cb_;                       // 存储用户传来的回调函数
        void *param_;                       // 回调函数的参数
        size_t offset_;                     // 一次没发送完的发送偏移
    }Info,*pInfo;

     struct RecvInfo
    {
        struct sockaddr *addr_; // sockaddr
        socklen_t *addrlen_;    // sockaddr长度
        Callback cb_;           // 回调函数
        void *param_;           // 回调函数参数
    }info;


    std::queue<pInfo> qSendInfo_; // 等待发送的队列
    std::queue<pInfo> qRecvInfo_; // 等待接收的队列
    

  public:
 
    // 创建一个channel,并将fd发给channel,param为用户回调参数
    int createChannel(int sockfd_,Callback cb,void *param); 

    // 客户端连接后的处理
    static int handleRead1(void *);

    // 保存用户信息 填充上面的结构体
    int setInfo(
        struct sockaddr *addr,
        socklen_t *addrlen,
        Callback cb,
        void *param);


    // 事件发生后的处理
    static int handleRead(void *);
    static int handleWrite(void *);

    int onRecv(char *buffer, size_t len, int flags,struct sockaddr *src_addr,socklen_t addrlen,Callback cb, void *param); // recv 接收函数

    int onSend(const void *buf, size_t len, int flags,struct sockaddr *dest_addr_,socklen_t addrlen,Callback cb, void *param); // 用户调用send发送数据
    
    // 清除注册
    int remove();
};

} // namespace net
} //namespace ndsl

#endif // __NDSL_NET_UDPENDPOINT_H__