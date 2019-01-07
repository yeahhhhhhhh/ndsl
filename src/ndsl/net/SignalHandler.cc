#include <string.h>
#include <sys/signalfd.h>
#include <signal.h>

#include "ndsl/net/SignalHandler.h"
#include "ndsl/utils/temp_define.h"

#include <iostream>


namespace ndsl{
namespace net{

SignalHandler::SignalHandler (EventLoop *pLoop){
	pLoop_ = pLoop;
}
SignalHandler::~SignalHandler(){}

int SignalHandler::registSignalfd(int signum, Callback handleFunc, void *p){
	signum_ = signum;
	handleFunc_ = handleFunc;
	p_ = p;
	
	sigset_t mask;  
    int sfd;  
    sigemptyset(&mask);  
    sigaddset(&mask, signum);
    
    // 阻塞信号，目的是不以默认的方式处理该信号
    sigprocmask(SIG_BLOCK, &mask, NULL);
    
    sfd = signalfd(-1, &mask, 0);
    
    pSignalChannel_ = new SignalChannel(sfd, pLoop_);
    pSignalChannel_ -> setCallBack(handleRead, handleWrite, this);
    pSignalChannel_ -> enroll(true);
    return S_OK;
}

int SignalHandler::handleRead(void *pthis){

	struct signalfd_siginfo fdsi;
	memset(&fdsi, 0, sizeof(struct signalfd_siginfo));
	
	SignalHandler *pSignalHandler = (SignalHandler *)(pthis);
	int sfd = pSignalHandler -> pSignalChannel_ -> getFd();
	int s = read(sfd, &fdsi, sizeof(struct signalfd_siginfo));
	
	if(s != sizeof(struct signalfd_siginfo)){
		std::cout << "error!" << std::endl;
		return S_FALSE;
	}
	
	pSignalHandler->handleFunc_(pSignalHandler -> p_);
	return S_OK;
	
}

int SignalHandler::handleWrite(void *pthis){
	return 0;
}

} // namespace net
} // namespace ndsl
