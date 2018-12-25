/**
 * @file TcpAcceptor.h
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#ifndef __TCPACCEPTOR_H__
#define __TCPACCEPTOR_H__

#include "TcpChannel.h"
#include "EventLoop.h"

namespace ndsl {
namespace net {

class TcpConnection;

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

    // TcpConnection用
    TcpChannel *getTcpChannel();

    // 保存用户信息
    int setInfo(
        TcpConnection *pCon,
        struct sockaddr *addr,
        socklen_t *addrlen,
        Callback cb,
        void *param);

    static int handleRead(void *pthis);
    int start();

  private:
    int createAndListen();
};

} // namespace net
} // namespace ndsl

#endif // __TCPACCEPTOR_H__