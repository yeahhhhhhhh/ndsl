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

void servercallbak(Multiplexer *Multiplexer, char *data, int len, int ero)
{
    printf("********server callback********\n");
    Protbload::ADD *addmessage = new Protbload::ADD;
    addmessage->ParseFromString(data);
    printf(
        "agv1:%d   agv2:%d \n", addmessage->agv1(), (int) addmessage->agv2());

    std::string fstr;
    Protbload::RESULT *resultmessage = new Protbload::RESULT;
    resultmessage->set_answer(addmessage->agv1() + addmessage->agv2());
    addmessage->SerializeToString(&fstr);
    int flen = fstr.size();
    printf("the size of pstr is %d\n", flen);

    Multiplexer->sendMessage(10, flen, fstr.c_str());
}

void clientcallbak(Multiplexer *Multiplexer, char *data, int len, int ero)
{
    printf("********client callback********\n");
    Protbload::RESULT *resultmessage = new Protbload::RESULT;
    resultmessage->ParseFromString(data);

    printf("result==%d \n", resultmessage->answer());
}

bool flag = false;

void fun1(void *a) { flag = true; }

TEST_CASE("Entitytest")
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
    TcpConnection *serverconn = pCli->onConnect(&loop);
    printf("return servercon \n");
    // REQUIRE(pCli->onConnect(&loop) == S_OK);

    // 添加中断
    loop.quit();
    REQUIRE(loop.loop(&loop) == S_OK);
    printf("before build two multi \n");
    if (Conn == serverconn)
        printf("conn==servercon\n");
    else
        printf("no equal\n");
    Multiplexer *clientmulti = new Multiplexer(Conn);
    Multiplexer *servermulti = new Multiplexer(serverconn);
    printf("hhhbuild two multi \n");
    REQUIRE(loop.loop(&loop) == S_OK);
    printf("build two multi \n");
    SECTION("entity")
    {
        /******
         * addInsertwork()测试
         *****/
        int clientid = 10;
        int serverid = 12;
        Entity *client = new Entity(clientid, clientcallbak, clientmulti);
        client->pri();
        Entity *server = new Entity(serverid, servercallbak, servermulti);
        server->pri();
        REQUIRE(loop.loop(&loop) == S_OK);

        /*********************************
         * 客户端服务器实体测试：
         ********************************/
        std::string pstr;
        Protbload::ADD *addmessage = new Protbload::ADD;
        addmessage->set_agv1(111);
        addmessage->set_agv2(222);
        addmessage->SerializeToString(&pstr);
        int mlen = pstr.size();
        printf("the size of pstr is %d\n", mlen);

        client->multiplexer_->sendMessage(serverid, mlen, pstr.c_str());
        printf("sendMessage!\n");
        loop.quit();
        REQUIRE(loop.loop(&loop) == S_OK);
        sleep(3);
        loop.quit();
        REQUIRE(loop.loop(&loop) == S_OK);
    }
}