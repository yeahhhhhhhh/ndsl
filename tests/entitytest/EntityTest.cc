/**
 * @file EntityTest.cc
 * @brief
 * 实体的测试
 *
 * @author zzt
 * @emial 429834658@qq.com
 **/
#include "ndsl/net/Entity.h"
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
#include <string>
#include "Protbload.pb.h"

using namespace ndsl;
using namespace net;
using namespace Protbload;

void servercallbak(Multiplexer *Multiplexer, char *data, int len, int ero)
{
    printf("********server callback********\n");
    Protbload::ADD *addmessage = new Protbload::ADD;
    addmessage->ParseFromString(data);
    printf("agv1:%d   agv2:%d \n", addmessage->agv1(), addmessage->agv2());

    std::string fstr;
    Protbload::RESULT *resultmessage = new Protbload::RESULT;
    resultmessage->set_answer(addmessage->agv1() + addmessage->agv2());
    resultmessage->SerializeToString(&fstr);
    int flen = fstr.size();
    Multiplexer->sendMessage(10, flen, fstr.c_str());
}

void clientcallbak(Multiplexer *Multiplexer, char *data, int len, int ero)
{
    printf("********client callback********\n");
    Protbload::RESULT *resultmessage = new Protbload::RESULT;
    resultmessage->ParseFromString(data);
    printf("result==%d \n", resultmessage->answer());
}

bool flag2 = false;

void fun2(void *a) { flag2 = true; }
int main()
{
    // 启动服务
    // 初始化EPOLL
    EventLoop loop;
    loop.init();

    // unsigned short p = 8888;
    struct SocketAddress4 servaddr("0.0.0.0", 8456);

    TcpAcceptor *tAc = new TcpAcceptor(&loop);
    tAc->start(servaddr);

    // 准备接收的数据结构
    struct sockaddr_in rservaddr;
    bzero(&rservaddr, sizeof(rservaddr));
    socklen_t addrlen;

    TcpConnection *Conn = new TcpConnection(tAc);
    Conn->onAccept(Conn, (SA *) &rservaddr, &addrlen, fun2, NULL);

    // 启动一个客户端
    struct SocketAddress4 clientservaddr("127.0.0.1", 8456);
    TcpConnection *serverconn;
    TcpClient *pCli = new TcpClient();
    serverconn = pCli->onConnect(&loop, true, clientservaddr);
    printf("success \n");
    // 添加中断
    loop.quit();
    loop.loop(&loop);

    Multiplexer *clientmulti = new Multiplexer(Conn);

    Multiplexer *servermulti = new Multiplexer(serverconn);

    loop.loop(&loop);

    /******
     * addInsertwork()测试
     *****/
    int clientid = 10;
    int serverid = 12;
    Entity *client = new Entity(clientid, clientcallbak, clientmulti);
    client->pri();
    Entity *server = new Entity(serverid, servercallbak, servermulti);
    server->pri();

    loop.loop(&loop);
    /*********************************
     * 客户端服务器实体测试：
     ********************************/
    int a, b;
    printf("input the agv1 and agv2 of ADD: \n");
    scanf("%d %d", &a, &b);
    std::string pstr;
    Protbload::ADD *addmessage = new Protbload::ADD;
    addmessage->set_agv1(a);
    addmessage->set_agv2(b);
    addmessage->SerializeToString(&pstr);
    int mlen = pstr.size();
    printf("the size of pstr is %d\n", mlen);

    client->multiplexer_->sendMessage(serverid, mlen, pstr.c_str());
    printf("sendMessage!\n");
    loop.loop(&loop);
    loop.loop(&loop);
    return 0;
}