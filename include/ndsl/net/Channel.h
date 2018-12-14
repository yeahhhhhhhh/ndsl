/**
 * @file Channel.h
 * @brief
 * Channel 基类
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#ifndef __NDSL_NET_CHANNEL_H__
#define __NDSL_NET_CHANNEL_H__
#include "EventLoop.h"

namespace ndsl {
namespace net {

// class ChannelCallBack
// {
//   public:
//     virtual int handleRead() = 0;
//     virtual int handleWrite() {}

//     TcpConnection::handleRead();

//     static void handleRead(void *param)
//     {
//         SomeChannel *pThis = reinterpret_cast<SomeChannel *>(param);
//         ...
//     }
// };

struct Channel
{
    using Callback = void (*)(void *);

  public:
    uint32_t events_;  // 注册事件
    uint32_t revents_; // 发生事件
    EventLoop *ploop_; // 指向EventLoop

    virtual ~Channel() {} // 虚析构函数

    virtual int onRead() = 0;  // read结束回调函数
    virtual int onWrite() = 0; // write结束回调函数

    virtual int handleEvent() = 0; // loop的事件处理函数
    virtual int getFd() = 0;       // rdma的fd在结构内部

    CallBack onRead = NULL;
    Callback onWrite = NULL;
};

} // namespace net
} // namespace ndsl

#endif // __CHANNEL_H__