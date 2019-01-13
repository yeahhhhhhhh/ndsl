/**
 * @file TcpConnectionTest.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#include "../catch.hpp"
#include "ndsl/net/EventLoop.h"
#include "ndsl/utils/temp_define.h"
#include "ndsl/net/TcpAcceptor.h"
#include "ndsl/net/TcpClient.h"

using namespace ndsl;
using namespace net;

bool rrecv = false;

static void fun1(void *param) { rrecv = true; }

TEST_CASE("net/TcpAcceptor")
{
    SECTION("start handleRead")
    {
        // 启动服务
        // 初始化EPOLL
        EventLoop loop;
        REQUIRE(loop.init() == S_OK);

        // 初始化tcpAcceptor
        TcpAcceptor *pAc = new TcpAcceptor(fun1, &loop);
        REQUIRE(pAc->start() == S_OK);

        // 启动一个客户端
        TcpClient *pCli = new TcpClient();
        REQUIRE(pCli->onConnect() == S_OK);

        // 添加中断
        loop.quit();
        REQUIRE(loop.loop() == S_OK);

        // // 测试是否接收到了客户的连接
        REQUIRE(rrecv == true);
    }
}