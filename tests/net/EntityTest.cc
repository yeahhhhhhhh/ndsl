/**
 * @file EntityTest.cc
 * @brief
 * 实体的测试
 *
 * @author zzt
 * @emial 429834658@qq.com
 **/
#include "../catch.hpp"
#include "ndsl/net/Entity.h"
#include "ndsl/net/Multiplexer.h"
#include "ndsl/net/TcpConnection.h"
#include "ndsl/net/TcpChannel.h"
#include "ndsl/net/EventLoop.h"
#include "ndsl/net/TcpAcceptor.h"
#include "ndsl/net/TcpClient.h"
#include "ndsl/net/Epoll.h"
#include <sys/socket.h>
#include "ndsl/config.h"
#include <cstring>
#include <arpa/inet.h>
#include <fcntl.h>
#include <unistd.h>
#include <string>
#include "ndsl/net/Protbload.pb.h"

using namespace ndsl;
using namespace net;
using namespace Protbload;

int id = 11;
static void entitycallbak(char *data, int len, int ero)
{
    printf("********entity callback********\n");
    Protbload::ADD *addmessage = new Protbload::ADD;
    addmessage->ParseFromString(data);

    printf(
        "agv1:%d   agv2:%d \n", addmessage->agv1(), (int) addmessage->agv2());
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
    if (pCli->onConnect(&loop) == NULL) printf("kong\n");
    // REQUIRE(pCli->onConnect(&loop) == S_OK);

    // 添加中断
    loop.quit();
    REQUIRE(loop.loop(&loop) == S_OK);

    Multiplexer *mymulti = new Multiplexer(Conn);

    SECTION("insert and remove ")
    {
        /******
         * addInsertwork()测试
         *****/
        Entity *entity1 = new Entity(id, entitycallbak, mymulti);
        entity1->pri();
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
         * 接收消息测试：
         ********************************/
        std::string pstr;
        Protbload::ADD *addmessage = new Protbload::ADD;
        addmessage->set_agv1(111);
        addmessage->set_agv2(222);
        addmessage->SerializeToString(&pstr);
        int mlen = pstr.size();
        printf("the size of pstr is %d\n", mlen);

        char *buffer = (char *) malloc(sizeof(int) * 2 + sizeof(char) * mlen);
        Message *message = reinterpret_cast<struct Message *>(buffer);
        message->id = htobe32(id);
        message->len = htobe32(mlen);
        memcpy(buffer + sizeof(struct Message), pstr.c_str(), mlen);

        write(pCli->sockfd_, buffer, sizeof(int) * 2 + mlen);
        printf("writed!\n");
        REQUIRE(loop.loop(&loop) == S_OK);

        /*********************************
         * dispatch 测试：一个长消息
         ********************************/
        // int id2 = 99;
        // mymulti->addInsertWork(id2, entitycallbak);
        // int len2 = 60;
        // char data2[] =
        //     "helloworldhelloworldhelloworldhelloworldhelloworldhelloworld";

        // char *buffer2 = (char *) malloc(sizeof(int) * 2 + sizeof(char) *
        // len2); Message *message2 = reinterpret_cast<struct Message
        // *>(buffer2); message2->id = htobe32(id2); message2->len =
        // htobe32(len2); memcpy(buffer2 + sizeof(struct Message), data2, len2);

        // write(pCli->sockfd_, buffer2, 40);

        // REQUIRE(loop.loop(&loop) == S_OK);

        // write(pCli->sockfd_, buffer2 + 40, 28);

        // REQUIRE(loop.loop(&loop) == S_OK);

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