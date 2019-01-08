/**
 * @file Thread.cc
 * @brief
 * 封装线程类和线程池
 *
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */
#include "ndsl/utils/Thread.h"

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

int Thread::join(void **retval) { return ::pthread_join(id_, retval); }

void *Thread::runInThread(void *arg)
{
    Thread *th = static_cast<Thread *>(arg);
    th->ret_ = th->func_(th->param_);
    return (void *) th->ret_;
}

Threadpool::Threadpool(size_t threadNum)
    : threadNum_(threadNum)
{}

Threadpool::~Threadpool() {}
} // namespace utils
} // namespace ndsl