/*
 * @file: EventLoop.cc
 * @brief
 * 事件循环的实现
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */

#include <sys/eventfd.h>
#include <errno.h>
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

    queueMutex_.lock();

    while (!queue_.empty()) {
        // 取队首任务
        curWork = queue_.front(); // 若非空，则取出
        queue_.pop_front();       // 删除第一个元素
        queueMutex_.unlock();

        // 执行任务
        curWork->doit(curWork->para);

        queueMutex_.lock();
    }

    queueMutex_.unlock();
}

void WorkQueue::enQueue(work_struct *work)
{
    queueMutex_.lock();
    queue_.push_back(work);
    queueMutex_.unlock();
}

/**
 * @class: QueueChannel
 * @brief:
 * 维护任务队列
 */
QueueChannel::QueueChannel(int fd, EventLoop *loop)
    : Channel(fd, loop)
{}

QueueChannel::~QueueChannel()
{
    if (getFd() >= 0) { ::close(getFd()); }
}

// 添加任务
void QueueChannel::addWork(work_struct *work) { workqueue_.enQueue(work); }

// 没有重载
int QueueChannel::onRead()
{
    LOG(LEVEL_ERROR, "Wrong call QueueChannel::onRead");
    return S_FAIL;
}

// 发送中断信号
int QueueChannel::onWrite()
{
    uint64_t data = 1;
    int ret = ::write(this->getFd(), &data, sizeof(data));

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
 * @class: InterruptChannel
 * @brief:
 * 中断EventLoop,退出循环
 */
InterruptChannel::InterruptChannel(int fd, EventLoop *loop)
    : Channel(fd, loop)
{}

InterruptChannel::~InterruptChannel()
{
    if (getFd() >= 0) { ::close(getFd()); }
}

int InterruptChannel::onRead()
{
    LOG(LEVEL_ERROR, "Wrong call InterruptChannel::onRead");
    return S_FAIL;
}

int InterruptChannel::onWrite()
{
    uint64_t data;
    data = 1;

    int ret = ::write(getFd(), &data, sizeof(data));

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
 * @class: EventLoop
 * @brief:
 * 事件循环: 包含一个QueueChannel和一个InterruptChannel
 */

EventLoop::EventLoop(Epoll *epoll)
    : epoll_(epoll)
    , pQueCh_(NULL)
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
    // 若pIntrCh_为空,则分配eventfd
    if (!pIntrCh_) {
        evfd = eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK | EFD_SEMAPHORE);
        if (evfd < 0) {
            LOG(LEVEL_ERROR, "EventLoop::init pIntrCh_ eventfd\n");
            return errno;
        }

        // 创建InterruptChannel
        pIntrCh_ = new InterruptChannel(evfd, this);

        printf("pIntrCh_.getFd() = %d\n", pIntrCh_->getFd());

        pIntrCh_->enableReading();
    }

    // 若pQueCh_为空,则分配eventfd
    if (!pQueCh_) {
        evfd = eventfd(0, EFD_CLOEXEC | EFD_NONBLOCK | EFD_SEMAPHORE);
        if (evfd < 0) {
            LOG(LEVEL_ERROR, "EventLoop::init pQueCh_ eventfd\n");
            return errno;
        }

        // 创建QueueChannel
        pQueCh_ = new QueueChannel(evfd, this);
        printf("pQueCh_.getFd() = %d\n", pQueCh_->getFd());
        pQueCh_->enableReading();
    }
    return S_OK;
}

int EventLoop::loop()
{
    // 进入事件循环
    while (true) {
        LOG(LEVEL_INFO, "In wait.\n");
        std::vector<Channel *> channels;
        epoll_->wait(channels, -1);

        LOG(LEVEL_INFO, "out wait.\n");
        bool quit = false;    // 退出标志
        bool haswork = false; // 中断标志

        // 处理事件
        for (auto it = channels.begin(); it != channels.end(); ++it) {
            // 若任务队列非空，则标记中断
            if (pIntrCh_->getFd() == (*it)->getFd())
                quit = true;
            else if (pQueCh_->getFd() == (*it)->getFd())
                haswork = true;
            else
                (*it)->handleEvent();
            LOG(LEVEL_INFO, "handle event.\n");
        }

        if (haswork) { pQueCh_->handleEvent(); }
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

int EventLoop::regist(Channel *pCh) { return epoll_->regist(pCh); }

int EventLoop::update(Channel *pCh) { return epoll_->update(pCh); }

int EventLoop::del(Channel *pCh) { return epoll_->del(pCh); }

void EventLoop::quit() { pIntrCh_->onWrite(); }

} // namespace net
} // namespace ndsl