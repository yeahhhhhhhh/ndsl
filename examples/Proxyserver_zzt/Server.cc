/**
 * @file server.cc
 * @brief
 *
 * @author zzt
 * @emial 429834658@qq.com
 **/
#include "ndsl/net/Entity.h"
#include "ndsl/net/Multiplexer.h"
#include "ndsl/net/TcpConnection.h"
#include "ndsl/net/EventLoop.h"
#include "ndsl/net/TcpAcceptor.h"
#include "ndsl/net/SocketAddress.h"
#include "Protbload.pb.h"
#include "ndsl/net/TcpClient.h"

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

int main()
{
    // 启动服务
    EventLoop loop;
    loop.init();

    struct SocketAddress4 servaddr("0.0.0.0", 8080);
    TcpAcceptor *tAc = new TcpAcceptor(&loop);
    tAc->start(servaddr);
    printf("111111111111\n");
    // 准备接收的数据结构
    struct sockaddr_in rservaddr;
    bzero(&rservaddr, sizeof(rservaddr));
    socklen_t addrlen;
    printf("22222222222222\n");
    TcpConnection *conn2c = new TcpConnection();
    tAc->onAccept(conn2c, (SA *) &rservaddr, &addrlen, NULL, NULL);

    //暂时
    // struct SocketAddress4 clientservaddr("127.0.0.1", 8080);
    // TcpConnection *serverconn;
    // TcpClient *pCli = new TcpClient();
    // serverconn = pCli->onConnect(&loop, true, &clientservaddr);
    // Multiplexer *servermulti = new Multiplexer(serverconn);
    // Entity *server2 = new Entity(99, servercallbak, servermulti);
    // server2->pri();

    printf("333333333333\n");
    Multiplexer *smulti = new Multiplexer(conn2c);
    printf("444444444444\n");
    Entity *server = new Entity(1, servercallbak, smulti);
    server->pri();

    loop.loop(&loop);
    return 0;
}