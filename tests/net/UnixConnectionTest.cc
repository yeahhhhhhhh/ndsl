/**
 * @file TcpConnectionTest.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "ndsl/net/EventLoop.h"
#include "ndsl/net/Epoll.h"
#include "ndsl/net/UnixChannel.h"
#include "ndsl/net/UnixConnection.h"
#include "ndsl/net/UnixAcceptor.h"
#include "ndsl/utils/temp_define.h"
#include "ndsl/net/SocketAddressUn.h"
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <sys/un.h>

using namespace ndsl;
using namespace net;

bool flag = false;

void fun1(void *a) { flag = true; }

bool flagsend = false;
static void sendTest(void *a) { flagsend = true; }

bool flagerror = false;
static void iserror(int a, int b) { flagerror = true; }

bool flagrecv = false;
static void recvTest(void *a) { flagrecv = true; }

TEST_CASE("net/TcpConnection(onRecv)")
{
    SECTION("onAccept")
    {
        // 启动服务
        // 初始化EPOLL
        EventLoop loop;
        REQUIRE(loop.init() == S_OK);

        UnixAcceptor *tAc = new UnixAcceptor(&loop);
        tAc->start("/mnt/unixsocket/test");

        // 准备接收的数据结构
        // struct sockaddr_un rservaddr;
        // bzero(&rservaddr, sizeof(rservaddr));
		SocketAddressUn rservaddr;
        socklen_t addrlen;

        UnixConnection *Conn = new UnixConnection(tAc);
        Conn->onAccept(Conn, (SA *) &rservaddr, &addrlen, fun1, NULL);

        // 启动一个客户端
        int sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
        // struct sockaddr_in servaddr;
        // bzero(&servaddr, sizeof(servaddr));
        // servaddr.sin_family = AF_INET;
        // servaddr.sin_port = htons(SERV_PORT);
        // inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
		SocketAddressUn servaddr("/mnt/unixsocket/test");
        connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

        // 添加中断
        loop.quit();
        REQUIRE(loop.loop() == S_OK);

        // 测试是否接收到了客户的连接
        REQUIRE(flag == true);

        // 测试onSend
        Conn->onError(iserror);
        Conn->onSend("hello world", sizeof("hello world"), 0, sendTest, NULL);

        char recvBuf[15];
        memset(recvBuf, 0, sizeof(recvBuf));
        read(sockfd, recvBuf, MAXLINE);

        REQUIRE(strcmp("hello world", recvBuf) == 0);
        REQUIRE(flagsend == true);

        // 测试onRecv
        memset(recvBuf, 0, sizeof(recvBuf));
        size_t len;
        write(sockfd, "hello world", sizeof("hello world"));

        REQUIRE(Conn->onRecv(recvBuf, len, 0, recvTest, NULL) == S_OK);
        REQUIRE(flagrecv == true);

        // 第二次不需要添加中断
        REQUIRE(loop.loop() == S_OK);
    }

    // TODO: handleRead handleWrite 好像没法测
    // SECTION("onRecv onSecd handleRead hanleWrite")
    // {
    //     // 启动服务
    //     // 初始化EPOLL
    //     EventLoop loop;
    //     REQUIRE(loop.init() == S_OK);
    // }
}
