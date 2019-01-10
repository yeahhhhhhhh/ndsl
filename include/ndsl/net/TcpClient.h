/**
 * @file TcpClient.h
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#ifndef __NDSL_NET_TCPCLIENT_H__
#define __NDSL_NET_TCPCLIENT_H__
#include "EventLoop.h"
#include "ndsl/net/TcpConnection.h"

namespace ndsl {
namespace net {

class TcpClient
{
  public:
    TcpClient();
    TcpClient(EventLoop *loop); // pingpong测试用

    int sockfd_;      // 保存sockfd
    EventLoop *loop_; // 保存EventLoop

    // 与服务器建立连接
    TcpConnection *onConnect();

    // 与服务器断开链接
    int disConnect();
};

} // namespace net
} // namespace ndsl

#endif // __NDSL_NET_TCPCLIENT_H__