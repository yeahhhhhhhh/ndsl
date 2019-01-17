/**
 * @file ELThreadpoolTest.cc
 * @brief
 * ELThreadpool的单元测试
 *
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */
#include "../catch.hpp"
#include "ndsl/net/ELThreadpool.h"
#include "ndsl/net/EventLoop.h"
#include "ndsl/utils/Error.h"

using namespace ndsl::net;
using namespace ndsl::utils;

void ELTP_func(void *) {}

void *test1(void *arg)
{
    LOG(LOG_INFO_LEVEL,
        LOG_SOURCE_ELTHREADPOOL,
        "This is thread %ld\n",
        (long) arg);
    return (void *) 0;
}

TEST_CASE("Thread")
{
    SECTION("run and join")
    {
        Thread t1(test1, (void *) 1);
        REQUIRE(t1.run() == S_OK);

        REQUIRE(t1.join() == S_OK);
    }
}

TEST_CASE("ELThreadpool")
{
    ELThreadpool eltp;
    SECTION("setMaxThreads")
    {
        int ret = eltp.setMaxThreads(4);
        REQUIRE(ret == S_OK);

        REQUIRE(eltp.getMaxThreads() == 4);

        eltp.setMaxThreads(1024);
        REQUIRE(ret == S_OK);
        REQUIRE(eltp.getMaxThreads() == (2 * Thread::getNumberOfProcessors()));
    }

    SECTION("quit")
    {
        eltp.start();

        // start只有一个线程
        REQUIRE(eltp.getLoopsNum() == 1);

        EventLoop *loop = eltp.getNextEventLoop();

        loop = eltp.getNextEventLoop();

        EventLoop::WorkItem wi;
        wi.doit = ELTP_func;
        wi.param = NULL;

        loop->addWork(&wi);

        // 以后没getNextEventLoop再起线程
        REQUIRE(eltp.getLoopsNum() == 2);

        REQUIRE(eltp.quit() == S_OK);

        REQUIRE(eltp.getLoopsNum() == 0);
    }
}