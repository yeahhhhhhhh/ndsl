/**
 * @file TcpConnection.h
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#ifndef __TCPCONNECTION_H__
#define __TCPCONNECTION_H__
#include <queue>
#include "TcpChannel.h"
#include "EventLoop.h"
#include "ChannelCallBack.h"
#include "Multiplexer.h"
#include "../utils/temp_define.h"

namespace ndsl {
namespace net {

class TcpChannel;

class TcpConnection : public ChannelCallBack
{
  private:
    TcpChannel *pTcpChannel_;

    // 用户主动调用onRecv/onSend函数的参数存在这
    typedef struct SSendInfo
    {
        void *buf_;  // 用户给的buf地址
        size_t len_; // buf长度
        int flags_;
        Callback cb_; // 存储用户传过来的回调函数
        void *param_; // 回调函数的参数
        int offset_;  // 一次没发送完的发送偏移
        int *errno_;  // 记录错误码
    } Info, *pInfo;

    Queue<pInfo> qSendInfo_; // 用于保存发送时的各种参数
    Info recvInfo_;          // 用于保存接收时的各种参数

    int createChannel(int sockfd_, EventLoop *pLoop);

  public:
    TcpConnection(int sockfd, EventLoop *pLoop);
    ~TcpConnection();

    int handleRead();
    int handleWrite();

    // 给Multipliter的接口
    int onRecvmsg(char *buf, Callback cb, void *param);

    // onSend onRecv 的语义是异步通知
    int onRecv(char *buffer, int &len, Callback cb, void *param, int &errno);

    // 会有好多人同时调用这个进行send，需要一个队列
    int onSend(
        const void *buf,
        size_t len,
        int flags,
        Callback cb,
        void *param,
        int *errno_);

    // 正常执行accept的流程
    int onAccept(
        TcpConnection *pCon,
        struct sockaddr *addr,
        socklen_t *addrlen,
        Callback cb,
        void *param);
};

} // namespace net
} // namespace ndsl

#endif // __TCPCONNECTION_H__