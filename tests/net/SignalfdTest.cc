#include "test.h"
#include <iostream>
#include "ndsl/net/EventLoop.h"
#include "ndsl/net/SignalHandler.h"

void aaa(void *p){
	std::cout << "ctrl+c false!" << std::endl;
}

TEST_CASE("signalfd"){
	SECTION("regist"){
		// 启动服务
        // 初始化EPOLL
        ndsl::net::EventLoop loop;
        REQUIRE(loop.init() == 0);
        
        ndsl::net::SignalHandler sh(&loop);
        sh.registSignalfd(2, aaa, NULL);
        
        std::cout << "start listen ctrl+c ..." << std::endl;
        
        // 开始loop
        loop.loop();
        
        // 添加中断
        loop.quit();
        REQUIRE(loop.loop() == 0);
	}
}
