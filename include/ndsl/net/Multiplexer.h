/**
 * @file Multiplexer.h
 * @brief
 *
 * 消息分发器，实现不同通信实体对tcp长连接的复用，每个通信实体拥有一个id，
 * 将通信实体的id与回调函数作为键值对存入map方便进行检索，回调相应的回调函数。
 * 分发器绑定在connection上，即 one multiplexer per connection.
 * 实现功能：
 *  1.绑定connection
 *  2.插入通信实体
 *  3.删除通信实体
 *  4.发送消息
 *  5.分发消息给实体
 *
 * @author zzt
 * @emial 429834658@qq.com
 **/

#ifndef __NDSL_NET_MULTIPLEXER_H__
#define __NDSL_NET_MULTIPLEXER_H__

#include <map>
#include <iostream>
//#include "ndsl/net/Connection.h" // connection抽象类
#include "ndsl/net/TcpConnection.h"
//#include "ndsl/net/EventLoop.h"
namespace ndsl {
namespace net {
// 自定义消息结构体 TODO 小序
#pragma pack(push)
#pragma pack(1) // 一字节对齐
struct Message
{
    int id;  // 通信实体的id
    int len; // 负载长度
};
#pragma pack(pop)

/**
 * @class: Multiplexer
 * @brief:
 * 多路复用类
 **/
class Multiplexer
{
  public:
    // 定义消息回调函数
    using Callback = void (*)(char *buffer, int len, int error);

  private:
    // 回调函数映射容器
    using CallbackMap = std::map<int, Callback>;

    ndsl::net::TcpConnection *conn_; // 绑定的connection

    int error_;
    int id_;
    int len_; // 负载长度
    size_t left_;
    size_t rlen_;

    char msg_[sizeof(char) * MAXLINE];
    char *databuf_ = NULL;
    char *location_ = msg_;

  public:
    Multiplexer(ndsl::net::TcpConnection *conn)
        : conn_(conn)
    {
      conn_->onRecv(msg_, rlen_, 0, dispatch, (void *)this);
    }
    CallbackMap cbMap_; // 回调函数映射容器
    // 在loop工作队列中加入insert任务
    void addInsertWork(int id, Callback cb);

    // 在loop工作队列中加入remove任务
    void addRemoveWork(int id);

    // 插入id对应的回调函数
    static void insert(void *pa);

    // 删除id对应的回调函数
    static void remove(void *pa);

    // 向上层提供发送消息接口
    void sendMessage(int id, int length, char *data);

    // 分发消息给通信实体
    static void dispatch(void *p);

  private:
    // 回调，释放已使用的内存
    void freecb(void *p);
};

// 自定义addwork传入的参数结构体
struct para
{
    Multiplexer *pthis;
    int id;
    ndsl::net::Multiplexer::Callback cb;
};

} // namespace net
} // namespace ndsl

#endif // __NDSL_NET_MULTIPLEXER_H__
