/**
 * @file TcpConnectionTest.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "ndsl/net/EventLoop.h"
#include "ndsl/net/Epoll.h"
#include "ndsl/net/TcpChannel.h"
#include "ndsl/net/TcpConnection.h"
#include "ndsl/utils/temp_define.h"
#include <cstring>

using namespace ndsl;
using namespace net;

// char *sayHello() { return "Hello"; }

bool recv = FALSE;

void fun1() { recv = TRUE; }

TEST_CASE("net/TcpConnection(onRecv)")
{
    SECTION("send write")
    {
        // 初始化EPOLL
        Epoll ep;
        ep.init();
        EventLoop loop(&ep);
        REQUIRE(loop.init() == S_OK);

        // 初始化 TcpConnection
        int fd = 342;
        TcpConnection *pConn = new TcpConnection(fd, &loop);

        // 写数据过去
        size_t len;
        char buf[24];
        memset(buf, 0, sizeof(buf));
        int errn;

        write(fd, "hello", sizeof("hello"));
        pConn->onRecv(buf, len, 0, cb1, NULL, errn);

        while (TRUE) {
            if (recv) {
                REQUIRE(strcmp(buf, "hello") == 0);
                break;
            }
        }

        // 停止loop循环
        loop.quit();
        REQUIRE(loop.loop() == S_OK);
    }
}