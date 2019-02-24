/**
 * @file nClient.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
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
#include "ndsl/net/ELThreadpool.h"
#include "ndsl/net/SocketAddress.h"
#include "ndsl/net/TcpChannel.h"

using namespace std;
using namespace ndsl;
using namespace net;
using namespace utils;

class Client;
uint64_t mlog;

class Session
{
  public:
    Session(EventLoop *loop, Client *owner)
        : client_() // 在这初始化的TcpClient
        , loop_(loop)
        , owner_(owner)
        , bytesRead_(0)
        , bytesWritten_(0)
        , messagesRead_(0)
        , buf_(NULL)
        , isStop_(false)
    {}
    ~Session() { free(buf_); }

    void start();

    void stop();

    int64_t bytesRead() const { return bytesRead_; }

    int64_t messagesRead() const { return messagesRead_; }

  private:
    static void onMessage(void *pthis)
    {
        Session *pThis = static_cast<Session *>(pthis);

        pThis->messagesRead_++;
        pThis->bytesRead_ += pThis->len_;
        pThis->bytesWritten_ += pThis->len_;

        int n;
        if ((n = pThis->conn_->onSend(
                 pThis->buf_, pThis->len_, 0, NULL, NULL)) < 0) {
            LOG(LOG_ERROR_LEVEL, mlog, "send fail");
        }

        if (!(pThis->isStop_)) {
            // 循环注册onRecv
            n = pThis->conn_->onRecv(
                pThis->buf_, &(pThis->len_), 0, onMessage, pThis);
            if (n < 0) { LOG(LOG_ERROR_LEVEL, mlog, "regist onRecv error"); }
        }
    }

  public:
    ssize_t len_;
    TcpClient client_;
    EventLoop *loop_;
    TcpConnection *conn_;
    Client *owner_;
    int64_t bytesRead_;
    int64_t bytesWritten_;
    int64_t messagesRead_;
    char *buf_;
    bool isStop_;
};

class Client
{
  public:
    Client(
        EventLoop *loop,
        ELThreadpool *threadPool,
        int blockSize,
        int sessionCount,
        int timeout,
        struct SocketAddress4 *servaddr)
        : loop_(loop)
        , blockSize_(blockSize)
        , threadPool_(threadPool)
        , sessionCount_(sessionCount)
        , timeout_(timeout)
        , servaddr_(servaddr)
    {
        // 初始化已连接数量
        numConnected_ = 0;

        // new出数据需要的空间
        message_ = (char *) malloc(sizeof(char) * (blockSize + 1));

        // 准备发送的数据
        for (int i = 0; i < blockSize; ++i) {
            message_[i] = '1';
        }
        message_[blockSize] = '\0';

        // 准备发送数据
        for (int i = 0; i < sessionCount; ++i) {
            Session *session =
                new Session(threadPool_->getNextEventLoop(), this);
            session->buf_ = (char *) malloc(sizeof(char) * 16384);
            sessions_.push_back(session);
            session->start();
        }
    }
    ~Client()
    {
        // 关闭定时器 释放资源
        time_->stop();
        delete time_;
    }

    void onConnect()
    {
        // 等所有链接都建立之后 设置定时器 发送数据
        if ((++numConnected_) == sessionCount_) {
            // 初始化定时器
            time_ = new TimeWheel(loop_);

            // 开始时间轮
            time_->start();

            // 初始化定时器任务
            TimeWheel::Task *t = new TimeWheel::Task;
            t->setInterval = timeout_; // 中断
            t->times = 1;
            t->doit = handleTimeout;
            t->param = this;

            // FIXME: 添加任务 task回收任务交给time处理
            time_->addTask(t);

            for (vector<Session *>::iterator it = sessions_.begin();
                 it != sessions_.end();
                 ++it) {
                int n;

                if ((n = (*it)->conn_->onSend(
                         message_, blockSize_, 0, NULL, NULL)) < 0) {
                    if (errno != EAGAIN || errno != EWOULDBLOCK)
                        LOG(LOG_ERROR_LEVEL, mlog, "send fail");
                }
            }

            free(message_);
        }
    }

    void onDisconnect()
    {
        if ((--numConnected_) == 0) {
            // LOG(LOG_INFO_LEVEL, mlog, "all disconnected");

            int64_t totalBytesRead = 0;
            int64_t totalMessagesRead = 0;

            for (Session *it : sessions_) {
                totalBytesRead += it->bytesRead();
                totalMessagesRead += it->messagesRead();

                delete it;
            }

            // 清空及释放内存
            sessions_.clear();
            vector<Session *>().swap(sessions_);

            LOG(LOG_INFO_LEVEL,
                mlog,
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
        }
    }

  private:
    static void handleTimeout(void *pthis)
    {
        Client *pThis = static_cast<Client *>(pthis);

        // 关闭每个链接
        for (Session *it : pThis->sessions_) {
            // 从loop上移除自身
            it->conn_->pTcpChannel_->erase();

            // 停止继续发送消息
            it->isStop_ = true;
        }

        // 关闭线程池
        pThis->threadPool_->quit();

        // 关闭每个链接
        for (Session *it : pThis->sessions_) {
            // 断开链接
            it->stop();
        }

        pThis->loop_->quit();
    }

    EventLoop *loop_;
    int blockSize_;
    ELThreadpool *threadPool_;
    int sessionCount_;
    int timeout_;
    vector<Session *> sessions_;
    char *message_;
    atomic_int numConnected_;
    TimeWheel *time_;

  public:
    struct SocketAddress4 *servaddr_;
};

void Session::start()
{
    // 阻塞建立连接
    conn_ = client_.onConnect(loop_, false, owner_->servaddr_);

    if (conn_ == NULL) { LOG(LOG_ERROR_LEVEL, mlog, "start onConnect fail"); }
    //将自身的recv函数注册进去
    if (conn_ != NULL) conn_->onRecv(buf_, &len_, 0, onMessage, this);

    if (conn_ != NULL) owner_->onConnect();
}

void Session::stop()
{
    client_.disConnect();
    owner_->onDisconnect();
}

int main(int argc, char *argv[])
{
    mlog = add_source();
    set_ndsl_log_sinks(mlog, LOG_OUTPUT_TER);
    if (argc != 7) {
        LOG(LOG_ERROR_LEVEL,
            mlog,
            "Usage: client <address> <port> <threads> <blocksize> "
            "<sessions> "
            "<time>");
    } else {
        struct SocketAddress4 servaddr(
            argv[1], static_cast<unsigned short>(atoi(argv[2])));

        int threadCount = atoi(argv[3]);
        int blockSize = atoi(argv[4]);
        int sessionCount = atoi(argv[5]);
        int timeout = atoi(argv[6]);

        // 新开loop放定时器
        EventLoop loop;
        loop.init();

        // 初始化线程池 设置线程
        ELThreadpool threadPool;
        threadPool.setMaxThreads(threadCount);

        // 在线程里new一个EventLoop
        threadPool.start();

        Client client(
            &loop, &threadPool, blockSize, sessionCount, timeout, &servaddr);

        // 开启定时器
        EventLoop::loop(&loop);
    }

    return 0;
}
