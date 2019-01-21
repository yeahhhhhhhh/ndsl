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
uint64_t mlog;

static void mError(int a, int b)
{
    LOG(LOG_ERROR_LEVEL, mlog, "there is a error");
}

static void onSendMessage(void *a) {
} // LOG(LOG_ERROR_LEVEL, mlog, "send a message"); }

static void onMessage(void *conn)
{
    TcpConnection *con1 = static_cast<TcpConnection *>(conn);
    if (len > 0) con1->onSend(sbuf, len, 0, onSendMessage, NULL);
}

static void onConnection(void *conn)
{
    TcpConnection *Con = static_cast<TcpConnection *>(conn);

    // 初始化
    memset(sbuf, 0, sizeof(sbuf));
    len = 0;
    Con->onRecv(sbuf, &len, 0, onMessage, Con);

    TcpConnection *con1 = new TcpConnection();
    tAc->onAccept(con1, NULL, NULL, onConnection, con1);
}

int main(int argc, char *argv[])
{
    // 设置log
    mlog = add_source();
    set_ndsl_log_sinks(mlog, LOG_OUTPUT_TER);

    if (argc < 4) {
        LOG(LOG_ERROR_LEVEL, mlog, "Usage: server <address> <port> <threads>");
    } else {
        int s;

        // 初始化EPOLL
        EventLoop loop;
        s = loop.init();
        if (s < 0) LOG(LOG_ERROR_LEVEL, mlog, "loop init fail");

        struct SocketAddress4 servaddr(
            argv[1], static_cast<unsigned short>(atoi(argv[2])));

        // TODO: 线程还没加入 后面加
        // int threadCount = atoi(argv[3]);

        tAc = new TcpAcceptor(&loop);
        s = tAc->start(servaddr);
        if (s < 0) LOG(LOG_ERROR_LEVEL, mlog, "tAc->start fail");

        // 准备接收的数据结构
        struct sockaddr_in rservaddr;
        bzero(&rservaddr, sizeof(rservaddr));
        socklen_t addrlen;

        Conn = new TcpConnection();
        Conn->onError(mError);
        tAc->onAccept(
            Conn, (struct sockaddr *) &rservaddr, &addrlen, onConnection, Conn);
        // 运行
        EventLoop::loop(&loop);
    }
}
