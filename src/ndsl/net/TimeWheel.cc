/**
 * @file TimeWheel.cc
 * @brief
 *
 *
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */
#include "ndsl/net/TimeWheel.h"
#include <algorithm>

namespace ndsl {
namespace net {
TimerfdChannel::TimerfdChannel(int fd, EventLoop *loop) {}

TimerfdChannel::~TimerfdChannel() {}

TimeWheel::TimeWheel(EventLoop *loop)
    : pLoop_(loop)
    , ptimerfdChannel_(NULL)
    , curTick_(0)
{}

TimeWheel::~TimeWheel()
{
    if (ptimerfdChannel_) delete ptimerfdChannel_;
}

// 初始化,创建TimerfdChannel
int TimeWheel::init()
{
    int fd = timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
    if (fd == -1) {
        LOG(LEVEL_ERROR, "TimeWheel::init timerfd_create error!\n");
        return errno;
    }

    ptimerfdChannel_ = new TimerfdChannel(fd, pLoop_);

    for (int i = 0; i < SLOTNUM; i++)
        slot[i].clear();

    return S_OK;
}

int TimeWheel::start()
{
    int ret = init();
    if (ret != S_OK) { return ret; }

    // 设置时间轮的时间间隔
    struct itimerspec new_value;
    struct timespec now;

    if (clock_gettime(CLOCK_MONOTONIC, &now) == -1) {
        LOG(LEVEL_ERROR, "TimeWheel::init clock_gettime error!\n");
        return errno;
    }

    new_value.it_value.tv_sec = now.tv_sec;
    new_value.it_value.tv_nsec = now.tv_nsec;

    new_value.it_interval.tv_sec = INTERVAL;
    new_value.it_interval.tv_nsec = 0;

    if (timerfd_settime(ptimerfdChannel_->getFd(), 0, &new_value, NULL) == -1) {
        LOG(LEVEL_ERROR, "TimeWheel::init timerfd_settime error!\n");
        return errno;
    }

    ptimerfdChannel_->enableReading();

    return S_OK;
}

// 停止时间轮
int TimeWheel::stop()
{
    if (timerfd_settime(ptimerfdChannel_->getFd(), 0, 0, NULL) == -1) {
        LOG(LEVEL_ERROR, "TimeWheel::init timerfd_settime error!\n");
        return errno;
    }

    return S_OK;
}

// FIXME:需要加锁吗?
int TimeWheel::addTask(Task *task)
{
    // 若task为空,直接返回
    if (task->setInterval == -1 || task->doit == NULL) return S_FAIL;

    int setTick = (curTick_ + task->setInterval) % SLOTNUM;

    slot[setTick].push_back(task);

    task->setTick = setTick;

    return S_OK;
}

int TimeWheel::removeTask(Task *task)
{
    // task为空,直接返回
    if (task->setInterval == -1 || task->setTick == -1 || task->doit == NULL)
        return S_FAIL;

    auto slotList = slot[task->setTick];

    // 标准模板库提供的find函数
    auto iter = std::find(slotList.begin(), slotList.end(), task);

    // 若没有找到,则直接返回
    if (iter == slotList.end()) return S_FAIL;

    slotList.erase(iter);
    return S_OK;
}

int TimeWheel::onTick()
{
    ++curTick_;

    // 若队列为空,则直接返回
    if (slot[curTick_].empty()) return S_OK;

    for (auto it = slot[curTick_].begin(); it != slot[curTick_].end(); ++it) {
        // 若不在本轮,则减少轮数
        if ((*it)->restInterval >= SLOTNUM) {
            (*it)->restInterval -= SLOTNUM;
        } else {
            (*it)->doit((*it)->para);
            if ((*it)->times > 0) (*it)->times--;
            // TODO:判断是否还有下一次执行,若有,则在时间轮上设置
        }
    }
}
} // namespace net
} // namespace ndsl