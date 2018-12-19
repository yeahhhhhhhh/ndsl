/**
 * @file EventLoop.cc
 * @brief
 * 事件循环的实现
 *
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */

#include <sys/eventfd.h>
#include <errno.h>
#include <list>
#include "ndsl/utils/temp_define.h"
#include "ndsl/net/Epoll.h"
#include "ndsl/net/Channel.h"
#include "ndsl/net/EventLoop.h"

namespace ndsl {
namespace net {

/**
 * @class: WorkQueue
 * @brief:
 * 任务队列
 */
bool WorkQueue::empty()
{
    queueMutex_.lock();
    bool ret = queue_.empty();
    queueMutex_.unlock();
    return ret;
}

void WorkQueue::doit()
{
    work_struct *curWork;

    std::list<struct work_struct *> getQueue;

    queueMutex_.lock();
    getQueue.swap(queue_);
    queueMutex_.unlock();

    while (!getQueue.empty()) {
        // 取队首任务
        curWork = getQueue.front(); // 若非空，则取出
        getQueue.pop_front();       // 删除第一个元素

        // 执行任务
        curWork->doit(curWork->para);
    }
}

void WorkQueue::enQueue(work_struct *work)
{
    queueMutex_.lock();
    queue_.push_back(work);
    queueMutex_.unlock();
}

/**
 * @class QueueChannel
 * @brief
 * 维护任务队列
 */
QueueChannel::QueueChannel(int fd, EventLoop *loop)
    : BaseChannel(fd, loop)
{}

QueueChannel::~QueueChannel()
{
    // if (fd_ >= 0) { ::close(fd_); }
}

// 添加任务
void QueueChannel::addWork(work_struct *work) { workqueue_.enQueue(work); }

// 没有重载
int QueueChannel::onRead(char *inBuf)
{
    LOG(LEVEL_ERROR, "Wrong call QueueChannel::onRead");
    return S_FAIL;
}

// 发送中断信号
int QueueChannel::onWrite()
{
    uint64_t data = 1;
    int ret = ::write(getFd(), &data, sizeof(data));

    if (ret == -1) {
        LOG(LEVEL_ERROR, "QueueChannel::onWrite write");
        return errno;
    }

    return S_OK;
}

// 处理队列中的任务
int QueueChannel::handleEvent()
{
    while (!workqueue_.empty()) {
        workqueue_.doit();
    }
    return S_OK;
}

/**
 * @class InterruptChannel
 * @brief
 * 中断EventLoop,退出循环
 */
InterruptChannel::InterruptChannel(int fd, EventLoop *loop)
    : BaseChannel(fd, loop)
{}

InterruptChannel::~InterruptChannel()
{
    if (fd_ >= 0) { ::close(fd_); }
}

int InterruptChannel::onRead(char *inBuf)
{
    LOG(LEVEL_ERROR, "Wrong call InterruptChannel::onRead");
    return S_FAIL;
}

int InterruptChannel::onWrite()
{
    uint64_t data;
    data = 1;

    int ret = ::write(fd_, &data, sizeof(data));

    if (ret == -1) {
        LOG(LEVEL_ERROR, "InterruptChannel::onWrite");
        return errno;
    }

    return S_OK;
}

int InterruptChannel::handleEvent()
{
    LOG(LEVEL_ERROR, "Wrong call InterruptChannel::handleEvent");
    return S_FAIL;
}

/**
 * @class EventLoop
 * @brief
 * 事件循环: 包含一个QueueChannel和一个InterruptChannel
 */

EventLoop::EventLoop()
    : pQueCh_(NULL)
    , pIntrCh_(NULL)

{}

EventLoop::~EventLoop()
{
    if (pIntrCh_) { delete pIntrCh_; } // 若pIntrCh_不为空,则释放内存
    if (pQueCh_) { delete pQueCh_; }   // 若pQueCh_不为空,则释放内存
}

int EventLoop::init()
{
    int evfd;
    int ret;

    // 初始化epoll
    ret = epoll_.init();
    if (ret != S_OK) { return ret; }

    // 若pQueCh_为空,则分配eventfd
    if (!pQueCh_) {
        evfd = eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK | EFD_SEMAPHORE);
        if (evfd < 0) {
            LOG(LEVEL_ERROR, "EventLoop::init pQueCh_ eventfd\n");
            return errno;
        }

        // 创建QueueChannel
        pQueCh_ = new QueueChannel(evfd, this);

        // printf("pQueCh_ = %d\n", pQueCh_->getFd());

        ret = pQueCh_->enableReading();
        if (ret != S_OK) return ret; // 若不成功直接返回
    }

    // 若pIntrCh_为空,则分配eventfd
    if (!pIntrCh_) {
        evfd = eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK | EFD_SEMAPHORE);
        if (evfd < 0) {
            LOG(LEVEL_ERROR, "EventLoop::init pIntrCh_ eventfd\n");
            return errno;
        }

        // 创建InterruptChannel
        pIntrCh_ = new InterruptChannel(evfd, this);

        // printf("pIntrCh_ = %d\n", pIntrCh_->getFd());

        ret = pIntrCh_->enableReading();
        if (ret != S_OK) return ret; // 若不成功直接返回
    }
    return S_OK;
}

int EventLoop::loop()
{
    int nEvents = 0;
    // 进入事件循环
    while (true) {
        Channel *channels[Epoll::MAX_EVENTS];
        if (S_OK != epoll_.wait(channels, nEvents, -1)) {
            // LOG(LEVEL_ERROR, "EventLoop::loop epoll->wait\n");
            break;
        }

        bool quit = false;    // 退出标志
        bool haswork = false; // 中断标志

        // 处理事件
        for (int i = 0; i < nEvents; i++) {
            if (pIntrCh_ == channels[i]) // 退出Channel响应,退出标记
                quit = true;
            else if (pQueCh_ == channels[i]) // 任务队列非空,中断标记
                haswork = true;
            else
                channels[i]->handleEvent();
        }

        // 处理任务队列
        if (haswork) { pQueCh_->handleEvent(); }
        // 退出
        if (quit) break;
    }
    return S_OK;
}

// 添加任务
void EventLoop::addWork(work_struct *work)
{
    pQueCh_->addWork(work);
    pQueCh_->onWrite();
}

int EventLoop::regist(Channel *pCh) { return epoll_.regist(pCh); }

int EventLoop::update(Channel *pCh) { return epoll_.update(pCh); }

int EventLoop::del(Channel *pCh) { return epoll_.del(pCh); }

void EventLoop::quit() { pIntrCh_->onWrite(); }

} // namespace net
} // namespace ndsl