/** 
* @file Multiplexer.cc
* @brief 
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

#include "ndsl/net/Mutiplexer.h"
#include "ndsl/net/Eventloop.h"

namespace ndsl{
namespace net{

// 在map中插入<id,callback>
static void Multiplexer::insert( void *pa )
{
    struct para *p = static_cast<struct para *>(pa);

    MultiplexerCallbackMap::iterator iter=cbMap_.lower_bound(p->id); // 返回map中第一个不小于id的迭代器指针
    if(iter == cbMap_.end() || iter->first != p->id){
        cbMap_.insert(iter,make_pair(p->id,p->cb)); 
    }
}

// 在loop工作队列中加入insert任务
void Multiplexer::addInsertWork(int id, MultiplexerCallback cb)
{
    para *p = new para;
    p->id = id;
    p->cb = cb;

    work_struct *w1 = new work_struct;
    w1->doit = this->insert;
    w1->para = (void *)p;
    conn_.loop_.addWork(w1);
}

// 在map中删除<id,callback>对
static void Multiplexer::remove( void *i )
{
    int id = static_cast<int>(i);
    cbMap_.erase(id);
}

// 在loop工作队列中加入remove任务
void Multiplexer::addRemoveWork(int id)
{
    work_struct *w2 = new work_struct;
    w1->doit = this->remove;
    w1->para = (void *)id;
    conn_.loop_.addWork(w2);
}

// 向上层提供发送消息接口 
static void Multiplexer::sendMessage(int id, int len,char *data)
{
    struct Message message;
    message.id = id;
    message.len = len;

    conn_->send(-1, data, message.len, -1, NULL, NULL); // 调用connection的send函数将message与data分片发出去
    //ssize_t send(int sockfd, const void *buf, size_t len, int flags, Callback cb, void *param);
}

// 分发消息给上层通信实体
void Multiplexer::dispatch(void *m, int rlen)
{
    char *location = static_cast<char *>(m);
    if(left_ == 0) // 是新任务
    {
        struct Message *message = reinterpret_cast<struct Message *>(m); // 这里强转好像有问题
        id_ = message->id;
        left_ = message->len;
        location += 2*sizeof(int); // 后移八个字节，定位到负载
        MultiplexerCallbackMap::iterator iter = cbMap_.find(id_);
            if (iter != cbMap_.end()) iter->second(location, rlen); // 在这里调用了实体对应的回调函数
        left_ = left_-rlen-2*sizeof(int); // 更新剩余字节数,减去message头部
    }
    else if(left_ > 0) // 有剩余字节数未读
    {
        MultiplexerCallbackMap::iterator iter = cbMap_.find(id_);
            if (iter != cbMap_.end()) iter->second(location, rlen); 
        left_ -= rlen;
        if(left_ == 0) id_=0;
    }
}

} // namespace net
} // namespace ndsl