/**
* @file SignalHandler.h
* @brief
* SignalHandler头文件
*
* @author why
* @email 136046355@qq.com
*/
#ifndef __SIGNALHANDLER_H__
#define __SIGNALHANDLER_H__

#include "SignalChannel.h"
#include "EventLoop.h"

class SignalChannel;

namespace ndsl{
namespace net{

using Callback = void (*)(void *); 

class SignalHandler {
	public:
	  SignalHandler (EventLoop *pLoop);
	  ~SignalHandler ();

    public:
	  SignalChannel *pSignalChannel_;
	  EventLoop *pLoop_;
	  unsigned int signum_; // 信号编号
	  Callback handleFunc_; // 用于信号发生后的用户处理函数
	  void *p_; // 信号发生后用户回调函数的参数
	   
	public:
	  // 将信号生成文件描述符fd，并发送给channel, p为用户回调函数参数
	  int registSignalfd(int signum, Callback handleFunc, void *p);
	  // 移除注册
	  int remove(); 
	  
	  // 事件发生后的处理
	  static int handleRead(void *pthis); 
      static int handleWrite(void *pthis);
	  
};
	
} // namespace net
} // namespace ndsl


#endif // __SIGNALHANDLER_H__

