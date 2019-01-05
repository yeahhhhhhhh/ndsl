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
#include "ndsl/utils/temp_define.h"

namespace ndsl {
namespace net {

class TcpChannel;
class EventLoop;
class TcpAcceptor;

class TcpConnection
{
  public:
    using Callback = void (*)(void *);      // Callback 函数指针原型
    using ErrorHandle = void (*)(int, int); // error回调函数

  private:
    // 用户主动调用onRecv/onSend函数的参数存在这
    typedef struct SInfo
    {
        void *sendBuf_; // 用户给的写地址
        void *readBuf_; // 用户给的读地址
        size_t *len_;   // buf长度
        int flags_;     // send()的参数
        Callback cb_;   // 存储用户传过来的回调函数
        void *param_;   // 回调函数的参数
        size_t offset_; // 一次没发送完的发送偏移
    } Info, *pInfo;

    std::queue<pInfo> qSendInfo_; // 等待发送的队列
    Info RecvInfo_;

    // 存储Acceptor的TcpChannel
    TcpAcceptor *pTcpAcceptor_;
    // 错误处理的回调函数
    ErrorHandle errorHandle_;

  public:
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
    int onRecv(char *buffer, size_t *len, int flags, Callback cb, void *param);

    // 会有好多人同时调用这个进行send，需要一个队列
    int onSend(void *buf, size_t len, int flags, Callback cb, void *param);

    // 准备接收一个新连接
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