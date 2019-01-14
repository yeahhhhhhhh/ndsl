////
// @file UdpEndpointTest.cc
// @brief
// 测试UdpEndpoint
//
// @author lanyue
// @email luckylanry@163.com 
//

#define CATCH_CONFIG_MAIN
#include "../catch.hpp"
#include "ndsl/net/UdpChannel.h"
#include "ndsl/net/UdpEndpoint.h"
#include "ndsl/net/EventLoop.h"
#include "ndsl/net/Epoll.h"
#include "ndsl/net/UdpClient.h"
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

bool flag = false;

void fun1(void *a) { flag = true; }

bool flagsend = false;
static void sendTest(void *a) { flagsend = true; }

// bool flagerror = false;
// static void iserror(int a, int b) { flagerror = true; }

// bool flagrecv = false;
// static void recvTest(void *a) { flagrecv = true; }

using namespace ndsl::net;

TEST_CASE("net/UdpEndpoint")
{   
    // 启动服务
    // 初始化EPOLL
    EventLoop loop;
    loop.init();
    int sockfd = socket(AF_LOCAL, SOCK_STREAM, 0);
    // SECTION("createChannel"){
       
    //     //注册udpchannel
    //     REQUIRE(ue.createChannel(sockfd,sendTest,NULL) == 0);
    //     if(fork() == 0){
    //         exit(0);
    //     }
    //     sleep(1);

    //     // 添加中断
    //     loop.quit();
    //     // 开始loop
    //     loop.loop();
    // }
        
    // SECTION("remove"){
       
    //     REQUIRE(ue.createChannel(sockfd,sendTest,NULL) == 0);
    //     if(fork() == 0){
    //         exit(0);
    //     }
    //     sleep(1);

    //     REQUIRE(ue.remove() == 0);
    //     // 添加中断
    //     loop.quit();
    //     // 开始loop
    //     loop.loop();
    // }

    SECTION("onAccept")
    {
        UdpEndpoint ue(&loop);
        ue.createChannel(sockfd,sendTest,NULL);
        // 准备接收的数据结构
        struct sockaddr_in rservaddr;
        bzero(&rservaddr, sizeof(rservaddr));
        // socklen_t addrlen;

        // 启动一个客户端
        UdpClient *pCli = new UdpClient();
        REQUIRE(pCli->start() == S_OK);

        // // 添加中断
        loop.quit();
        REQUIRE(loop.loop(&loop) == S_OK);

        // 测试是否接收到了客户的连接
        REQUIRE(flag == true);

        // // 测试send
        // Conn->onError(iserror);
        // char *sendbuf = (char *) malloc(sizeof(char) * 12);
        // // sendbuf = 'hello world';
        // strcpy(sendbuf, "hello world\0");
        // Conn->onSend(sendbuf, strlen("hello world"), 0, sendTest, NULL);

        // char recvBuf[15];
        // memset(recvBuf, 0, sizeof(recvBuf));
        // read(pCli->sockfd_, recvBuf, MAXLINE);

        // REQUIRE(strcmp("hello world", recvBuf) == 0);
        // REQUIRE(flagsend == true);

        // // 测试onRecv
        // memset(recvBuf, 0, sizeof(recvBuf));
        // size_t len;
        // write(pCli->sockfd_, "hello world", strlen("hello world"));

        // REQUIRE(Conn->onRecv(recvBuf, &len, 0, recvTest, NULL) == S_OK);
        // REQUIRE(len == strlen("hello world"));
        // REQUIRE(flagrecv == true);

        // // 第二次不需要添加中断
        // loop.quit();
        // REQUIRE(loop.loop() == S_OK);
     }
}
