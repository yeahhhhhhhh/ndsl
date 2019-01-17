/**
 * @file ELThreadpool.cc
 * @brief
 * 封装EventLoop的线程和线程池
 *
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */
#include "ndsl/net/ELThreadpool.h"
#include "ndsl/net/EventLoop.h"
#include "ndsl/utils/Error.h"
// #include "ndsl/utils/Thread.h"
#include "ndsl/utils/Log.h"

namespace ndsl {

using namespace net;
namespace utils {

Thread::Thread(ThreadFunc threadfunc, void *param)
    : func_(threadfunc)
    , param_(param)
    , id_(0)
    , ret_(NULL)
{}

Thread::~Thread() {}

int Thread::run()
{
    int ret = ::pthread_create(&id_, NULL, runInThread, (void *) this);
    if (ret != S_OK) {
        LOG(LOG_ERROR_LEVEL,
            LOG_SOURCE_THREAD,
            "pthread_create errno = %d:%s\n",
            errno,
            strerror(errno));
        return S_FALSE;
    }
    return S_OK;
}

int Thread::join(void **retval)
{
    int ret = ::pthread_join(id_, retval);
    if (ret != S_OK) {
        LOG(LOG_ERROR_LEVEL,
            LOG_SOURCE_THREAD,
            "pthread_join errno = %d:%s\n",
            errno,
            strerror(errno));
        return S_FALSE;
    }
    return S_OK;
}

void *Thread::runInThread(void *arg)
{
    LOG(LOG_INFO_LEVEL, LOG_SOURCE_THREAD, "one thread is running!\n");

    Thread *th = static_cast<Thread *>(arg);
    th->ret_ = th->func_(th->param_);
    return (void *) th->ret_;
}

int Thread::getNumberOfProcessors()
{
    int ret = ::sysconf(_SC_NPROCESSORS_ONLN);
    if (ret == -1) {
        LOG(LOG_ERROR_LEVEL,
            LOG_SOURCE_THREAD,
            "sysconf errno = %d:%s\n",
            errno,
            strerror(errno));
        return S_FALSE;
    }

    return ret;
}

ELThread::ELThread(EventLoop *loop)
    : loop_(loop)
    , thread_(loop_->loop, loop)
    , running_(false)
{}

ELThread::~ELThread()
{
    // 若线程正在运行,则退出循环,等待线程结束
    if (running_) {
        loop_->quit();
        join();
    }
}

int ELThread::run()
{
    int ret = thread_.run();
    if (ret == S_OK) running_ = true;

    return ret;
}

int ELThread::join()
{
    int ret = thread_.join();
    if (ret == S_OK) running_ = false;

    return ret;
}

bool ELThread::isRunning() const { return running_; }

ELThreadpool::ELThreadpool()
    : MaxThreads_(0)
    , nextThread_(0)
{}

ELThreadpool::~ELThreadpool() {}

int ELThreadpool::start()
{
    // 若没有设置最大线程数,则设为默认值
    if (MaxThreads_ == 0) MaxThreads_ = capacity();

    // 暂时打开一个线程
    EventLoop *el = new EventLoop();

    // EventLoop的初始化
    int ret = el->init();
    if (ret != S_OK) {
        LOG(LOG_ERROR_LEVEL, LOG_SOURCE_ELTHREADPOOL, "EventLoop init error\n");
        return S_FALSE;
    }

    ELThread *elt = new ELThread(el);
    loops_.push_back(el);
    loopThreads_.push_back(elt);

    // 开启线程
    ret = elt->run();
    if (ret != S_OK) {
        LOG(LOG_ERROR_LEVEL, LOG_SOURCE_ELTHREADPOOL, "ELThread run error\n");
        return S_FALSE;
    }

    return S_OK;
}

EventLoop *ELThreadpool::getNextEventLoop()
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
            LOG(LOG_ERROR_LEVEL, LOG_SOURCE_ELTHREADPOOL, "init error\n");
            return NULL;
        }

        ELThread *elt = new ELThread(el);
        loops_.push_back(el);
        loopThreads_.push_back(elt);

        // 开启线程
        ret = elt->run();
        if (ret != S_OK) {
            LOG(LOG_ERROR_LEVEL, LOG_SOURCE_ELTHREADPOOL, "run error\n");
            return NULL;
        }

        return loops_[nextThread_++];
    } else {
        LOG(LOG_ERROR_LEVEL, LOG_SOURCE_ELTHREADPOOL, "fatal error\n");
        return NULL;
    }
}

int ELThreadpool::setMaxThreads(unsigned int maxThreads)
{
    // 若设置的线程数小于当前已有的线程数,则退出
    if (maxThreads < loopThreads_.size()) return S_FALSE;

    MaxThreads_ = capacity();
    // 若超过默认的最大值,则设置为最大值
    if (maxThreads > MaxThreads_) return S_OK;

    MaxThreads_ = maxThreads;
    return S_OK;
}

unsigned int ELThreadpool::getMaxThreads() const { return MaxThreads_; }

int ELThreadpool::quit()
{
    if (loopThreads_.size() != loops_.size()) {
        LOG(LOG_ERROR_LEVEL, LOG_SOURCE_ELTHREADPOOL, "fatal error\n");
        return S_FALSE;
    }

    LOG(LOG_DEBUG_LEVEL,
        LOG_SOURCE_ELTHREADPOOL,
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

int ELThreadpool::getLoopsNum() { return loops_.size(); }

int ELThreadpool::capacity()
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