/**
 * @file Multiplexer.h
 * @brief
 *
 * 消息分发器，实现不同通信实体对tcp长连接的复用，每个通信实体拥有一个id，
 * 将通信实体的id与回调函数作为键值对存入map方便进行检索，回调相应的回调函数。
 * 分发器绑定在connection上，即 one multiplexer per connection.
 * 实现功能如下：
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
// 自定义消息结构体
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
    using Callback =
        void (*)(Multiplexer *Multiplexer, char *buffer, int len, int error);

  private:
    // 回调函数映射容器
    using CallbackMap = std::map<int, Callback>;

    ndsl::net::TcpConnection *conn_ = NULL; // 绑定的connection

    int error_ = 0;
    int msghead = 0;
    int changeheadflag = 0;
    int id_;
    int len_; // 负载长度
    int left_ = 0;
    ssize_t rlen_;

    char msg_[sizeof(char) * MAXLINE + sizeof(Message)];
    char *location_ = msg_;
    char *databuf_ = NULL;

  public:
    Multiplexer(ndsl::net::TcpConnection *conn)
        : conn_(conn)
    {
        if (conn_ == NULL)
            LOG(LOG_ERROR_LEVEL,
                LOG_SOURCE_MULTIPLEXER,
                "MULTIPLEXER::MULTIPLEXER conn_ == NULL\n");
        conn_->onRecv(msg_, &rlen_, 0, dispatch, (void *) this);
        conn_->onError(handleErro);
    }

    Multiplexer() {}
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
    void sendMessage(int id, int length, const char *data);

    // 分发消息给通信实体
    static void dispatch(void *p);
    static void handleErro(int, Channel *)
    {
        LOG(LOG_ERROR_LEVEL, LOG_SOURCE_MULTIPLEXER, "ERROR!!!\n");
    }
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
