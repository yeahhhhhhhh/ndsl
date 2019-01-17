/**
 * @file EventLoopThreadpool.cc
 * @brief
 * 封装EventLoop的线程和线程池
 *
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */
#include "ndsl/utils/EventLoopThreadpool.h"
#include "ndsl/net/EventLoop.h"
#include "ndsl/utils/Error.h"
#include "ndsl/utils/Thread.h"
#include "ndsl/utils/Log.h"

namespace ndsl {

using namespace net;
namespace utils {

EventLoopThread::EventLoopThread(EventLoop *loop)
    : loop_(loop)
    , thread_(loop_->loop, loop)
    , running_(false)
{}

EventLoopThread::~EventLoopThread()
{
    // 若线程正在运行,则退出循环,等待线程结束
    if (running_) {
        loop_->quit();
        join();
    }
}

int EventLoopThread::run()
{
    int ret = thread_.run();
    if (ret == S_OK) running_ = true;

    return ret;
}

int EventLoopThread::join()
{
    int ret = thread_.join();
    if (ret == S_OK) running_ = false;

    return ret;
}

bool EventLoopThread::isRunning() const { return running_; }

EventLoopThreadpool::EventLoopThreadpool()
    : MaxThreads_(0)
    , nextThread_(0)
{}

EventLoopThreadpool::~EventLoopThreadpool() {}

int EventLoopThreadpool::start()
{
    // 若没有设置最大线程数,则设为默认值
    if (MaxThreads_ == 0) MaxThreads_ = capacity();

    // 暂时打开一个线程
    EventLoop *el = new EventLoop();

    // EventLoop的初始化
    int ret = el->init();
    if (ret != S_OK) {
        LOG(LOG_ERROR_LEVEL,
            LOG_SOURCE_EVENTLOOPTHREADPOOL,
            "EventLoop init error\n");
        return S_FALSE;
    }

    EventLoopThread *elt = new EventLoopThread(el);
    loops_.push_back(el);
    loopThreads_.push_back(elt);

    // 开启线程
    ret = elt->run();
    if (ret != S_OK) {
        LOG(LOG_ERROR_LEVEL,
            LOG_SOURCE_EVENTLOOPTHREADPOOL,
            "EventLoopThread run error\n");
        return S_FALSE;
    }

    return S_OK;
}

EventLoop *EventLoopThreadpool::getNextEventLoop()
{
    nextThread_ %= MaxThreads_;
    // 若已有足够多的线程,则直接返回
    if (nextThread_ < loops_.size())
        return loops_[nextThread_++];
    else if (nextThread_ == loops_.size()) {
        EventLoop *el = new EventLoop();

        // EventLoop初始化
        int ret = el->init();
        if (ret != S_OK) {
            LOG(LOG_ERROR_LEVEL,
                LOG_SOURCE_EVENTLOOPTHREADPOOL,
                "init error\n");
            return NULL;
        }

        EventLoopThread *elt = new EventLoopThread(el);
        loops_.push_back(el);
        loopThreads_.push_back(elt);

        // 开启线程
        ret = elt->run();
        if (ret != S_OK) {
            LOG(LOG_ERROR_LEVEL, LOG_SOURCE_EVENTLOOPTHREADPOOL, "run error\n");
            return NULL;
        }

        return loops_[nextThread_++];
    } else {
        LOG(LOG_ERROR_LEVEL, LOG_SOURCE_EVENTLOOPTHREADPOOL, "fatal error\n");
        return NULL;
    }
}

int EventLoopThreadpool::setMaxThreads(unsigned int maxThreads)
{
    // 若设置的线程数小于当前已有的线程数,则退出
    if (maxThreads < loopThreads_.size()) return S_FALSE;

    MaxThreads_ = capacity();
    // 若超过默认的最大值,则设置为最大值
    if (maxThreads > MaxThreads_) return S_OK;

    MaxThreads_ = maxThreads;
    return S_OK;
}

unsigned int EventLoopThreadpool::getMaxThreads() const { return MaxThreads_; }

int EventLoopThreadpool::quit()
{
    if (loopThreads_.size() != loops_.size()) {
        LOG(LOG_ERROR_LEVEL, LOG_SOURCE_EVENTLOOPTHREADPOOL, "fatal error\n");
        return S_FALSE;
    }

    LOG(LOG_DEBUG_LEVEL,
        LOG_SOURCE_EVENTLOOPTHREADPOOL,
        "%d threads joined\n",
        loops_.size());

    for (int i = loops_.size() - 1; i >= 0; i--) {
        delete loopThreads_[i];
        delete loops_[i];

        loops_.pop_back();
        loopThreads_.pop_back();
    }

    return S_OK;
}

int EventLoopThreadpool::getLoopsNum() { return loops_.size(); }

int EventLoopThreadpool::capacity()
{
    int processors = Thread::getNumberOfProcessors();
    if (processors == S_FALSE) {
        // 获取失败,默认返回1
        return 1;
    }

    return Redundancy * processors;
}
} // namespace utils
} // namespace ndsl