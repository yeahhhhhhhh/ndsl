/**
 * @file server.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#include <cstdio>
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include "ndsl/net/EventLoop.h"
#include "ndsl/net/TcpConnection.h"
#include "ndsl/net/TcpAcceptor.h"
#include "ndsl/net/SocketAddress.h"
#include "ndsl/config.h"

using namespace ndsl;
using namespace net;
using namespace utils;

#define BUFSIZE 16384

TcpAcceptor *tAc;
uint64_t mlog;
int isStop = false;

static void mError(void *se, int eno);

class Session
{
  private:
    static void onMessage(void *pthis)
    {
        if (!isStop) {
            Session *pThis = static_cast<Session *>(pthis);
            int n;

            if (pThis->len_ > 0)
                if ((n = pThis->conn_->onSend(
                         pThis->buf_, pThis->len_, 0, NULL, NULL)) < 0)
                    LOG(LOG_ERROR_LEVEL, mlog, "send error");

            // 循环注册onRecv

            if ((n = pThis->conn_->onRecv(
                     pThis->buf_, &(pThis->len_), 0, onMessage, pThis)) < 0)
                LOG(LOG_ERROR_LEVEL, mlog, "recv error");
        }
    }

  public:
    // static void onSendMessage(void *conn)
    // {
    //     // LOG(LOG_ERROR_LEVEL, mlog, "send a message");
    // }

    Session(TcpConnection *conn)
        : conn_(conn)
        , len_(0)
    {}
    ~Session() {}

    void start()
    {
        conn_->onError(::mError, this);
        int n = conn_->onRecv(buf_, &len_, 0, onMessage, this);
        if (n < 0) { LOG(LOG_ERROR_LEVEL, mlog, "recv error"); }
    }

    char buf_[BUFSIZE];
    TcpConnection *conn_;
    ssize_t len_;
    // bool isStop_;
};

static void mError(void *se, int eno)
{
    // LOG(LOG_ERROR_LEVEL, mlog, "error");
    Session *session = static_cast<Session *>(se);
    if (eno == 11) {
        // LOG(LOG_ERROR_LEVEL, mlog, "bad error");
        printf("sd\n");
        // session->isStop_ = true;
        isStop = true;
        // 对端断开 释放资源
        session->conn_->pTcpChannel_->erase();

        delete session->conn_;
        delete session;
    }
}

static void onConnection(void *conn)
{
    TcpConnection *Con = static_cast<TcpConnection *>(conn);
    Session *session = new Session(Con);
    session->start();

    TcpConnection *con1 = new TcpConnection();
    tAc->onAccept(con1, NULL, NULL, onConnection, con1);
}

int main(int argc, char *argv[])
{
    printf("main\n");
    // 设置log
    mlog = add_source();
    // set_ndsl_log_sinks(LOG_SOURCE_ALL | mlog, LOG_OUTPUT_FILE);
    set_ndsl_log_sinks(mlog | LOG_SOURCE_TCPCONNECTION, LOG_OUTPUT_TER);

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

        // 线程还没加入 后面加
        int threadCount = atoi(argv[3]);

        // 初始化线程池
        ELThreadpool threadPool;
        threadPool.setMaxThreads(threadCount);

        threadPool.start();

        tAc = new TcpAcceptor(&loop);
        s = tAc->start(servaddr);
        if (s < 0) LOG(LOG_ERROR_LEVEL, mlog, "tAc->start fail");

        TcpConnection *Conn = new TcpConnection();

        tAc->onAccept(Conn, NULL, NULL, onConnection, Conn);

        // 运行
        EventLoop::loop(&loop);

        delete tAc;
    }
}
