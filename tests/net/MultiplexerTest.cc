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
#include "ndsl/utils/temp_define.h"
#include <cstring>
#include <arpa/inet.h>
#include <fcntl.h>

using namespace ndsl;
using namespace net;

int id = 11;
static void entitycallbak(char *data, int len, int ero){}

bool flag = false;

void fun1(void *a) { flag = true; }

TEST_CASE("Mutiplexer/cbmaptest")
{
    SECTION("onAccept")
    {
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

	std::map<int, Multiplexer::Callback> cbMap;
	Multiplexer *mymulti = new Multiplexer(Conn, cbMap);
	
	SECTION("addInsertWork")
	{
		mymulti->addInsertWork(id, entitycallbak);
	}
	SECTION("addRemoveWork")
	{
		mymulti->addRemoveWork(id);
	}
    SECTION("insert and remove")
	{
        struct para *p1 = new para; 
        p1->id = id;
        p1->cb = entitycallbak;
	    p1->pthis = mymulti;

		mymulti->insert((void *)p1);
        std::map<int, Multiplexer::Callback>::iterator iter;
        iter = cbMap.find(id);
        REQUIRE(iter != cbMap.end());

        struct para *p2 = new para; 
        p2->id = id;
        p2->cb = entitycallbak;
	    p2->pthis = mymulti;

        mymulti->remove((void *)p2);
        std::map<int, Multiplexer::Callback>::iterator iter2;
        iter2 = cbMap.find(id);
        REQUIRE(iter2 == cbMap.end());
	}
    }
}