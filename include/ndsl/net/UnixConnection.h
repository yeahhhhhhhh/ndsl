////
// @file UnixConnection.h
// @brief 
// fengzhuang unixconnetion
//
// @author ranxiangjun
// @email ranxianshen@gmail.com
//
#ifndef __UNIXCONNECTION_H__
#define __UNIXCONNECTION_H__
#include <queue>
#include <sys/socket.h>
#include "Channel.h"
#include "../utils/temp_define.h"

namespace ndsl {
namespace net {

class UnixChannel;
class EventLoop;
// class ChannelCallBack;

class UnixConnection  // : public ChannelCallBack
{
  public:
    using Callback = void (*)(void *); // Callback 函数指针原型

  private:
    // 用户主动调用onRecv/onSend函数的参数存在这
    typedef struct SInfo
    {
        const void *sendBuf_; // 用户给的写地址
        void *readBuf_;       // 用户给的读地址
        size_t len_;          // buf长度
        int flags_;           // send()的参数
        Callback cb_;         // 存储用户传过来的回调函数
        void *param_;         // 回调函数的参数
        size_t offset_;       // 一次没发送完的发送偏移
        int *errno_;          // 记录错误码
    } Info, *pInfo;

    std::queue<pInfo> qSendInfo_; // 等待发送的队列
    std::queue<pInfo> qRecvInfo_; // 等待接收的队列

    UnixChannel *pUnixChannel_;

  public:
    UnixConnection();
    ~UnixConnection();

    static int handleRead(void*);
    static int handleWrite(void*);

    int createChannel(int sockfd_, EventLoop *pLoop);

    // TODO: 给Multipliter的接口 没有实现的必要？
    int onRecvmsg(char *buf, Callback cb, void *param, int &errn);

    // onSend onRecv 的语义是异步通知
    int onRecv(
        char *buffer,
        size_t &len,
        int flags,
        Callback cb,
        void *param,
        int &errn);

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
        UnixConnection *pCon,
        struct sockaddr *addr,
        socklen_t *addrlen,
        Callback cb,
        void *param);
};

} // namespace net
} // namespace ndsl

#endif // __UNIXCONNECTION_H__
