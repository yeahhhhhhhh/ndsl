/**
* @file SignalfdTest.cc
* @brief
* signalfd测试
*
* @author why
* @email 136046355@qq.com
*/
#include "../catch.hpp"
#include <iostream>

#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <unistd.h>

#include "ndsl/net/EventLoop.h"
#include "ndsl/net/SignalHandler.h"

void aaa(void *p){
	std::cout << "this is SIGCHLD handler!" << std::endl;
}

TEST_CASE("signalfd"){
	// 启动服务
    // 初始化EPOLL
    ndsl::net::EventLoop loop;
    loop.init();
    
    // 初始化signalHandler
    ndsl::net::SignalHandler sh(&loop);
      
	SECTION("regist"){
		
		// 注册SIGCHLD信号
  		REQUIRE(sh.registSignalfd(SIGCHLD, aaa, NULL) == 0);
  		
        if(fork() == 0){
			exit(0);
		}
		
		sleep(1);
		
		// 添加中断
        loop.quit();     
        // 开始loop
        loop.loop(); 
	}
	SECTION("remove"){
	
		REQUIRE(sh.registSignalfd(SIGCHLD, aaa, NULL) == 0);
		
		if(fork() == 0){
			exit(0);
		}
		
		sleep(1);
		
		REQUIRE(sh.remove() == 0);
		
		// 添加中断
        loop.quit();        
        // 开始loop
        loop.loop();
	}
}
