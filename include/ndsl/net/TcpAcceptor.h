/**
 * @file TcpAcceptor.h
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#ifndef __TCPACCEPTOR_H__
#define __TCPACCEPTOR_H__

#include "Channel.h"
#include "TcpChannel.h"
#include "EventLoop.h"

namespace ndsl {
namespace net {

class TcpAcceptor
{
  private:
    int listenfd_;
    EventLoop *pLoop_;
    TcpChannel *pTcpChannel_;
    using Callback = void (*)(void *); // Callback 函数指针原型

    // 测试专用
    Callback cb_;

    // 用于保存用户回调信息
    struct Info
    {
        TcpConnection *pCon_;
        struct sockaddr *addr_;
        socklen_t *addrlen_;
        Callback cb_;
        void *param_;
        bool inUse_; // 判断当前结构体是否有数据
    } info;

  public:
    TcpAcceptor(EventLoop *pLoop);
    ~TcpAcceptor();

    // 测试专用
    TcpAcceptor(Callback cb, EventLoop *pLoop);

    // 为用户主动调用onAcceptor()而生
    TcpAcceptor(
        EventLoop *pLoop,
        TcpConnection *pCon,
        struct sockaddr *addr,
        socklen_t *addrlen,
        Callback cb,
        void *param);

    static int handleRead(void *pthis);
    // int handleWrite();
    int start();

  private:
    int createAndListen();
};

} // namespace net
} // namespace ndsl

#endif // __TCPACCEPTOR_H__