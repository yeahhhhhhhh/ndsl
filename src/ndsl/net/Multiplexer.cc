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
#include<string.h>
#include "ndsl/net/Multiplexer.h"
#include "ndsl/net/EventLoop.h"

namespace ndsl{
namespace net{

// 在map中插入<id,callback>
static void Multiplexer::insert(void *pa )
{
    struct para *p = static_cast<struct para *>(pa);
	Multiplexer *pthis = p->pthis;

    Multiplexer::CallbackMap::iterator iter=pthis->cbMap_.lower_bound(p->id); // 返回map中第一个不小于id的迭代器指针
    if(iter == pthis->cbMap_.end() || iter->first != p->id){
        pthis->cbMap_.insert(iter,make_pair(p->id,p->cb));
    }

	if (p != NULL) // 释放para
	{
		delete p;
		p = NULL;
	}

	conn_->onRecv(pthis->msghead_, &(pthis->rlen_), pthis->dispatch, (void *)pthis); // 开始接收消息
}

// 在loop工作队列中加入insert任务
void Multiplexer::addInsertWork(int id, Callback cb)
{
    struct para *p = new para; // 在insert()中释放
    p->id = id;
    p->cb = cb;
	p->pthis = this;

    work_struct *w1 = new work_struct; // 在eventloop中释放
    w1->doit = insert;
    w1->para = static_cast<void *>(p);
    conn_.loop_.addWork(w1);
}

// 在map中删除<id,callback>对
static void Multiplexer::remove( void *pa )
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

    work_struct *w2 = new work_struct; // 在eventloop中释放
    w2->doit = remove;
    w2->para = static_cast<void *>(p);
    conn_.loop_.addWork(w2);
}

// 回调，释放已使用的内存
static void Multiplexer::freecb(void &p)
{
	if (p != NULL)
	{
		free(p);
		p = NULL;
	}
}

// 向上层提供发送消息接口
void Multiplexer::sendMessage(int id, int len,char *data)
{
	buffer = (char *)malloc(sizeof(char)*len);  // 在tcpconnection中释放
	Message *message = reinterpret_cast<struct Message *>(buffer);
    message->id = id;
    message->len = len; // 消息头中的len为负载长度
	strcpy(buffer + sizeof(Message), data, len);

	conn_->onSend(buffer, len+sizeof(Message), -1, NULL, NULL);
}

// 分发消息给上层通信实体
static void Multiplexer::dispatch(void *p)
{
	Multiplexer *pthis  = static_cast<Multiplexer *>(p);
    if(pthis->left_ == 0) // 是新任务，处理读取消息头的逻辑
    {
        struct Message *message = reinterpret_cast<struct Message *>(pthis->msghead_);
        pthis->id_ = message->id;
        pthis->len_ = message->len;
		pthis->left_ = pthis->len_;
		pthis->location_ = pthis->msghead_;
	    pthis->rlen_ -=sizeof(int) * 2 // 对rlen_做更新，表示读到的数据长度
		pthis->left_ -= pthis->rlen_; // 对left_做更新
		pthis->location_ += sizeof(int)*2; // 定位到负载

		if (pthis->left_== 0) // 已读完消息
		{
			Multiplexer::CallbackMap::iterator iter = pthis->cbMap_.find(pthis->id_);
			if (iter != pthis->cbMap_.end()) iter->second(pthis->location_, pthis->rlen_, pthis->error_); // 在这里调用了实体对应的回调函数

			pthis->conn_->onRecv(pthis->msghead_, &(pthis->rlen_), pthis->dispatch, (void *)pthis); // 又开始新一轮读取
		}
		else if (pthis->left_ > 0)
		{
            databuf_ = (char *)malloc(sizeof(char) * pthis->len_);  // TODO:释放内存
            memcpy( pthis->databuf_, pthis->location_, pthis->rlen_); // 做一次拷贝开销不大
		    // 原型void *memcpy(void*dest, const void *src, size_t n)
			pthis->location_ = pthis->databuf_;
			pthis->location_ += pthis->rlen_; // location指针向后滑动
			pthis->conn_->onRecv(pthis->location_, &(pthis->rlen_), pthis->dispatch, (void *)pthis);
		}
    }
    else if(pthis->left_ > 0) // 有剩余字节数未读
    {
		pthis->left_ -= pthis->rlen_;
		pthis->location_ += pthis->rlen_; // location指针向后滑动
		if (pthis->left_== 0) // 已读完消息
		{
			Multiplexer::CallbackMap::iterator iter = pthis->cbMap_.find(pthis->id_);
			if (iter != pthis->cbMap_.end()) iter->second(pthis->databuf_, pthis->len_, pthis->error_);

			pthis->conn_->onRecv(pthis->msghead_, &(pthis->rlen_), pthis->dispatch, (void *)pthis); // 又开始新一轮读取
		}
		else if(pthis->left_ > 0) // 继续读取数据
			pthis->conn_->onRecv(pthis->location_, &(pthis->rlen_), pthis->dispatch, (void *)pthis);
    }
}

} // namespace net
} // namespace ndsl
