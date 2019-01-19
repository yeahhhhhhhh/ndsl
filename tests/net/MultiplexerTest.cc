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
#include "ndsl/net/SocketAddress.h"
#include <sys/socket.h>
#include "ndsl/config.h"
#include <cstring>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>

using namespace ndsl;
using namespace net;

#define PORT 7878

int id = 11;
static void
entitycallbak(Multiplexer *Multiplexer, char *data, int len, int ero)
{
    printf("********entity callback********\n");
    char *p = data;
    for (int i = 0; i < len; i++) {
        printf("%c", *p);
        p++;
    }
    printf("\n");
}

bool flag3 = false;

void fun3(void *a) { flag3 = true; }

TEST_CASE("Mutiplexer/cbmaptest")
{
    // 启动服务
    // 初始化EPOLL
    EventLoop loop;
    REQUIRE(loop.init() == S_OK);

    struct SocketAddress4 servaddr("0.0.0.0", PORT);

    TcpAcceptor *tAc = new TcpAcceptor(&loop);
    tAc->start(servaddr);

    // 准备接收的数据结构
    struct sockaddr_in rservaddr;
    bzero(&rservaddr, sizeof(rservaddr));
    socklen_t addrlen;

    TcpConnection *Conn = new TcpConnection();
    tAc->onAccept(Conn, (SA *) &rservaddr, &addrlen, fun3, NULL);

    // 启动一个客户端
    struct SocketAddress4 clientservaddr("127.0.0.1", PORT);
    TcpClient *pCli = new TcpClient();
    // pCli->onConnect(&loop, true, clientservaddr);
    TcpConnection *clientconn;
    clientconn = pCli->onConnect(&loop, true, &clientservaddr);
    // 添加中断
    loop.quit();
    REQUIRE(loop.loop(&loop) == S_OK);

    Multiplexer *mymulti = new Multiplexer(Conn);
    Multiplexer *multi2 = new Multiplexer(clientconn);

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
        multi2->addInsertWork(id, entitycallbak);
        loop.quit();
        REQUIRE(loop.loop(&loop) == S_OK);

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
        char data[] = "helloworld";
        int len = 10;
        char *buffer =
            (char *) malloc((sizeof(int) * 2 + sizeof(char) * len) * 5);

        Message *message = reinterpret_cast<struct Message *>(buffer);
        message->id = htobe32(id);
        message->len = htobe32(len);
        memcpy(buffer + sizeof(struct Message), data, len);

        char *p = buffer;
        for (int i = 1; i <= 4; i++) //发了5个消息过去
        {
            memcpy(buffer + 18 * i, p, 18);
        }

        write(pCli->sockfd_, buffer, 10);
        loop.quit();
        REQUIRE(loop.loop(&loop) == S_OK);

        write(pCli->sockfd_, buffer + 10, 40);
        loop.quit();
        REQUIRE(loop.loop(&loop) == S_OK);

        write(pCli->sockfd_, buffer + 50, 40);
        loop.quit();
        REQUIRE(loop.loop(&loop) == S_OK);
        /*********************************
         * dispatch 测试：一个长消息
        //  ********************************/
        int id2 = 99;
        mymulti->addInsertWork(id2, entitycallbak);
        loop.quit();
        REQUIRE(loop.loop(&loop) == S_OK);

        int len2 = 60;
        char data2[] =
            "helloworldhelloworldhelloworldhelloworldhelloworldhelloworld";

        char *buffer2 = (char *) malloc(sizeof(int) * 2 + sizeof(char) * len2);
        Message *message2 = reinterpret_cast<struct Message *>(buffer2);
        message2->id = htobe32(id2);
        message2->len = htobe32(len2);
        memcpy(buffer2 + sizeof(struct Message), data2, len2);

        write(pCli->sockfd_, buffer2, 40);
        loop.quit();
        REQUIRE(loop.loop(&loop) == S_OK);

        write(pCli->sockfd_, buffer2 + 40, 28);
        loop.quit();
        REQUIRE(loop.loop(&loop) == S_OK);

        /*********************************
         * sendMessage测试
         ********************************/

        char data3[] = "helloworld";
        int len3 = 10;
        mymulti->sendMessage(id, len3, data3);

        loop.quit();
        REQUIRE(loop.loop(&loop) == S_OK);
    }
}