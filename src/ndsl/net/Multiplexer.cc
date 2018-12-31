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
#include "ndsl/net/Mutiplexer.h"
#include "ndsl/net/Eventloop.h"

namespace ndsl{
namespace net{

// 在map中插入<id,callback>
static void Multiplexer::insert( void *pa )
{
    struct para *p = reinterpret_cast<struct para *>(pa);

    MultiplexerCallbackMap::iterator iter=cbMap_.lower_bound(p->id); // 返回map中第一个不小于id的迭代器指针
    if(iter == cbMap_.end() || iter->first != p->id){
        cbMap_.insert(iter,make_pair(p->id,p->cb)); 
    }

	if (p != NULL)
	{
		delete p;
		p = NULL;
	}

	conn_->onRecv(msghead_, &rlen_, dispatch, NULL); // 开始接收消息
}

// 在loop工作队列中加入insert任务
void Multiplexer::addInsertWork(int id, MultiplexerCallback cb)
{
    para *p = new para; // 在insert()中释放
    p->id = id;
    p->cb = cb;

    work_struct *w1 = new work_struct; // 在eventloop中释放
    w1->doit = insert;
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
    work_struct *w2 = new work_struct; // 在eventloop中释放
    w1->doit = remove;
    w1->para = (void *)id;
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
static void Multiplexer::sendMessage(int id, int len,char *data)
{
	buffer = (char *)malloc(sizeof(char)*len);  // TODO:释放内存
	Message *message = reinterpret_cast<struct Message *>(buffer);
    message->id = id;
    message->len = len; // 消息头中的len为负载长度
	strcpy(buffer + sizeof(Message), data, len);

	conn_->onSend(buffer, len+sizeof(Message), -1, freecb, NULL);
}

// 分发消息给上层通信实体
void Multiplexer::dispatch()
{
    if(left_ == 0) // 是新任务，处理读取消息头的逻辑
    {
        struct Message *message = reinterpret_cast<struct Message *>(msghead_);
        id_ = message->id;
        len_ = message->len;
		left_ = len_;
		location_ = msghead_;
	    rlen_ -=sizeof(int) * 2 // 对rlen_做更新，表示读到的数据长度
		left_ -= rlen_; // 对left_做更新
		location_ += sizeof(int)*2; // 定位到负载

		if (left_== 0) // 已读完消息
		{
			MultiplexerCallbackMap::iterator iter = cbMap_.find(id_);
			if (iter != cbMap_.end()) iter->second(location_, rlen_, error_); // 在这里调用了实体对应的回调函数
			
			conn_->onRecv(msghead_, &rlen_, dispatch, NULL); // 又开始新一轮读取
		}
		else if (left_ > 0)
		{
            databuf_ = (char *)malloc(sizeof(char) * len_);  // TODO:释放内存
            memcpy( databuf_, location_, rlen_); // 做一次拷贝开销不大
		    // 原型void *memcpy(void*dest, const void *src, size_t n)
			location_ = databuf_;
			location_ += rlen_; // location指针向后滑动
			conn_->onRecv(location_, &rlen_, dispatch, NULL);
		}
    }
    else if(left_ > 0) // 有剩余字节数未读
    {
		left_ -= rlen_;
		location_ += rlen_; // location指针向后滑动
		if (left_== 0) // 已读完消息
		{
			MultiplexerCallbackMap::iterator iter = cbMap_.find(id_);
			if (iter != cbMap_.end()) iter->second(databuf_, len_, error_);
			
			conn_->onRecv(msghead_, &rlen_, dispatch, NULL); // 又开始新一轮读取
		}
		else if(left_ > 0) // 继续读取数据
			conn_->onRecv(location_, &rlen_, dispatch, NULL);
    }
}

} // namespace net
} // namespace ndsl