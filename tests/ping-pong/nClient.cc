/**
 * @file nClient.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#include <boost/bind.hpp>
#include <vector>
#include <stdio.h>
#include <cstring>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <atomic>

#include "ndsl/net/EventLoop.h"
#include "ndsl/net/TcpClient.h"
#include "ndsl/net/TcpConnection.h"
#include "ndsl/net/TimeWheel.h"
#include "ndsl/utils/Log.h"
#include "ndsl/utils/EventLoopThreadpool.h"
#include "ndsl/net/SocketAddress.h"

#include <cstdio>

using namespace std;
using namespace ndsl;
using namespace net;
using namespace utils;

class Client;
char *buf; // 接收数据的地址
bool toEnd = false;

class Session
{
  public:
    // Session *session = new Session(threadPool_.getNextLoop(), this);
    Session(EventLoop *loop, Client *owner)
        : client_() // 在这初始化的TcpClient
        , loop_(loop)
        , owner_(owner)
        , bytesRead_(0)
        , bytesWritten_(0)
        , messagesRead_(0)
    {}

    void start();

    void stop();

    int64_t bytesRead() const { return bytesRead_; }

    int64_t messagesRead() const { return messagesRead_; }

  private:
    static void onMessage(void *pthis)
    {
        // printf("nClient::onMessage\n");
        Session *pThis = static_cast<Session *>(pthis);
        pThis->messagesRead_++;
        pThis->bytesRead_ += pThis->len;
        pThis->bytesWritten_ += pThis->len;

        int n;
        if ((n = pThis->conn_->onSend(buf, pThis->len, 0, NULL, NULL)) < 0) {
            printf("nClient::onMessage send fail\n");
        }
    }

  public:
    ssize_t len;
    TcpClient client_;
    EventLoop *loop_;
    TcpConnection *conn_;
    Client *owner_;
    int64_t bytesRead_;
    int64_t bytesWritten_;
    int64_t messagesRead_;
};

class Client
{
  public:
    // Client client(threadPool, blockSize, sessionCount, timeout);
    Client(
        EventLoopThreadpool *threadPool,
        int blockSize,
        int sessionCount,
        int timeout,
        struct SocketAddress4 *servaddr)
        : blockSize_(blockSize)
        , threadPool_(threadPool)
        , sessionCount_(sessionCount)
        , timeout_(timeout)
        , servaddr_(servaddr)
    {
        // 初始化已连接数量
        numConnected_ = 0;

        // new出数据需要的空间
        message_ = (char *) malloc(sizeof(char) * blockSize);

        // 准备发送的数据
        for (int i = 0; i < blockSize; ++i) {
            message_[i] = '1';
        }
        message_[blockSize] = '\0';

        // 准备发送数据
        for (int i = 0; i < sessionCount; ++i) {
            Session *session =
                new Session(threadPool_->getNextEventLoop(), this);
            // 发送数据
            sessions_.push_back(session);
            session->start();
        }
    }

    const char *message() const { return message_; }

    void onConnect()
    {
        // printf("nClient::Client onConnect sessionCount = %d\n",
        // sessionCount_); printf(
        //     "nClient::Client onConnect numConnected = %d\n",
        //     (int) numConnected_);

        // 等所有链接都建立之后 设置定时器 发送数据
        if ((++numConnected_) == sessionCount_) {
            // 提示所有链接已建立 TODO: 等待LOG确认写法
            // LOG(LOG_INFO_LEVEL, LOG_SOURCE_TESTCLIENT, "all connected\n");
            printf("nClient::onConection all connected\n");

            // FIXME:MEMORY LEAK!!!
            EventLoop *loop = new EventLoop;
            loop->init();
            // FIXME:MEMORY LEAK!!!
            EventLoopThread *th0 = new EventLoopThread(loop);
            // EventLoop *loop = threadPool_->getNextEventLoop();

            // 初始化定时器
            TimeWheel *time = new TimeWheel(loop);
            // TimeWheel *time = new TimeWheel(threadPool_->getNextEventLoop());
            // 开始时间轮
            time->start();

            // 初始化定时器任务
            TimeWheel::Task *t = new TimeWheel::Task;
            t->setInterval = timeout_; // 中断
            t->times = 1;
            t->doit = handleTimeout;
            t->param = this;

            // 添加任务
            time->addTask(t);

            th0->run();

            for (vector<Session *>::iterator it = sessions_.begin();
                 it != sessions_.end();
                 ++it) {
                int n;

                if ((n = (*it)->conn_->onSend(
                         message_, blockSize_, 0, NULL, NULL)) < 0) {
                    printf("nClient::onConect send fail\n");
                }
            }
        }
    }

    void onDisconnect()
    {
        if ((--numConnected_) == 0) {
            // TODO:
            // LOG(LOG_INFO_LEVEL, LOG_SOURCE_TESTCLIENT, "all disconnected\n");

            int64_t totalBytesRead = 0;
            int64_t totalMessagesRead = 0;
            for (vector<Session *>::iterator it = sessions_.begin();
                 it != sessions_.end();
                 ++it) {
                totalBytesRead += (*it)->bytesRead();
                totalMessagesRead += (*it)->messagesRead();
            }
            printf(
                "%lf MiB/s throughput\n",
                static_cast<double>(totalBytesRead) / (timeout_ * 1024 * 1024));

            // LOG_WARN << totalBytesRead << " total bytes read";
            // LOG_WARN << totalMessagesRead << " total messages read";
            // LOG_WARN << static_cast<double>(totalBytesRead) /
            //                 static_cast<double>(totalMessagesRead)
            //          << " average message size";
            // LOG_WARN << static_cast<double>(totalBytesRead) /
            //                 (timeout_ * 1024 * 1024)
            //          << " MiB/s throughput";

            toEnd = true;
        }
    }

  private:
    static void handleTimeout(void *pthis)
    {
        // TODO:
        // LOG(LOG_INFO_LEVEL, LOG_SOURCE_TESTCLIENT, "stop\n");

        printf("nClient::handleTimeout\n");

        Client *pThis = static_cast<Client *>(pthis);

        // 计时器时间到
        pThis->threadPool_->quit();

        // 关闭每个链接
        for (vector<Session *>::iterator it = pThis->sessions_.begin();
             it != pThis->sessions_.end();
             ++it) {
            (*it)->stop();
        }
        // std::for_each(
        //     pThis->sessions_.begin(),
        //     pThis->sessions_.end(),
    }

    // EventLoop *loop_;
    int blockSize_;
    // EventLoopThreadPool threadPool_;
    EventLoopThreadpool *threadPool_;
    int sessionCount_;
    int timeout_;
    vector<Session *> sessions_;
    char *message_;
    // 原子操作 C++支持的
    atomic_int numConnected_;

  public:
    struct SocketAddress4 *servaddr_;
};

void Session::start()
{
    printf("nClient::Session start\n");

    // 阻塞建立连接 建立好的之后调用client的onConnect
    // TODO: 确认下端口号是否正确
    // struct SocketAddress4 servaddr("127.0.0.1", 9999);
    conn_ = client_.onConnect(loop_, false, owner_->servaddr_);

    if (conn_ == NULL) { printf("nClient::Session::start onConnect fail\n"); }
    // 将自身的recv函数注册进去
    if (conn_ != NULL) conn_->onRecv(buf, &len, 0, onMessage, this);

    if (conn_ != NULL) owner_->onConnect();

    // if (NULL == conn_) { printf("Session::start conn_ == NULL\n"); }

    // loop跑起来
    // loop_->loop(loop_);

    // printf("Session::start loop already run\n");
}

void Session::stop()
{
    client_.disConnect();
    owner_->onDisconnect();
}

int main(int argc, char *argv[])
{
    if (argc != 7) {
        fprintf(
            stderr,
            "Usage: client <address> <port> <threads> <blocksize> <sessions> "
            "<time>\n");
    } else {
        uint64_t mlog = add_source();
        set_ndsl_log_sinks(mlog, LOG_OUTPUT_TER);

        struct SocketAddress4 *servaddr = new struct SocketAddress4(
            argv[1], static_cast<unsigned short>(atoi(argv[2])));
        int threadCount = atoi(argv[3]);
        int blockSize = atoi(argv[4]);
        int sessionCount = atoi(argv[5]);
        int timeout = atoi(argv[6]);

        // 初始化线程池 设置线程
        EventLoopThreadpool *threadPool = new EventLoopThreadpool();
        threadPool->setMaxThreads(threadCount);

        // 在线程里new一个EventLoop
        // 只是让线程跑起来，里面的EventLoop并没开始循环
        threadPool->start();

        // 将buf的空间new出来 Memory leak
        buf = (char *) malloc(sizeof(char) * blockSize);

        Client client(threadPool, blockSize, sessionCount, timeout, servaddr);
        // ，貌似没有作用
        while (!toEnd)
            ;

        // FIXME: 主线程竟然结束了 !!!!
        printf("main end\n");
    }

    return 0;
}
