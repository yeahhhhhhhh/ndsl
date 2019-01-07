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
static void Multiplexer::sendMessage(int len, char *message)
{
	/*onSend没有提供分片发送的接口，要求用户将message封装好
    struct Message message;
    message.id = id;
    message.len = len;*/

	conn_->onSend(data, len, -1, NULL, NULL, &errno_); // 调用connection的onSend函数
	//ssize_t onSend(const void *buf, size_t len, int flags, Callback cb, void *param, int &errno);

	conn_->onRecvMsg(msghead_, &rlen_, dispatch, NULL, &errno_); // 注册一个读事件读取消息头部
	// 函数原型 int onRecv(char *buffer, int &len, Callback cb, void *param, int &errno);
}

// 将char转换为int
int Multiplexer::ctoi(char *ch)
{
	int result = 0;
	for (int i = 0; i < 4; i++)
	{
		if (*ch >= '0' && *ch <= '9')
		{
			result = result * 10 + (*ch - '0');
			ch++;
		}
	}
	return result;
}

// 分发消息给上层通信实体
void Multiplexer::dispatch()
{
    if(left_ == 0) // 是新任务，处理读取消息头的逻辑
    {
		/*  这样强转好像有问题
        struct Message *message = reinterpret_cast<struct Message *>(m); 
        id_ = message->id;
        left_ = message->len;
		*/
		location_ = msghead_;
		id_ = ctoi(location_); // 获取msg中的id
		location_ += sizeof(int);
		len_ = ctoi(location_); // 获取msg中的len
		left_ = len_;
		left_ -= (rlen_ - sizeof(int) * 2); // 对left_做更新
		location_ += sizeof(int); // 定位到负载

		if (left_== 0) // 已读完消息
		{
			MultiplexerCallbackMap::iterator iter = cbMap_.find(id_);
			if (iter != cbMap_.end()) iter->second(location_, rlen_ - sizeof(int) * 2, errno_); // 在这里调用了实体对应的回调函数
		}
		else if (left_ > 0)
		{
            databuf_ = (char *)malloc(sizeof(char) * len_);
            memcpy( databuf_, location_, rlen_-sizeof(int)*2 ); // 将后面的数据部分复制到databuf里
		    // 原型void *memcpy(void*dest, const void *src, size_t n)
			location_ = databuf_;
			location_ += rlen_-sizeof(int)*2; // location指针向后滑动
			conn_->onRecvMsg(location_, &rlen_, dispatch, NULL, &errno_);
		}
    }
    else if(left_ > 0) // 有剩余字节数未读
    {
		left_ -= rlen_;
		location_ += rlen_; // location指针向后滑动
		if (left_== 0) // 已读完消息
		{
			MultiplexerCallbackMap::iterator iter = cbMap_.find(id_);
			if (iter != cbMap_.end()) iter->second(databuf_, len_, errno_);
		}
		else if(left_ > 0) // 继续读取数据
			conn_->onRecvMsg(location_, &rlen_, dispatch, NULL, &errno_);
    }
}

} // namespace net
} // namespace ndsl