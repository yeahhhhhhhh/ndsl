/*
 * File: TestTcpConnection.cc
 * brief:
 *
 * Author: gyz
 * Email: mni_gyz@163.com
 * Last Modified: Thursday, 29th November 2018 3:30:43 pm
 */

// #include "../catch.hpp"
#include "ndsl/net/EventLoop.h"
#include "ndsl/net/Epoll.h"
#include "ndsl/net/TcpChannel.h"
#include "ndsl/net/TcpConnection.h"
#include "ndsl/utils/temp_define.h"
#include <cstring>
#include <cstdio>
#include <sys/eventfd.h>
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <unistd.h>
using namespace std;

using namespace ndsl;
using namespace net;

int initserver()
{
    int listenfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);

    // server
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    bind(listenfd, (SA *) &servaddr, sizeof(servaddr));
    listen(listenfd, LISTENQ);

    // client
    inet_pton(AF_INET, "192.168.1.1", &servaddr.sin_addr);
    connect(listenfd, (SA *) &servaddr, sizeof(servaddr));

    return listenfd;
}

int main(int argc, char const *argv[])
{
    // 初始化socket
    // int fd = init();

    // 初始化EPOLL
    Epoll ep;
    ep.init();
    EventLoop loop(&ep);
    loop.init();

    // 初始化 TcpConnection
    int fd = 12;
    cout << "test fd = " << fd << endl;
    TcpConnection pConn(fd, &loop);

    // 写数据过去
    write(fd, "hello", sizeof("hello"));
    loop.quit();
    loop.loop();

    char buf[MAXLINE];
    memset(buf, 0, sizeof(buf));
    read(fd, buf, MAXLINE);

    printf("main buf = %s\n", buf);

    // REQUIRE(strcmp(buf, "received") == 0);

    // 停止loop循环
    //
    // REQUIRE(loop.loop() == S_OK);

    return 0;
}
