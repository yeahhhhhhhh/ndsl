/**
 * @file TcpAccepter.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#include "ndsl/utils/temp_define.h"
#include "ndsl/net/TcpAcceptor.h"

namespace ndsl {
namespace net {

TcpAcceptor::TcpAcceptor(int listenfd, EventLoop *pLoop)
    : listenfd_(-1)
    , pLoop_(pLoop)
{}

int TcpAcceptor::start()
{
    listenfd_ = createAndListen();
    pTcpChannel_ = new TcpChannel(listenfd_, pLoop_);
    pTcpChannel_->setCallBack(this);
}

int TcpAcceptor::createAndListen()
{
    // int on = 1;
    listenfd_ = socket(AF_INET, SOCK_STREAM, 0);

    // struct sockaddr_in serevaddr;
    struct SocketAddress4 servaddr();

    // 设置非阻塞
    fcntl(listenfd_, F_SETFL, O_NONBLOCK);
    // setsockopt(listenfd_, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    servaddr.setPort(SERV_PORT);

    // servaddr.sin_family = AF_INET;
    // servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    // servaddr.sin_port = htons(SERV_PORT);

    if (-1 ==
        bind(listenfd_, (struct sockaddr *) &servaddr, sizeof(servaddr))) {
        cout << "bind error, errno:" << errno << endl;
    }

    if (-1 == listen(listenfd_, LISTENQ)) {
        cout << "listen error, errno:" << errno << endl;
    }

    return listenfd_;
}

int TcpAcceptor::handleRead()
{
    int connfd;
    struct sockaddr_in cliaddr;
    socklen_t clilen = sizeof(struct sockaddr_in);
    connfd = accept(listenfd_, (sockaddr *) &cliaddr, (socklen_t *) &clilen);
    if (connfd > 0) {
        // 连接成功

        // cout << "new connection from "
        //      << "[" << inet_ntoa(cliaddr.sin_addr) << ":"
        //      << ntohs(cliaddr.sin_port) << "]"
        //      << " new socket fd:" << connfd << endl;
    } else {
        // 连接失败

        // cout << "accept error, connfd:" << connfd << " errno:" << errno <<
        // endl;
    }

    // 设置非阻塞io
    fcntl(connfd, F_SETFL, O_NONBLOCK);

    pTcpChannel_->newConnection(connfd);
}

// 空函数 无此功能
int TcpAcceptor::handleWrite() {}

} // namespace net
} // namespace ndsl
