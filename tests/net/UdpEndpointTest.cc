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

bool flag = false;

void fun1(void *a) { flag = true; }

bool flagsend = false;
static void sendTest(void *a) { flagsend = true; }

bool flagrecv = false;
static void recvTest(void *a) { flagrecv = true; }

bool clientRecv = false;
static void ClientRecvTest(void *a) { clientRecv = true; }

using namespace ndsl::net;

TEST_CASE("net/UdpEndpoint")
{
	SECTION("udp")
	{
		// 初始化EPOLL 服务器 客户端共用一个EPOLL
		EventLoop loop;
		REQUIRE(loop.init() == S_OK);

		// 准备客户端的接受参数 默认全ip接受 端口9877
		//struct SocketAddress4 servaddr("0.0.0.0", SERV_PORT);

		UdpEndpoint *t = new UdpEndpoint(&loop);
		t->start();

		// 准备接收的数据结构
		struct sockaddr_in rservaddr;
		bzero(&rservaddr, sizeof(rservaddr));
		socklen_t addrlen;
		t->onData((SA*)&rservaddr,&addrlen,fun1,NULL);

        UdpEndpoint *pClient;
		// 启动一个客户端
		UdpClient *pCli = new UdpClient();

		REQUIRE((pClient = pCli->begin(&loop))!= NULL);
		
		// 添加中断
		loop.quit();
		REQUIRE(loop.loop(&loop) == S_OK);


		// 测试onSend
		char *sendbuf = (char *)malloc(sizeof(char) * 12);
		strcpy(sendbuf, "hello world\0");
		t->onSend(sendbuf, strlen("hello world"), 0,(struct sockaddr*)&rservaddr,sizeof(rservaddr),sendTest, NULL);
		char recvBuf[15];
		ssize_t recvLen;
		memset(recvBuf, 0, sizeof(recvBuf));
		t->onRecv(recvBuf, &recvLen, 0, (struct sockaddr*)&rservaddr,sizeof(rservaddr),ClientRecvTest, NULL);

		REQUIRE(strcmp("hello world", recvBuf) == 0);
		REQUIRE(flagsend == true);
		REQUIRE(clientRecv == true);

		// 测试onRecv
		memset(recvBuf, 0, sizeof(recvBuf));
		ssize_t len;
		write(pCli->sfd, "hello world", strlen("hello world"));

		REQUIRE(t->onRecv(recvBuf, &len, 0,(struct sockaddr*)&rservaddr,sizeof(rservaddr),recvTest, NULL) == S_OK);
		REQUIRE(len == strlen("hello world"));
		REQUIRE(flagrecv == true);

		// 第二次不需要添加中断
		// loop.quit();
		REQUIRE(loop.loop(&loop) == S_OK);
	}

}
