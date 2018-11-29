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

#include <map>
#include <iostream>

#include "ndsl/net/Connection.h" // connection抽象类
#include "ndsl/net/Eventloop.h"
#include "ndsl/net/Buffer.h"

namespace ndsl{
namespace net{
// 自定义消息结构体
struct Message{
    int len; // 消息长度
    int id; // 通信实体的id
    ndsl::net::Buffer *buf; // 数据
}

// 消息回调函数
using MultiplexerCallBack = Boost::function<void (
    const ndsl::net::Connection &conn,
    ndsl::net::Buffer &buff,  // 假设已实现一个buffer类
    const ndsl::Timestamp time)>;

/**
   typedef Boost::function<void (
   const ndsl::net::Connection &conn,
   ndsl::net::Buffer &buff,  
   const ndsl::Timestap time)> MultiplexerCallBack;  
   可读性没有using好  
**/

// 回调函数映射容器
using MultiplexerCallbackMap = std::map<int, MultiplexerCallback>;

// 自定义addwork传入参数结构体
struct para{
    int id;
    MultiplexerCallBack cb;
}

/**
 * @class: Multiplexer
 * @brief:
 * 多路复用类
 **/
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

    // 在loop工作队列中加入insert任务
    void addInsertWork(int id, MultiplexerCallback cb);

    // 在loop工作队列中加入remove任务
    void addRemoveWork(int id);

    // 插入id对应的回调函数
    static int insert(int id, MultiplexerCallback cb);

    // 删除id对应的回调函数
    static int remove(int id);

    // 向上层提供发送消息接口
    static void sendMessage(
        const ndsl::net::Connection &conn,
        int id,
        ndsl::net::Buffer &buffer);
    
    // 分发消息给通信实体
    void dispatch(
        const ndsl::net::Connection &conn,
        struct Message *message,
        const ndsl::Timestamp time);
    
};

} // namespace net
} // namespace ndsl 

#endif // __NDSL_NET_MULTIPLEXER_H__