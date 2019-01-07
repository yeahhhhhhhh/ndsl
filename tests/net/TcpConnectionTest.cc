/*
 * File: TcpChannelTest.cc
 * brief:
 *
 * Author: gyz
 * Email: mni_gyz@163.com
 * Last Modified: Thursday, 29th November 2018 11:39:46 am
 */

#include "../catch.hpp"
#include "ndsl/net/EventLoop.h"
#include "ndsl/net/Epoll.h"
#include "ndsl/net/TcpChannel.h"
#include "ndsl/net/TcpConnection.h"
#include "ndsl/utils/Log.h"
#include <cstring>

using namespace ndsl;
using namespace net;

TEST_CASE("net/TcpConnection")
{
    SECTION("send write")
    {
        // 初始化EPOLL
        Epoll ep;
        ep.init();
        EventLoop loop(&ep);
        REQUIRE(loop.init() == S_OK);

        // 初始化 TcpConnection
        int fd = 1;
        TcpConnection pConn(fd, &loop);

        // 写数据过去
        write(fd, "hello world", sizeof("hello world"));
        char buf[MAXLINE];
        read(fd, buf, MAXLINE);
        REQUIRE(strcmp(buf, "received") == 0);

        // 停止loop循环
        loop.quit();
        REQUIRE(loop.loop() == S_OK);
    }
}