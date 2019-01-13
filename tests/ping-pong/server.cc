/**
 * @file server.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */

#include <cstdio>
#include "ndsl/net/EventLoop.h"
#include "ndsl/net/TcpConnection.h"
#include "ndsl/net/TcpAcceptor.h"
#include "ndsl/config.h"
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

using namespace ndsl;
using namespace net;

#define BUFSIZE 16384

TcpConnection *Conn;
char sbuf[BUFSIZE];
ssize_t len;

static void mError(int a, int b) { printf("there is a error\n"); }

static void onSendMessage(void *a) {} // printf("send a message\n"); }

static void onMessage(void *a)
{
    printf("server::Message\n");
    printf("server::Message len = %ld\n", len);
    if (len > 0) Conn->onSend(sbuf, len, 0, onSendMessage, NULL);
}

static void onConnection(void *a)
{
    printf("server::onConnection\n");

    // 初始化
    memset(sbuf, 0, sizeof(sbuf));
    len = 0;

    Conn->onRecv(sbuf, &len, 0, onMessage, NULL);
}

int main()
{
    // 启动服务
    // 初始化EPOLL
    int s;

    EventLoop loop;
    s = loop.init();
    if (s < 0) printf("loop init fail\n");

    TcpAcceptor *tAc = new TcpAcceptor(&loop);
    s = tAc->start();
    if (s < 0) printf("tAc->start fail\n");

    // 准备接收的数据结构
    struct sockaddr_in rservaddr;
    bzero(&rservaddr, sizeof(rservaddr));
    socklen_t addrlen;

    Conn = new TcpConnection(tAc);
    Conn->onError(mError);
    Conn->onAccept(
        Conn, (struct sockaddr *) &rservaddr, &addrlen, onConnection, NULL);

    // 运行
    // loop.loop();
    EventLoop::loop(&loop);
}
