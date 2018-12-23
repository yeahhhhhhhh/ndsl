/**
* @file SignalChannel.h
* @brief
* SignalChannel头文件
*
* @author why
* @email 136046355@qq.com
*/
#ifndef __SIGNAL_CHANNEL_H__
#define __SIGNAL_CHANNEL_H__

#include "BaseChannel.h"
#include "EventLoop.h"
#include "SignalHandler.h"

namespace ndsl{
namespace net{
class SignalChannel : public BaseChannel{
	public:
	  SignalChannel (int signalfd, EventLoop *loop);
	  virtual ~SignalChannel ();

    private:
	  int signalfd_;
	  SignalHandler *pSignalHander_;
    
    public:
      // epoll事件注册
      int update();
      int regist();
      int del();
      
      // epoll事件管理
      int enableReading();
	  int enableWriting();
	  int disableWriting();
	  int isWriting();
      
      
      int onRead();
      int onWrite();
      
      // 处理事件
      int handleEvent();
      
      // get、set方法
	  int setCallBack(SignalHandler *pSignalHander);
      int getFd();
      int getEvents();
      int setRevents(int revents);
   
};

} // namespace net
} // namespace ndsl




#endif // __SIGNAL_CHANNEL_H__

