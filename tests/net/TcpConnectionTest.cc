/**
 * @file TcpConnectionTest.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#include "../catch.hpp"
#include "ndsl/net/EventLoop.h"
#include "ndsl/net/Epoll.h"
#include "ndsl/net/TcpChannel.h"
#include "ndsl/net/TcpConnection.h"
#include "ndsl/net/TcpAcceptor.h"
#include "ndsl/utils/temp_define.h"
#include "ndsl/net/TcpClient.h"
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

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

        TcpAcceptor *tAc = new TcpAcceptor(&loop);
        tAc->start();

        // 准备接收的数据结构
        struct sockaddr_in rservaddr;
        bzero(&rservaddr, sizeof(rservaddr));
        socklen_t addrlen;

        TcpConnection *Conn = new TcpConnection(tAc);
        Conn->onAccept(Conn, (SA *) &rservaddr, &addrlen, fun1, NULL);

        // 启动一个客户端
        TcpClient *pCli = new TcpClient();
        REQUIRE(pCli->onConnect() == S_OK);

        // 添加中断
        loop.quit();
        REQUIRE(loop.loop() == S_OK);

        // 测试是否接收到了客户的连接
        REQUIRE(flag == true);

        // 测试onSend
        Conn->onError(iserror);
        char *sendbuf = (char *) malloc(sizeof(char) * 12);
        // sendbuf = 'hello world';
        strcpy(sendbuf, "hello world\0");
        Conn->onSend(sendbuf, strlen("hello world"), 0, sendTest, NULL);

        char recvBuf[15];
        memset(recvBuf, 0, sizeof(recvBuf));
        read(pCli->sockfd_, recvBuf, MAXLINE);

        REQUIRE(strcmp("hello world", recvBuf) == 0);
        REQUIRE(flagsend == true);

        // 测试onRecv
        memset(recvBuf, 0, sizeof(recvBuf));
        size_t len;
        write(pCli->sockfd_, "hello world", strlen("hello world"));

        REQUIRE(Conn->onRecv(recvBuf, &len, 0, recvTest, NULL) == S_OK);
        REQUIRE(len == strlen("hello world"));
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