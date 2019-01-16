////
// @file UdpEndpointTest.cc
// @brief
// 测试UdpEndpoint
//
// @author lanyue
// @email luckylanry@163.com 
//

#include "../catch.hpp"
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include "ndsl/net/EventLoop.h"
#include "ndsl/net/UdpChannel.h"
#include "ndsl/net/UdpEndpoint.h"
#include "ndsl/net/Epoll.h"
#include "ndsl/net/UdpClient.h"
#include "ndsl/net/SocketAddress.h"

bool flag_ = false;

static void sign(void *aa) { flag_ = true; }

using namespace ndsl::net;

TEST_CASE("net/UdpEndpoint")
{
	// 初始化EPOLL 服务器 客户端共用一个EPOLL
	EventLoop loop;
	REQUIRE(loop.init() == S_OK);
	int s = socket(AF_INET,SOCK_DGRAM,0);
	UdpEndpoint *t = new UdpEndpoint(&loop);

	SECTION("udp")
	{
		// 准备客户端的接受参数 默认全ip接受 端口9877
		struct SocketAddress4 servaddr("0.0.0.0", 6666);

		t->start(servaddr);

		// 准备接收的数据结构
		struct sockaddr_in rservaddr;
		bzero(&rservaddr, sizeof(rservaddr));
		socklen_t addrlen;
 
		REQUIRE((t->setInfo((SA *)&rservaddr,&addrlen,sign,NULL))==0);
		
        UdpEndpoint *pClient;
		struct SocketAddress4 cliservaddr("127.0.0.1", 6666);
		UdpClient *pCli = new UdpClient();

		REQUIRE((pClient = pCli->begin(&loop,cliservaddr))!= NULL);
	}

	SECTION("注册udpchannel"){
		
  		REQUIRE(t->createChannel(s,&loop)== 0);
  		
        if(fork() == 0){
			exit(0);
		}
		
		// sleep(1);
		
		// // 添加中断
        // loop.quit();     
        // // 开始loop
        // loop.loop(&loop); 
	}

}
