/**
 * @file Thread.cc
 * @brief
 * 封装线程类和线程池
 *
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */
#include <unistd.h>
#include "ndsl/utils/Thread.h"
#include "ndsl/utils/Error.h"
#include "ndsl/utils/Log.h"

namespace ndsl {
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
    return ret;
}

int Thread::join(void **retval)
{
    int ret = ::pthread_join(id_, retval);
    if (ret != S_OK) {
        LOG(LOG_ERROR_LEVEL,
            LOG_SOURCE_THREAD,
            "Thread::join pthread_join error");
        LOG(LOG_ERROR_LEVEL,
            LOG_SOURCE_THREAD,
            "errno = %d, %s",
            errno,
            strerror(errno));
    }
    return ret;
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
            "Thread::getNumberOfProcessors sysconf");
        return S_FALSE;
    }

    return ret;
}

Threadpool::Threadpool() {}

Threadpool::~Threadpool() {}

int Threadpool::create(ThreadFunc threadfunc, void *param)
{
    // 若已达到最大线程数,则返回失败
    if (size() >= (int) capacity()) return S_FALSE;

    Thread *th = new Thread(threadfunc, param);
    pool_.push_back(th);

    return th->run();
}

int Threadpool::join()
{
    for (auto it = pool_.begin(); it != pool_.end(); ++it) {
        int ret = (*it)->join();
        if (ret != S_OK) return ret;
    }

    LOG(LOG_DEBUG_LEVEL,
        LOG_SOURCE_THREADPOOL,
        "ThreadPool joined %ld threads.\n",
        pool_.size());

    clean();
    return S_OK;
}

int Threadpool::capacity()
{
    return Redundancy * Thread::getNumberOfProcessors();
}

int Threadpool::size() { return pool_.size(); }

int Threadpool::clean()
{
    while (pool_.begin() != pool_.end()) {
        delete *pool_.begin();
        pool_.erase(pool_.begin());
    }

    return S_OK;
}

} // namespace utils
} // namespace ndsl