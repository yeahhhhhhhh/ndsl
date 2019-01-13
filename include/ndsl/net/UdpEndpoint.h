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
#include "../utils/temp_define.h"

namespace ndsl{
namespace net{

class UdpChannel;
class EventLoop;

class  UdpEndpoint
{
  public:
    using Callback = void (*)(void *); // Callback 函数指针原型
    using ErrorHandle = void (*)(int,int); // error callbak function
  
  private:
    // 用户调用sendto/recvfrom函数的参数
    typedef struct SInfo
    {
        const void *sendBuf_;               // 用户的发送缓冲区
        void *recvBuf_;                     // 用户的接收缓冲区
        size_t len_;                        // 缓冲区的大小
        int flags_;                         // sendto和recvfrom的参数
        struct sockaddr *dest_addr_;  // 接收数据的用户主机地址
        struct sockaddr *src_addr_;         // 发送数据的用户主机地址
        // const struct sockaddr *dest_addr_;  // 接收数据的用户主机地址
        // struct sockaddr *src_addr_;         // 发送数据的用户主机地址
        socklen_t addrlen_;                 // 地址结构的长度
        Callback cb_;                       // 存储用户传来的回调函数
        void *param_;                       // 回调函数的参数
        size_t offset_;                     // 一次没发送完的发送偏移
    } Info,*pInfo;

    std::queue<pInfo> qSendInfo_; // 等待发送的队列
    std::queue<pInfo> qRecvInfo_; // 等待接收的队列

    UdpChannel *pUdpChannel_;
    ErrorHandle errorHandle_;

  public:
    UdpEndpoint();
    ~ UdpEndpoint();
    
    UdpChannel *getUdpChannel();

    static int handleRead(void *);
    static int handleWrite(void *);

    int createChannel(int sockfd_,EventLoop *pLoop); // create a channel
	
	  int onError(ErrorHandle cb); // error summary, register callback function of error

    int recv(char *buffer, size_t len, int flags,struct sockaddr *src_addr,socklen_t addrlen,Callback cb, void *param); // onSend onRecv 的语义是异步通知

    int send(const void *buf, size_t len, int flags,struct sockaddr *dest_addr_,socklen_t addrlen,Callback cb, void *param); // 多用户调用

    // // 正常执行accept的流程
    // int onAccept(
    //     UdpEndpoint *pCon,
    //     struct sockaddr *addr,
    //     socklen_t *addrlen,
    //     Callback cb,
    //     void *param);
};

} // namespace net
} //namespace ndsl

#endif // __NDSL_NET_UDPENDPOINT_H__