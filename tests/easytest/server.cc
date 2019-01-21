#include "ndsl/net/EventLoop.h"
#include "ndsl/net/Epoll.h"
#include "ndsl/net/TcpChannel.h"
#include "ndsl/net/TcpConnection.h"
#include "ndsl/net/TcpAcceptor.h"
#include "ndsl/net/TcpClient.h"
#include "ndsl/utils/Log.h"
#include "ndsl/config.h"
#include "ndsl/utils/Error.h"
#include "ndsl/net/SocketAddress.h"
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

using namespace ndsl;
using namespace net;

int main(int argc, char const *argv[])
{
    set_ndsl_log_sinks(LOG_SOURCE_TCPCONNECTION, LOG_OUTPUT_TER);

    EventLoop loop;
    loop.init();

    // 准备客户端的接受参数 默认全ip接受 端口6666
    struct SocketAddress4 servaddr("0.0.0.0", 6666);

    TcpAcceptor *tAc = new TcpAcceptor(&loop);
    tAc->start(servaddr);

    // 准备接收的数据结构
    struct sockaddr_in rservaddr;
    bzero(&rservaddr, sizeof(rservaddr));
    socklen_t addrlen;

    // TODO: 逻辑需要再调整，其实Acceptor不需要Connection
    // 可以直接在Acceptor里面弄一个函数 setAcceptInfo() 把信息传进去
    TcpConnection *Conn = new TcpConnection();
    tAc->onAccept(Conn, (SA *) &rservaddr, &addrlen, NULL, NULL);

    char *buf = (char *) malloc(sizeof(char) * 2048);
    ssize_t len;
    Conn->onRecv(buf, &len, 0, NULL, NULL);

    // loop.quit();
    loop.loop(&loop);

    return 0;
}
