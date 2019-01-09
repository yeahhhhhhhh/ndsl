/**
 * @file TcpClient.h
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#ifndef __NDSL_NET_TCPCLIENT_H__
#define __NDSL_NET_TCPCLIENT_H__
#include "TcpChannel.h"
#include "EventLoop.h"
#include "ndsl/net/SocketAddress.h"
#include <errno.h>
#include <unistd.h>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>

namespace ndsl {
namespace net {

class TcpClient
{
  public:
    TcpChannel *pTcpChannel_;        // 用来保存TcpChannel
    struct SocketAddress4 servaddr_; // 保存链接信息

    using Callback = void (*)(void *);      // 回调函数指针原型
    using ErrorHandle = void (*)(int, int); // error回调函数

    // 链接完成回调函数
    Callback onConnect_;
    // 错误处理的回调函数
    ErrorHandle errorHandle_;

    // 与Channel建立联系 方便加入到EventLoop
    int createChannel(int sockfd, EventLoop *pLoop);

    // 处理第一次没完成的connect
    static int handleConnect(void *pthis);

    // 处理来消息的情况
    static int handleRead(void *pthis);

    // 设置错误处理函数
    int onError(ErrorHandle cb);

    // 与服务器建立连接
    int onConnect(Callback cb);

    // 与服务器断开链接
    int disConnect();
};

} // namespace net
} // namespace ndsl

#endif // __NDSL_NET_TCPCLIENT_H__