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
#include <string.h>
#include "ndsl/net/Multiplexer.h"
#include "ndsl/net/EventLoop.h"
#include "ndsl/net/TcpChannel.h"
//#include "ndsl/utils/Endian.h"
#include <endian.h>

namespace ndsl {
namespace net {

// 在map中插入<id,callback>
void Multiplexer::insert(void *pa)
{
    struct para *p = static_cast<struct para *>(pa);
    Multiplexer *pthis = p->pthis;

    Multiplexer::CallbackMap::iterator iter =
        pthis->cbMap_.lower_bound(p->id); // 返回map中第一个不小于id的迭代器指针
    if (iter == pthis->cbMap_.end() || iter->first != p->id) {
        pthis->cbMap_.insert(std::make_pair(p->id, p->cb));
    }

    if (p != NULL) // 释放para
    {
        delete p;
        p = NULL;
    }
}

// 在loop工作队列中加入insert任务
void Multiplexer::addInsertWork(int id, Callback cb)
{
    struct para *p = new para; // 在insert()中释放
    p->id = id;
    p->cb = cb;
    p->pthis = this;

    EventLoop::WorkItem *w1 = new EventLoop::WorkItem; // 在eventloop中释放
    w1->doit = insert;
    w1->param = static_cast<void *>(p);
    conn_->pTcpChannel_->pLoop_->addWork(w1);
}

// 在map中删除<id,callback>对
void Multiplexer::remove(void *pa)
{
    struct para *p = static_cast<struct para *>(pa);
    int id = p->id;

    p->pthis->cbMap_.erase(id);

    if (p != NULL) // 释放para
    {
        delete p;
        p = NULL;
    }
}

// 在loop工作队列中加入remove任务
void Multiplexer::addRemoveWork(int id)
{
    struct para *p = new para; // 在remove()中释放
    p->id = id;
    p->cb = NULL;
    p->pthis = this;

    EventLoop::WorkItem *w2 = new EventLoop::WorkItem; // 在eventloop中释放
    w2->doit = remove;
    w2->param = static_cast<void *>(p);
    conn_->pTcpChannel_->pLoop_->addWork(w2);
}

// 向上层提供发送消息接口
void Multiplexer::sendMessage(int id, int length, char *data)
{
    char *buffer = (char *) malloc(
        sizeof(int) * 2 + sizeof(char) * length); // 在tcpconnection中释放
    Message *message = reinterpret_cast<struct Message *>(buffer);
    // message->id = ndsl::utils::Endian::hToN32(id);
    // message->len = ndsl::utils::Endian::hToN32(length); //
    // 消息头中的len为负载长度
    message->id = htobe32(id);
    message->len = htobe32(length);

    memcpy(buffer + sizeof(struct Message), data, length);
    printf("before onSend\n");
    conn_->onSend(buffer, length + sizeof(Message), 0, NULL, NULL);
}

/********************
 * 函数： Multiplexer::dispatch
 * 功能：分发消息给上层通信实体
 * 实现逻辑：
 * 1.消息特别长，读一次缓冲区读不完，需要保留left_状态以备下次继续读取
 * 2.消息特别短，读一次缓冲区会读到多个消息，需要根据rlen_和len_进行判断
 * 3.在长消息的最后一次读取时可能会有别的消息在后面，需要根据rlen_进行判断
 ********************/
void Multiplexer::dispatch(void *p)
{
    printf("in the dispatch \n");
    Multiplexer *pthis = static_cast<Multiplexer *>(p);
    if (pthis->left_ == 0) // 是新任务，处理读取消息头的逻辑
    {
        struct Message *message =
            reinterpret_cast<struct Message *>(pthis->location_);
        // pthis->id_ = ndsl::utils::Endian::nToH32(message->id);
        // pthis->len_ = ndsl::utils::Endian::nToH32(message->len);
        pthis->id_ = be32toh(message->id);
        pthis->len_ = be32toh(message->len);

        printf("id:%d, len:%d \n", pthis->id_, pthis->len_);

        pthis->left_ = pthis->len_;
        pthis->rlen_ -= sizeof(int) * 2;     // 对rlen_做更新
        pthis->left_ -= pthis->rlen_;        // 对left_做更新
        pthis->location_ += sizeof(int) * 2; // 定位到负载

        if (pthis->left_ <= 0) // 刚好读完消息 或读完消息后还有别的实体消息
        {
            Multiplexer::CallbackMap::iterator iter =
                pthis->cbMap_.find(pthis->id_);
            if (iter != pthis->cbMap_.end())
                iter->second(
                    pthis->location_,
                    pthis->len_,
                    pthis->error_); // 在这里调用了实体对应的回调函数

            if (pthis->left_ < 0) {
                pthis->rlen_ -= pthis->len_;     //对rlen更新
                pthis->left_ = 0;                //对left_做更新
                pthis->location_ += pthis->len_; // location_指针后移
                dispatch((void *) pthis); // 递归 继续分发缓冲区剩下的消息
            } else {
                pthis->location_ = pthis->msg_;
            }
        } else if (
            pthis->left_ > 0) //没有读完该实体消息，申请一块len_大小的缓冲区
        {
            pthis->databuf_ = (char *) malloc(sizeof(char) * pthis->len_);
            memcpy(
                pthis->databuf_,
                pthis->location_,
                pthis->rlen_); // 做一次拷贝开销不大
            // 原型void *memcpy(void*dest, const void *src, size_t n)

            pthis->location_ = pthis->databuf_;
            pthis->location_ += pthis->rlen_; // location指针向后滑动
        }
    } else if (pthis->left_ > 0) // 有实体消息未读完
    {
        // printf("left=%d, rlen=%d\n", pthis->left_, (int) pthis->rlen_);
        if (pthis->left_ <=
            (int) pthis->rlen_) //刚好读完消息 或读完消息后还有别的实体消息
        {
            memcpy(pthis->location_, pthis->msg_, pthis->left_);
            Multiplexer::CallbackMap::iterator iter =
                pthis->cbMap_.find(pthis->id_);
            if (iter != pthis->cbMap_.end())
                iter->second(pthis->databuf_, pthis->len_, pthis->error_);

            if (pthis->databuf_ != NULL) // 释放新生成的大块databuffer
            {
                free(pthis->databuf_);
                pthis->databuf_ = NULL;
            }

            pthis->location_ = pthis->msg_;
            //重新将location指针指向msg_，读取别的实体消息

            if ((pthis->left_ - pthis->rlen_) <= 0) {
                pthis->rlen_ -= pthis->left_;     //对rlen更新
                pthis->location_ += pthis->left_; // location_指针后移
                pthis->left_ = 0;                 //对left_做更新
                dispatch((void *) pthis); // 递归 继续分发缓冲区剩下的消息
            }
        } else //太太太长了，还没读完
        {
            memcpy(pthis->location_, pthis->msg_, pthis->rlen_);
            pthis->left_ -= pthis->rlen_;
        }
    }
}

} // namespace net
} // namespace ndsl
