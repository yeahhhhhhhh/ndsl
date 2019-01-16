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

bool udpTestFlagSend = false;

static void udpSendTest(void *aa) { udpTestFlagSend = true; }

bool udpFlagRecv = false;

static void udpRecvTest(void *aa) { udpFlagRecv = true; }

bool udpClientRecv = false;
static void ClientudpRecvTest(void *aa)
{
    udpClientRecv = true;
}

using namespace ndsl::net;

TEST_CASE("net/UdpEndpoint")
{
	// 初始化EPOLL 服务器 客户端共用一个EPOLL
	EventLoop loop;
	REQUIRE(loop.init() == S_OK);

	UdpEndpoint *t = new UdpEndpoint(&loop);

	SECTION("udp")
	{
		// 准备客户端的接受参数 默认全ip接受 
		struct SocketAddress4 servaddr("0.0.0.0", 6666);

		REQUIRE((t->start(servaddr))== 0);

		// 准备接收的数据结构
		struct sockaddr_in rservaddr;
		bzero(&rservaddr, sizeof(rservaddr));
		socklen_t addrlen;
		addrlen =sizeof(rservaddr);
		
        UdpEndpoint *pClient;
		struct SocketAddress4 cliaddr("127.0.0.1", 6666);
		UdpClient *pCli = new UdpClient();

	    REQUIRE((pClient = pCli->begin(&loop,cliaddr))!= NULL);

		// 测试Send
        char *sendbuf = (char *) malloc(sizeof(char) * 12);
        strcpy(sendbuf, "hello world\0");

        t->onSend(
            sendbuf, strlen("hello world"),0,(struct sockaddr*)&cliaddr,sizeof(cliaddr),udpSendTest, NULL);

        char recvBuf[15];
        ssize_t recvLen;
        memset(recvBuf, 0, sizeof(recvBuf));
        pClient->onRecv(
            recvBuf, &recvLen, 0,(struct sockaddr*)&rservaddr,addrlen,ClientudpRecvTest, NULL);

        // REQUIRE(strcmp("hello world", recvBuf) == 0);

        // REQUIRE(udpTestFlagSend== true);
        // REQUIRE(udpClientRecv == true);

        // 测试onRecv
        memset(recvBuf, 0, sizeof(recvBuf));
        ssize_t len;
        write(pCli->sfd, "hello world", strlen("hello world"));

        REQUIRE(
           t->onRecv(recvBuf, &len,0,(struct sockaddr*)&cliaddr,sizeof(cliaddr),udpRecvTest, NULL) ==
            S_OK);
        // REQUIRE(len == strlen("hello world"));
        // REQUIRE(udpFlagRecv == true);
	}
}