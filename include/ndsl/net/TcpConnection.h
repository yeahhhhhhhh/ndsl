/**
 * @file TcpConnection.h
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#ifndef __NDSL_NET_TCPCONNECTION_H__
#define __NDSL_NET_TCPCONNECTION_H__
#include <queue>
#include <sys/socket.h>
#include "ndsl/config.h"
#include "ndsl/utils/Log.h"

namespace ndsl {
namespace net {

class TcpChannel;
class EventLoop;
class TcpAcceptor;
class Channel;

class TcpConnection
{
  public:
    using Callback = void (*)(void *); // Callback 函数指针原型
    using ErrorHandle =
        void (*)(int, Channel *); // error回调函数 int errno, Channel*

  private:
    // 用户主动调用onRecv/onSend函数的参数存在这
    typedef struct SInfo
    {
        void *sendBuf_;  // 用户给的写地址
        void *readBuf_;  // 用户给的读地址
        ssize_t *len_;   // buf长度
        int flags_;      // send()的参数在
        Callback cb_;    // 存储用户传过来的回调函数
        void *param_;    // 回调函数的参数
        ssize_t offset_; // 一次没发送完的发送偏移
        bool recvInUse_; // 判断是否已经使用过一次 Proactor要求每次注册
    } Info, *pInfo;

    std::queue<pInfo> qSendInfo_; // 等待发送的队列
    Info RecvInfo_;

    // 存储Acceptor的TcpChannel
    // TcpAcceptor *pTcpAcceptor_;
    // 错误处理的回调函数
    ErrorHandle errorHandle_;

  public:
    TcpConnection();
    TcpConnection(TcpAcceptor *tcpAcceptor);
    ~TcpConnection();

    static int handleRead(void *pthis);
    static int handleWrite(void *pthis);

    // TcpChannel的指针 方便Mulpipleter拿
    TcpChannel *pTcpChannel_;

    // 新建一个Channel
    int createChannel(int sockfd, EventLoop *pLoop);

    // error汇总 注册error回调函数
    int onError(ErrorHandle cb);

    // onSend onRecv 的语义是异步通知
    // 需要调用一次 就是起到一个注册buf和回调的作用
    int onRecv(char *buffer, ssize_t *len, int flags, Callback cb, void *param);

    // 会有好多人同时调用这个进行send，需要一个队列
    int onSend(void *buf, ssize_t len, int flags, Callback cb, void *param);

    // 进程之前相互通信
    int sendMsg(
        int sockfd, // 要不要加?
        struct msghdr *msg,
        int flags,
        Callback cb,
        void *param);
};

} // namespace net
} // namespace ndsl

#endif // __NDSL_NET_TCPCONNECTION_H__