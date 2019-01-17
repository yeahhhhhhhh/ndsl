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
#include "ndsl/net/SocketAddress.h"
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
TcpAcceptor *tAc;

static void mError(int a, int b) { printf("there is a error\n"); }

static void onSendMessage(void *a) {} // printf("send a message\n"); }

static void onMessage(void *conn)
{
    TcpConnection *con1 = static_cast<TcpConnection *>(conn);
    // printf("server::Message\n");
    // printf("server::Message len = %ld\n", len);
    // printf("%d", con1->pTcpChannel_->getFd());
    if (len > 0) con1->onSend(sbuf, len, 0, onSendMessage, NULL);
    // memset(sbuf, 0, sizeof(sbuf));
}

static void onConnection(void *conn)
{
    // printf("server::onConnection\n");
    TcpConnection *Con = static_cast<TcpConnection *>(conn);

    // printf("server::onConnection sockfd = %d\n", Con->pTcpChannel_->getFd());

    // 初始化
    memset(sbuf, 0, sizeof(sbuf));
    len = 0;
    Con->onRecv(sbuf, &len, 0, onMessage, Con);

    TcpConnection *con1 = new TcpConnection(tAc);
    con1->onAccept(con1, NULL, NULL, onConnection, con1);
}

int main(int argc, char *argv[])
{
    if (argc < 4) {
        fprintf(stderr, "Usage: server <address> <port> <threads>\n");
    } else {
        int s;

        // 初始化EPOLL
        EventLoop loop;
        s = loop.init();
        if (s < 0) printf("loop init fail\n");

        struct SocketAddress4 servaddr(
            argv[1], static_cast<unsigned short>(atoi(argv[2])));

        // TODO: 线程还没加入 后面加
        // int threadCount = atoi(argv[3]);

        tAc = new TcpAcceptor(&loop);
        s = tAc->start(servaddr);
        if (s < 0) printf("tAc->start fail\n");

        // 准备接收的数据结构
        struct sockaddr_in rservaddr;
        bzero(&rservaddr, sizeof(rservaddr));
        socklen_t addrlen;

        // FIXME: 这里只能建立一个连接
        Conn = new TcpConnection(tAc);
        Conn->onError(mError);
        Conn->onAccept(
            Conn, (struct sockaddr *) &rservaddr, &addrlen, onConnection, Conn);

        // 运行
        EventLoop::loop(&loop);
    }
}
