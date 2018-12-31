/**
 * @file MultiplexerTest.cc
 * @brief
 * Multiplexertest
 *
 * @author zzt
 * @email 429834658@qq.com
 */

#include "../catch.hpp"
#include "ndsl/net/Multiplexer.h"
#include "ndsl/net/TcpConnection.h"
#include "ndsl/net/TcpChannel.h"
#include "ndsl/net/EventLoop.h"
#include "ndsl/net/TcpAcceptor.h"
#include <sys/socket.h>

using namespace ndsl;
using namespace net;

int id = 11;
void fun1(char *data, int len);

TEST_CASE("Mutiplexer/cbmaptest")
{
	using Callback = void (*)(char *buffer, int len, int error);
	using CallbackMap = std::map<int, Callback>;


	// 启动服务
    // 初始化EPOLL
    EventLoop loop;
    REQUIRE(loop.init() == S_OK);
    TcpAcceptor *tAc = new TcpAcceptor(&loop);	
	tAc->start();
    // 准备接收的数据结构
    struct sockaddr_in rservaddr;
    bzero(&rservaddr, sizeof(rservaddr));
    socklen_t addrlen;
		
	TcpConnection *Conn = new TcpConnection(tAc);
    Conn->onAccept(Conn, (SA *) &rservaddr, &addrlen, fun1, NULL);

    // 启动一个客户端
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
    connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

    // 添加中断
    loop.quit();
    REQUIRE(loop.loop() == S_OK);

    // 测试是否接收到了客户的连接
    REQUIRE(flag == true);


	CallbackMap cbMap;
	Multiplexer mymulti(conn, cbMap);
	
	SECTION("insert")
	{
		mymulti.insert(id, fun1);
	}
	SECTION("remove")
	{
		mymulti.remove(id);
	}
}