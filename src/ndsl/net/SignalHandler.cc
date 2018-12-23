#include <string.h>
#include <sys/signalfd.h>

#include "SignalHandler.h"

namespace ndsl{
namespace net{

SignalHandler::SignalHandler (EventLoop *pLoop){
	pLoop_ = pLoop;
}

int SignalHandler:;registSignalfd(int signum, Callback handleFunc){
	signum_ = signum;
	handleFunc_ = handleFunc;
	
	sigset_t mask;  
    int sfd;  
    sigemptyset(&mask);  
    sigaddset(&mask, signum);
    
    // 阻塞信号，目的是不以默认的方式处理该信号
    sigprocmask(SIG_BLOCK, &mask, NULL);
    
    sfd = signalfd(-1, &mask, 0);
    
    pSignalChannel_ = new SignalChannel(sfd, pLoop_);
    pSignalChannel_ -> setCallBack(this);
    return pSignalChannel_ -> enableReading();
}

int handleRead(){
	struct signalfd_siginfo fdsi;
	memset(&fdsi, 0, sizeof(struct signalfd_siginfo));
	
	int sfd = pSignalChannel_ -> signalfd_;
	int s = read(sfd, &fdsi, sizeof(struct signalfd_siginfo));
	
	if(s != sizeof(struct signalfd_siginfo)){
		return S_FALSE;
	}
	
	if(fdsi.ssi_signo == signum_){
		handleFunc_();
		return S_OK;
	}else{
		return S_FALSE;
	}
}

int handleWrite(){

}

} // namespace net
} // namespace ndsl
