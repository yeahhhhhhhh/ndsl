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

class TcpAcceptor : public ChannelCallBack
{
  private:
    int listenfd_;
    EventLoop *pLoop_;
    TcpChannel *pTcpChannel_;
    Callback cb_;
    void *param_;

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
    TcpAcceptor(int listenfd, EventLoop *pLoop);
    ~TcpAcceptor();

    // 为用户主动调用onAcceptor()而生
    TcpAcceptor(
        int listenfd,
        EventLoop *pLoop,
        TcpConnection *pCon,
        struct sockaddr *addr,
        socklen_t *addrlen,
        Callback cb,
        void *param);

    int handleRead();
    int handleWrite();
    int start();

  private:
    int createAndListen();
};

} // namespace net
} // namespace ndsl

#endif // __TCPACCEPTOR_H__