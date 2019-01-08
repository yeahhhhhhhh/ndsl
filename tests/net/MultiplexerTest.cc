/**
 * @file MultiplexerTest.cc
 * @brief
 * Multiplexertest
 *
 * @author zzt
 * @email 429834658@qq.com
 */

#include "../catch.hpp"
#include "ndsl/net/Multiplexer.h"
#include "ndsl/net/TcpConnection.h"
#include "ndsl/net/TcpChannel.h"
#include "ndsl/net/EventLoop.h"
#include "ndsl/net/TcpAcceptor.h"
#include "ndsl/net/TcpClient.h"
#include "ndsl/net/Epoll.h"
#include <sys/socket.h>
#include "ndsl/utils/temp_define.h"
#include <cstring>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

using namespace ndsl;
using namespace net;

int id = 11;
static void entitycallbak(char *data, int len, int ero)
{
    printf("********entity callback********\n");
    char *p = data;
    for (int i = 0; i < len; i++) {
        printf("%c", *p);
        p++;
    }
    printf("\n");
}

bool flag = false;

void fun1(void *a) { flag = true; }

TEST_CASE("Mutiplexer/cbmaptest")
{
    // 启动服务
    // 初始化EPOLL
    EventLoop loop;
    REQUIRE(loop.init() == S_OK);

    TcpAcceptor *tAc = new TcpAcceptor(&loop);
    tAc->start();

    // 准备接收的数据结构
    struct sockaddr_in rservaddr;
    bzero(&rservaddr, sizeof(rservaddr));
    socklen_t addrlen;

    TcpConnection *Conn = new TcpConnection(tAc);
    Conn->onAccept(Conn, (SA *) &rservaddr, &addrlen, fun1, NULL);

    // 启动一个客户端
    TcpClient *pCli = new TcpClient();
    REQUIRE(pCli->onConnect() == S_OK);

    // 添加中断
    loop.quit();
    REQUIRE(loop.loop() == S_OK);

    Multiplexer *mymulti = new Multiplexer(Conn);

    // SECTION("addInsertWork")
    // {
    //     int id = 1;
    //     mymulti->addInsertWork(id, entitycallbak);
    // }
    // SECTION("addRemoveWork")
    // {
    //     int id = 1;
    //     mymulti->addRemoveWork(id);
    // }

    SECTION("insert and remove ")
    {
        /******
         * insert()测试
         *****/
        struct para *p1 = new para;
        p1->id = id;
        p1->cb = entitycallbak;
        p1->pthis = mymulti;

        mymulti->insert((void *) p1);
        std::map<int, Multiplexer::Callback>::iterator iter;
        iter = mymulti->cbMap_.find(id);
        REQUIRE(iter != mymulti->cbMap_.end());

        printf("insert entity\n");

        /********************************
         * remove()测试
         ********************************/
        // struct para *p2 = new para;
        // p2->id = id;
        // p2->cb = entitycallbak;
        // p2->pthis = mymulti;
        // mymulti->remove((void *) p2);
        // std::map<int, Multiplexer::Callback>::iterator iter2;
        // iter2 = mymulti->cbMap_.find(id);
        // REQUIRE(iter2 == mymulti->cbMap_.end());

        /*********************************
         * dispatch 测试：多个短消息
         ********************************/
        // char data[] = "helloworld";
        // int len = 10;
        // char *buffer = (char *) malloc(sizeof(int) * 2 + sizeof(char) * len);
        // Message *message = reinterpret_cast<struct Message *>(buffer);
        // message->id = htobe32(id);
        // message->len = htobe32(len);
        // memcpy(buffer + sizeof(struct Message), data, len);

        // char *p = buffer;
        // for (int i = 1; i <= 5; i++) //发了5个消息过去
        // {
        //     memcpy(buffer + 18 * i, p, 18);
        // }

        // write(pCli->sockfd_, buffer, 50);
        // printf("writed!\n");
        // REQUIRE(loop.loop() == S_OK);

        // write(pCli->sockfd_, buffer + 50, 40);

        // REQUIRE(loop.loop() == S_OK);

        /*********************************
         * dispatch 测试：一个长消息
         ********************************/
        char data2[] =
            "helloworldhelloworldhelloworldhelloworldhelloworldhelloworld";
        int len2 = 60;
        char *buffer2 = (char *) malloc(sizeof(int) * 2 + sizeof(char) * len2);
        Message *message2 = reinterpret_cast<struct Message *>(buffer2);
        message2->id = htobe32(id);
        message2->len = htobe32(len2);
        memcpy(buffer2 + sizeof(struct Message), data2, len2);

        write(pCli->sockfd_, buffer2, 68);

        REQUIRE(loop.loop() == S_OK);

        write(pCli->sockfd_, buffer2 + 50, 18);

        REQUIRE(loop.loop() == S_OK);

        /*********************************
         * sendMessage测试
         ********************************/
        // char data[] = "helloworld\0";
        // int len = 11;
        // mymulti->sendMessage(id, len, data);

        // char recvBuf[20];
        // loop.quit();
        // REQUIRE(loop.loop() == S_OK);

        // read(pCli->sockfd_, recvBuf, MAXLINE);
        // char *p = recvBuf;
        // for (int i = 0; i < 10; i++) {
        //     printf("%c", *(p + 8));
        //     p++;
        // }
        // printf("\n");
        // REQUIRE(loop.loop() == S_OK);
    }
}