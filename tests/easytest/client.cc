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
#include "ndsl/net/ELThreadpool.h"
#include <cstring>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <fcntl.h>

using namespace ndsl;
using namespace net;

int main(int argc, char const *argv[])
{
    EventLoop loop;
    loop.init();

    // ELThreadpool *threadPool = new ELThreadpool();
    // threadPool->setMaxThreads(1);
    // threadPool->start();

    // EventLoop *loop = threadPool->getNextEventLoop();

    struct SocketAddress4 clientservaddr("127.0.0.1", 6666);
    TcpConnection *pClientConn;
    TcpClient *pCli = new TcpClient();

    pClientConn = pCli->onConnect(&loop, false, &clientservaddr);
    char buf[] = "hello world";
    pClientConn->onSend(buf, strlen(buf), 0, NULL, NULL);

    // sleep(1);

    // close(pCli->sockfd_);
    // loop.quit();
    loop.loop(&loop);

    // threadPool->quit();

    return 0;
}
