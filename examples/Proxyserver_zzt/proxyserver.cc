/**
 * @file proxyserver.cc
 * @brief
 *
 * @author zzt
 * @emial 429834658@qq.com
 **/
#include <netdb.h>
#include "ndsl/net/TcpConnection.h"
#include "ndsl/net/EventLoop.h"
#include "ndsl/net/TcpAcceptor.h"
#include "ndsl/net/SocketAddress.h"
#include "Httphandler.h"
using namespace ndsl;
using namespace net;
Multiplexer *multi2s = NULL;
int main()
{
    set_ndsl_log_sinks(
        LOG_SOURCE_ENTITY | LOG_SOURCE_EVENTLOOP | LOG_SOURCE_TCPCONNECTION |
            LOG_SOURCE_TCPCHANNEL | LOG_SOURCE_TCPACCETPOR,
        LOG_OUTPUT_FILE);
    // 启动服务
    EventLoop loop;
    loop.init();

    // 连接到算术服务器
    struct SocketAddress4 mathserveraddr("127.0.0.1", 9999);
    TcpConnection *conn2s;
    TcpClient *pCli = new TcpClient();
    conn2s = pCli->onConnect(&loop, true, &mathserveraddr);

    multi2s = new Multiplexer(conn2s);
    Entity *client = new Entity(
        1, Httphandler::disposeServerMsg, multi2s); // 插入entity在本地multi

    // 准备接收来自浏览器的连接
    struct SocketAddress4 proservaddr("0.0.0.0", 8080);
    TcpAcceptor *tAc = new TcpAcceptor(&loop);
    tAc->start(proservaddr);

    struct sockaddr_in rservaddr;
    bzero(&rservaddr, sizeof(rservaddr));
    socklen_t addrlen;

    TcpConnection *conn2c = new TcpConnection();
    tAc->onAccept(
        conn2c, (SA *) &rservaddr, &addrlen, Httphandler::beginProxy, conn2c);

    // TcpConnection *conn22 = new TcpConnection();
    // tAc->onAccept(
    //     conn22, (SA *) &rservaddr, &addrlen, Httphandler::beginProxy,
    //     conn22);

    loop.loop(&loop);
    return 0;
}