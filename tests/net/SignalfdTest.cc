#include "test.h"
#include "Guid.h"
#include <iostream>
#include "ndsl/net/EventLoop.h"
#include "ndsl/net/Epoll.h"

void aaa(){
	std::cout << "aaa()" std::endl;
}

TEST_CASE("signalfd"){
	SECTION("regist"){
		// 初始化EPOLL
        Epoll ep;
        ep.init();
        EventLoop loop(&ep);
        
        //signalfdHandler
        SignalHandler signalHandler(&loop);
        registSignalfd(2, aaa);
	}
}
