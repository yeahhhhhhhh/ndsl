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

namespace ndsl{
namespace net{

using Callback = void (*)(void *); 

class SignalHandler {
	public:
	  SignalHandler (EventLoop *pLoop);
	  virtual ~SignalHandler ();

    private:
	  SignalChannel *pSignalChannel_;
	  EventLoop *pLoop_;
	  int signum_; // 信号编号
	  Callback handleFunc_; // 用于信号发生后的处理函数
	   
	public:
	  int registSignalfd(int signum); // 将信号生成文件描述符fd，并发送给channel
	  int handleRead(); // 事件发生后的处理
      int handleWrite();
	  
};
	
} // namespace net
} // namespace ndsl


#endif // __SIGNALHANDLER_H__

