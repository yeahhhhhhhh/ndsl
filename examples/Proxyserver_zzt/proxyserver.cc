/**
 * @file proxyserver.cc
 * @brief
 *
 * @author zzt
 * @emial 429834658@qq.com
 **/
#include <netdb.h>
#include "ndsl/net/Entity.h"
#include "ndsl/net/Multiplexer.h"
#include "ndsl/net/TcpConnection.h"
#include "ndsl/net/TcpClient.h"
#include "ndsl/net/EventLoop.h"
#include "ndsl/net/TcpAcceptor.h"
#include "ndsl/net/SocketAddress.h"
#include "Httphandler.h"
#include "./var.h"
using namespace ndsl;
using namespace net;
// extern entityMap *entitymap;
// printf("enMap = %p\n",Httphandler::enMap);
// class Httphandler;
// void Httphandler::beginProxy(void *para);
int main()
{
    set_ndsl_log_sinks(
        LOG_SOURCE_ENTITY | LOG_SOURCE_MULTIPLEXER | LOG_SOURCE_EVENTLOOP |
            LOG_SOURCE_TCPCONNECTION | LOG_SOURCE_TCPCHANNEL |
            LOG_SOURCE_TCPACCETPOR,
        LOG_OUTPUT_FILE);
    // 启动服务
    EventLoop loop;
    loop.init();

    // 连接到算术服务器
    struct SocketAddress4 mathserveraddr("127.0.0.1", 9999);
    TcpConnection *conn2s;
    TcpClient *pCli = new TcpClient();
    conn2s = pCli->onConnect(&loop, true, &mathserveraddr);
    if (conn2s != NULL)
        LOG(LOG_INFO_LEVEL, LOG_SOURCE_ENTITY, "already connect to server\n");

    struct con *conPtr = new struct con;
    conPtr->multi2s = new Multiplexer(conn2s);
    if (conPtr->multi2s != NULL)
        LOG(LOG_INFO_LEVEL,
            LOG_SOURCE_MULTIPLEXER,
            "already build multiplexer to server\n");
    printf("multi = %p\n", conPtr->multi2s);

    // 准备接收来自浏览器的连接
    struct SocketAddress4 proservaddr("0.0.0.0", 8080);
    TcpAcceptor *tAc = new TcpAcceptor(&loop);
    tAc->start(proservaddr);

    struct sockaddr_in rservaddr;
    bzero(&rservaddr, sizeof(rservaddr));
    socklen_t addrlen;

    TcpConnection *conn2c = new TcpConnection(); // TODO:内存释放
    conPtr->con2c = conn2c;
    printf("con2c = %p\n", conn2c);
    struct hpara *hp = new struct hpara(); // TODO:内存释放
    hp->map = Httphandler::getMap();
    hp->conn = conPtr;
    hp->tAc = tAc;
    tAc->onAccept(
        conn2c,
        (SA *) &rservaddr,
        &addrlen,
        Httphandler::beginProxy,
        (void *) hp);

    // TcpConnection *conn22 = new TcpConnection();
    // tAc->onAccept(
    //     conn22, (SA *) &rservaddr, &addrlen, Httphandler::beginProxy,
    //     conn22);

    loop.loop(&loop);
    return 0;
}