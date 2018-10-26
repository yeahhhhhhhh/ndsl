/**
* @file: Multiplexer.h
* @brief:
*
* 消息分发器，实现不同通信实体对tcp长连接的复用，每个通信实体拥有一个id，
* 将通信实体的id与回调函数作为键值对存入map方便进行检索，回调相应的回调函数。
* 分发器绑定在eventloop上，即 one multiplexer per eventloop.
* 实现功能：
*  1.绑定eventloop
*  2.插入通信实体
*  3.删除通信实体
*  4.dispatch消息
*
* @author: zzt
* @emial:429834658@qq.com
**/

#ifndef __NDSL_NET_MULTIPLEXER_H__
#define __NDSL_NET_MULTIPLEXER_H__

#include <google/protobuf/message.h>
#include <map>
#include <iostream>

#include "ndsl/net/TcpConnection.h"
#include "ndsl/net/MsgHeader.h"
#include "ndsl/net/Eventloop.h"

namespace ndsl{
namespace net{

// 消息回调函数
using MultiplexerCallBack = Boost::function<void (
    const ndsl::net::TcpConnection &conn,
    ndsl::string &buff,
    const ndsl::Timestap time)>;

/**
   typedef Boost::function<void (
   const ndsl::net::TcpConnection &conn,
   ndsl::string &buff,
   const ndsl::Timestap time)> MultiplexerCallBack;
   可读性没有using好
**/

// 回调函数映射
using MultiplexerCallbackMap = std::map<int, MultiplexerCallback>;

// 多路复用类
class Multiplexer
{
  private:
    ndsl::net::Eventloop *loop_; // 绑定的eventloop循环
    MultiplexerCallbackMap cbMap_; // 回调函数映射容器

  public:
    Multiplexer(ndsl::net::EventLoop *loop): loop_(loop) {}

    Multiplexer(ndsl::net::EventLoop *loop,
    const MultiplexerCallbackMap &multiplexerCallBackMap)
    : loop_(loop), cbMap_(multiplexerCallBackMap)

    // 插入id对应的回调函数
    bool insert(ndsl::net::EventLoop *loop, int id, MultiplexerCallback cb);

    // 删除id对应的回调函数
    bool remove(ndsl::net::EventLoop *loop, int id);

    // 发送proto消息
    static void sendProto(
        const ndsl::net::TcpConnection &conn,
        int cmd,
        const ::google::protobuf::Message &message);

    //解析报头，分发消息
    void dispatch(
        const ndsl::net::TcpConnection &conn,
        ndsl::net::Buffer *buff,
        const ndsl::Timestamp time);

};

} // namespace net
} // namespace ndsl

#endif // __NDSL_NET_MULTIPLEXER_H__
