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
#include "ndsl/net/TcpClient.h"
#include "ndsl/utils/Log.h"
#include "ndsl/config.h"
#include "ndsl/utils/Error.h"
#include "ndsl/net/SocketAddress.h"
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

using namespace ndsl;
using namespace net;

bool tcpConnectionTestFlag = false;

void tcpConnectionTestFun1(void *a) { tcpConnectionTestFlag = true; }

bool tcpConnectionTestFlagSend = false;
static void tcpConnectionSendTest(void *a) { tcpConnectionTestFlagSend = true; }

bool tcpConnectionFalgError = false;
static void tcpConnectionisError(int a, int b)
{
    tcpConnectionFalgError = true;
}

bool tcpConnectionFlagRecv = false;
static void tcpConnectionRecvTest(void *a) { tcpConnectionFlagRecv = true; }

bool tcpConnectionClientRecv = false;
static void ClienttcpConnectionRecvTest(void *a)
{
    tcpConnectionClientRecv = true;
}

TEST_CASE("net/TcpConnection(onRecv)")
{
    SECTION("onAccept")
    {
        // 初始化EPOLL 服务器 客户端共用一个EPOLL
        EventLoop loop;
        REQUIRE(loop.init() == S_OK);

        // 准备客户端的接受参数 默认全ip接受 端口6666
        struct SocketAddress4 servaddr("0.0.0.0", 6666);

        TcpAcceptor *tAc = new TcpAcceptor(&loop);
        tAc->start(servaddr);

        // 准备接收的数据结构
        struct sockaddr_in rservaddr;
        bzero(&rservaddr, sizeof(rservaddr));
        socklen_t addrlen;

        // TODO: 逻辑需要再调整，其实Acceptor不需要Connection
        // 可以直接在Acceptor里面弄一个函数 setAcceptInfo() 把信息传进去
        TcpConnection *Conn = new TcpConnection();
        tAc->onAccept(
            Conn, (SA *) &rservaddr, &addrlen, tcpConnectionTestFun1, NULL);

        // 启动一个客户端
        struct SocketAddress4 clientservaddr("127.0.0.1", 6666);
        TcpConnection *pClientConn;
        TcpClient *pCli = new TcpClient();
        REQUIRE(
            (pClientConn = pCli->onConnect(&loop, true, &clientservaddr)) !=
            NULL);

        // 添加中断
        loop.quit();
        REQUIRE(loop.loop(&loop) == S_OK);

        // 测试是否接收到了客户的连接
        REQUIRE(tcpConnectionTestFlag == true);

        // 测试onSend
        Conn->onError(tcpConnectionisError);
        char *sendbuf = (char *) malloc(sizeof(char) * 12);
        strcpy(sendbuf, "hello world\0");
        Conn->onSend(
            sendbuf, strlen("hello world"), 0, tcpConnectionSendTest, NULL);

        char recvBuf[15];
        ssize_t recvLen;
        memset(recvBuf, 0, sizeof(recvBuf));
        pClientConn->onRecv(
            recvBuf, &recvLen, 0, ClienttcpConnectionRecvTest, NULL);

        REQUIRE(strcmp("hello world", recvBuf) == 0);
        REQUIRE(tcpConnectionTestFlagSend == true);
        REQUIRE(tcpConnectionClientRecv == true);

        // 测试onRecv
        memset(recvBuf, 0, sizeof(recvBuf));
        ssize_t len;
        write(pCli->sockfd_, "hello world", strlen("hello world"));

        REQUIRE(
            Conn->onRecv(recvBuf, &len, 0, tcpConnectionRecvTest, NULL) ==
            S_OK);
        REQUIRE(len == strlen("hello world"));
        REQUIRE(tcpConnectionFlagRecv == true);

        // 第二次需要添加中断
        loop.quit();
        REQUIRE(loop.loop(&loop) == S_OK);
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