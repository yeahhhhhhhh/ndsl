#include <muduo/net/TcpClient.h>

#include <muduo/base/Logging.h>
#include <muduo/base/Thread.h>
#include <muduo/net/EventLoop.h>
#include <muduo/net/EventLoopThreadPool.h>
#include <muduo/net/InetAddress.h>

#include <boost/bind.hpp>
#include <boost/ptr_container/ptr_vector.hpp>

#include <utility>

#include <mcheck.h>
#include <stdio.h>
#include <unistd.h>

using namespace muduo;
using namespace muduo::net;

class Client;

class Session
{
  public:
    // Session *session = new Session(threadPool_.getNextLoop(), this);
    Session(EventLoop *loop, Client *owner)
        : client_()
        , owner_(owner)
        , bytesRead_(0)
        , bytesWritten_(0)
        , messagesRead_(0)
    {
        // 绑定 链接完成后的函数 既 链接完毕只有开始发送数据
        client_.setConnectionCallback(
            boost::bind(&Session::onConnection, this, _1));

        // 接收到数据之后 发送数据 ？
        client_.setMessageCallback(
            boost::bind(&Session::onMessage, this, _1, _2, _3));
    }

    void start() { client_.connect(); }

    void stop() { client_.disconnect(); }

    int64_t bytesRead() const { return bytesRead_; }

    int64_t messagesRead() const { return messagesRead_; }

  private:
    void onConnection(const TcpConnectionPtr &conn);

    void onMessage(const TcpConnectionPtr &conn, Buffer *buf, Timestamp time)
    {
        ++messagesRead_;
        bytesRead_ += buf->readableBytes();
        bytesWritten_ += buf->readableBytes();
        conn->send(buf);
    }

    TcpClient client_;
    Client *owner_;
    int64_t bytesRead_;
    int64_t bytesWritten_;
    int64_t messagesRead_;
};

void Session::onConnection(const TcpConnectionPtr &conn)
{
    if (conn->connected()) {
        conn->setTcpNoDelay(true);
        conn->send(owner_->message());
        owner_->onConnect();
    } else {
        owner_->onDisconnect();
    }
}

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
        , threadPool_(loop)
        , sessionCount_(sessionCount)
        , timeout_(timeout)
    {
        // 设置定时器 TODO: 全部链接完成后再设置 换成自己的timewheel
        loop->runAfter(timeout, boost::bind(&Client::handleTimeout, this));

        // 设置线程 如果是多线程的话 在这里new一个线程池出来
        // if (threadCount > 1) { threadPool_.setThreadNum(threadCount); }
        // threadPool_.start();

        // 准备发送的数据
        for (int i = 0; i < blockSize; ++i) {
            message_.push_back(static_cast<char>(i % 128));
        }

        // 准备发送数据
        for (int i = 0; i < sessionCount; ++i) {
            Session *session = new Session(threadPool_.getNextLoop(), this);
            // 发送数据
            session->start();
            sessions_.push_back(session);
        }
    }

    const string &message() const { return message_; }

    void onConnect()
    {
        // 为以后多线程做准备
        if (numConnected_.incrementAndGet() == sessionCount_) {
            LOG_WARN << "all connected";
        }
    }

    void onDisconnect()
    {
        if (numConnected_.decrementAndGet() == 0) {
            LOG_WARN << "all disconnected";

            int64_t totalBytesRead = 0;
            int64_t totalMessagesRead = 0;
            for (boost::ptr_vector<Session>::iterator it = sessions_.begin();
                 it != sessions_.end();
                 ++it) {
                totalBytesRead += it->bytesRead();
                totalMessagesRead += it->messagesRead();
            }
            LOG_WARN << totalBytesRead << " total bytes read";
            LOG_WARN << totalMessagesRead << " total messages read";
            LOG_WARN << static_cast<double>(totalBytesRead) /
                            static_cast<double>(totalMessagesRead)
                     << " average message size";
            LOG_WARN << static_cast<double>(totalBytesRead) /
                            (timeout_ * 1024 * 1024)
                     << " MiB/s throughput";
            loop_->quit();
        }
    }

  private:
    void handleTimeout()
    {
        LOG_WARN << "stop";
        std::for_each(
            sessions_.begin(), sessions_.end(), boost::mem_fn(&Session::stop));
    }

    EventLoop *loop_;
    EventLoopThreadPool threadPool_;
    int sessionCount_;
    int timeout_;
    boost::ptr_vector<Session> sessions_;
    string message_;
    AtomicInt32 numConnected_;
};

int main(int argc, char *argv[])
{
    if (argc != 5) {
        fprintf(
            stderr, "Usage: client <threads> <blocksize> <sessions> <time>\n");
    } else {
        LOG_INFO << "pid = " << getpid() << ", tid = " << CurrentThread::tid();
        Logger::setLogLevel(Logger::WARN);

        int threadCount = atoi(argv[1]);
        int blockSize = atoi(argv[2]);
        int sessionCount = atoi(argv[3]);
        int timeout = atoi(argv[4]);

        // 初始化EPOLL
        EventLoop loop;
        loop.init();

        Client client(&loop, blockSize, sessionCount, timeout, threadCount);

        loop.loop();
    }
}
