/*
 * @file: EventLoopTest.cc
 * @brief
 * EventLoop的单元测试，包含WorkQueue的单元测试
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */

#include <thread>
#include "catch.hpp"
#include "ndsl/net/EventLoop.h"
#include "ndsl/net/Epoll.h"
#include "ndsl/utils/temp_define.h"

using namespace ndsl;
using namespace net;

void func1(void *para) { printf("Call func1 and para is %ld!\n", (long) para); }

void func2(void *para)
{
    printf("Call func2 and para is %s!\n", (char *) para);
}

TEST_CASE("net/EventLoop(WorkQueue)")
{
    SECTION("addwork and quit")
    {
        Epoll ep;
        ep.init();
        EventLoop loop(&ep);
        REQUIRE(loop.init() == S_OK);

        // bind c++11特性
        // std::thread th(std::bind(&EventLoop::loop, &loop));

        work_struct *w1 = new work_struct;
        w1->doit = func1;
        w1->para = (void *) 100;
        loop.addWork(w1);

        work_struct *w2 = new work_struct;
        w2->doit = func2;
        w2->para = (void *) "Hello World!";
        loop.addWork(w2);

        loop.quit();

        REQUIRE(loop.loop() == S_OK);
    }
}