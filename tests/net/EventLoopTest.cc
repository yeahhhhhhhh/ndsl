/*
 * @file: EventLoopTest.cc
 * @brief
 * EventLoop的单元测试，包含WorkQueue的单元测试
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */

#include <thread>
#include "catch2/catch.hpp"
#include "ndsl/net/EventLoop.h"
#include "ndsl/net/Epoll.h"
#include "ndsl/utils/temp_define.h"

using namespace ndsl;
using namespace net;

TEST_CASE("net/EventLoop(WorkQueue)")
{
    SECTION("quit")
    {
        Epoll ep;
        ep.init();
        EventLoop loop(&ep);
        REQUIRE(loop.init() == S_OK);

        // bind c++11特性
        std::thread th(std::bind(&EventLoop::loop, loop));
    }
}