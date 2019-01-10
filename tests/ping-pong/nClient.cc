/**
 * @file nClient.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#include <boost/bind.hpp>
#include <boost/ptr_container/ptr_vector.hpp>
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

using namespace std;
using namespace ndsl;
using namespace net;

class Client;
char *buf; // 接收数据的地址

class Session
{
  public:
    // Session *session = new Session(threadPool_.getNextLoop(), this);
    Session(EventLoop *loop, Client *owner)
        : client_(loop)
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
        Session *pThis = static_cast<Session *>(pthis);
        pThis->messagesRead_++;
        pThis->bytesRead_ += pThis->len;
        pThis->bytesWritten_ += pThis->len;
        pThis->conn_->onSend(buf, pThis->len, 0, NULL, NULL);
    }

  public:
    int64_t len;
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
    Client(
        EventLoop *loop,
        int blockSize,
        int sessionCount,
        int timeout,
        int threadCount)
        : loop_(loop)
        , blockSize_(blockSize)
        // , threadPool_(loop)
        , sessionCount_(sessionCount)
        , timeout_(timeout)
    {
        // TODO: 初始化定时器 线程池未完成 暂时挂起
        TimeWheel *time = new TimeWheel(threadPool_.getNextLoop());
        time->init();

        // 初始化定时器任务
        struct Task t;
        t->setInterval = 60;
        t->times = 1;
        t->doit = handleTimeout;
        t->param = this;

        // 添加任务
        time->addTask(t);

        // 开始时间轮
        time->start();

        // 设置线程 如果是多线程的话 在这里new一个线程池出来
        // if (threadCount > 1) { threadPool_.setThreadNum(threadCount); }
        // threadPool_.start();

        // new出数据需要的空间
        message_ = (char *) malloc(sizeof(char) * blockSize);

        // 准备发送的数据
        for (int i = 0; i < blockSize; ++i) {
            message_[i] = static_cast<char>(i % 128);
        }

        // 准备发送数据
        for (int i = 0; i < sessionCount; ++i) {
            // TODO: 得看线程池是怎么实现的
            // Session *session = new Session(threadPool_.getNextLoop(), this);
            // 发送数据
            // session->start();
            // sessions_.push_back(session);
        }
    }

    const char *message() const { return message_; }

    void onConnect()
    {
        // 等所有链接都建立之后 设置定时器 发送数据
        if ((++numConnected_) == sessionCount_) {
            // 提示所有链接已建立 TODO: 换成自己的log
            // LOG_WARN << "all connected";

            for (boost::ptr_vector<Session>::iterator it = sessions_.begin();
                 it != sessions_.end();
                 ++it) {
                it->conn_->onSend(message_, blockSize_, 0, NULL, NULL);
            }
        }
    }

    void onDisconnect()
    {
        if ((--numConnected_) == 0) {
            // TODO:
            // LOG_WARN << "all disconnected";

            int64_t totalBytesRead = 0;
            int64_t totalMessagesRead = 0;
            for (boost::ptr_vector<Session>::iterator it = sessions_.begin();
                 it != sessions_.end();
                 ++it) {
                totalBytesRead += it->bytesRead();
                totalMessagesRead += it->messagesRead();
            }
            // LOG_WARN << totalBytesRead << " total bytes read";
            // LOG_WARN << totalMessagesRead << " total messages read";
            // LOG_WARN << static_cast<double>(totalBytesRead) /
            //                 static_cast<double>(totalMessagesRead)
            //          << " average message size";
            // LOG_WARN << static_cast<double>(totalBytesRead) /
            //                 (timeout_ * 1024 * 1024)
            //          << " MiB/s throughput";
            // TODO:
            loop_->quit();
        }
    }

  private:
    static void handleTimeout(void *pthis)
    {
        // TODO:
        // LOG_WARN << "stop";
        Client *pThis = static_cast<Client *>(pthis);
        std::for_each(
            pThis->sessions_.begin(),
            pThis->sessions_.end(),
            boost::mem_fn(&Session::stop));
    }

    EventLoop *loop_;
    int blockSize_;
    // EventLoopThreadPool threadPool_;
    int sessionCount_;
    int timeout_;
    boost::ptr_vector<Session> sessions_;
    char *message_;
    // 原子操作 C++支持的
    atomic_int numConnected_;
};

void Session::start()
{
    // 阻塞建立连接 建立好的之后调用client的onConnect
    conn_ = client_.onConnect();
    // 将自身的recv函数注册进去
    conn_->onRecv(buf, &len, 0, onMessage, this);
    if (conn_ != NULL) owner_->onConnect();
}

void Session::stop()
{
    client_.disConnect();
    owner_->onDisconnect();
}

int main(int argc, char *argv[])
{
    if (argc != 5) {
        fprintf(
            stderr, "Usage: client <threads> <blocksize> <sessions> <time>\n");
    } else {
        // LOG_INFO << "pid = " << getpid() << ", tid = " <<
        // CurrentThread::tid(); Logger::setLogLevel(Logger::WARN);

        int threadCount = atoi(argv[1]);
        int blockSize = atoi(argv[2]);
        int sessionCount = atoi(argv[3]);
        int timeout = atoi(argv[4]);

        // 初始化EPOLL
        EventLoop loop;
        loop.init();

        // 将buf的空间new出来 Memory leak
        buf = (char *) malloc(sizeof(char) * blockSize);

        Client client(&loop, blockSize, sessionCount, timeout, threadCount);

        loop.loop();
    }

    return 0;
}
