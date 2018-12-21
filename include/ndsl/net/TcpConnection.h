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
#include <sys/socket.h>
// #include "TcpChannel.h"
// #include "EventLoop.h"
// #include "Channel.h"
#include "../utils/temp_define.h"

namespace ndsl {
namespace net {

class TcpChannel;
class EventLoop;

class TcpConnection
{
  public:
    // TcpChannel *pTcpChannel_;
    using Callback = void (*)(void *); // Callback 函数指针原型

  private:
    // 用户主动调用onRecv/onSend函数的参数存在这
    typedef struct SInfo
    {
        const void *buf_; // 用户给的buf地址
        size_t len_;      // buf长度
        int flags_;
        Callback cb_; // 存储用户传过来的回调函数
        void *param_; // 回调函数的参数
        int offset_;  // 一次没发送完的发送偏移
        int *errno_;  // 记录错误码
    } Info, *pInfo;

    std::queue<pInfo> qSendInfo_; // 等待发送的队列
    std::queue<pInfo> qRecvInfo_; // 等待接收的队列

    TcpChannel *pTcpChannel_;

  public:
    TcpConnection();
    ~TcpConnection();

    static int handleRead();
    static int handleWrite();

    int createChannel(int sockfd_, EventLoop *pLoop);

    // TODO: 给Multipliter的接口 没有实现的必要？
    int onRecvmsg(char *buf, Callback cb, void *param, int &errn);

    // onSend onRecv 的语义是异步通知
    int onRecv(char *buffer, size_t &len, Callback cb, void *param, int &errn);

    // 会有好多人同时调用这个进行send，需要一个队列
    int onSend(
        const void *buf,
        size_t len,
        int flags,
        Callback cb,
        void *param,
        int &errn);

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