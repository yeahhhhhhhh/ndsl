/** 
* @file: multiplexer.cc
* @brief: 
* 实现功能：
*  1.绑定eventloop
*  2.插入通信实体
*  3.删除通信实体
*  4.dispatch消息
*
* @author: zzt
* @emial:429834658@qq.com
**/

#include "ndsl/net/mutiplexer.h"
#include "ndsl/net/Eventloop.h"

namespace ndsl{
namespace net{

// 在map中插入<id,callback>对
static int Multiplexer::insert( void *pa )
{
    struct para *p = static_cast<struct para *>(pa);

    MultiplexerCallbackMap::iterator iter=cbMap_.lower_bound(p->id); // 返回map中第一个不小于id的迭代器指针
    if(iter == cbMap_.end() || iter->first != p->id){
        cbMap_.insert(iter,make_pair(p->id,p->cb)); // 当map中有这个关键字时，insert操作再插入数据是不会成功的
        return true;
    }
    else{
        return false;
    }
}

// 在loop工作队列中加入insert任务
void Multiplexer::addInsertWork(int id, MultiplexerCallback cb)
{
    para *p = new para; // 为什么要new?
    p->id = id;
    p->cb = cb;

    work_struct *w1 = new work_struct;
    w1->doit = insert;
    w1->para = (void *)p; // 两个参数id,cb 该怎么传进去？
    loop_.addWork(w1);
}

// 在map中删除<id,callback>对
static int Multiplexer::remove( void *i )
{
    int id = static_cast<int>(i);
    cbMap_.erase(id);
    return true;
}

// 在loop工作队列中加入remove任务
void Multiplexer::addRemoveWork(int id)
{
    work_struct *w2 = new work_struct;
    w1->doit = remove;
    w1->para = (void *)id;
    loop_.addWork(w2);
}

// 向上层提供发送消息接口
static void Multiplexer::sendMessage(const ndsl::net::Connection &conn, int id, ndsl::net::Buffer &buffer)
{
    struct Message message;
    message.id = id;
    message.len = buffer.size();
    message.buf = &buffer;

    conn->send(&message); // 调用conn对象的send函数将message发出去
}

// 分发消息给上层通信实体
void Multiplexer::dispatch(const ndsl::net::Connection &conn, struct Message *message, const ndsl::Timestamp time)
{
    if(message.len == message.buf.size())
    {
        MultiplexerCallbackMap::iterator iter = cbMap_.find(message.id);
            if (iter != cbMap_.end()) iter->second(conn, message.buf, time); // 在这里调用了对应的回调函数
    }
}

} // namespace net
} // namespace ndsl