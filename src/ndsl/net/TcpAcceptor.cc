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

TcpAcceptor::~TcpAcceptor() { delete pTcpChannel_; }

TcpAcceptor::TcpAcceptor(
    int listenfd,
    EventLoop *pLoop,
    TcpConnection *pCon,
    struct sockaddr *addr,
    socklen_t *addrlen,
    Callback cb,
    void *param,
    TcpConnection *pCbCon)
    : listenfd_(-1)
    , pLoop_(pLoop)
    , info.pCon_(pCon)
    , info.addr_(addr)
    , info.addrlen_(addrlen)
    , info.cb_(cb)
    , info.param_(param)
    , info.inUse_(true)
{}

int TcpAcceptor::start()
{
    listenfd_ = createAndListen();
    pTcpChannel_ = new TcpChannel(listenfd_, pLoop_);
    pTcpChannel_->setCallBack(this);
    pTcpChannel_->enableReading();
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
        // cout << "bind error, errno:" << errno << endl;
    }

    if (-1 == listen(listenfd_, LISTENQ)) {
        // cout << "listen error, errno:" << errno << endl;
    }

    return listenfd_;
}

static int TcpAcceptor::handleRead()
{
    int connfd;
    struct sockaddr_in cliaddr;
    socklen_t clilen = sizeof(struct sockaddr_in);
    connfd =
        accept(listenfd_, (struct sockaddr *) &cliaddr, (socklen_t *) &clilen);
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
    TcpConnection *tCon = pTcpChannel_->newConnection(connfd);

    if (info.inUse_) {
        info.pCon_ = tCon;
        info.addr_ = (struct sockaddr *) &cliaddr;
        info.addrlen_ = (socklen_t *) &clilen;
        if (info.cb_ != NULL) info.cb_(info.param_);
        pTcpChannel_->disableReading();

        this->~TcpAcceptor();
    }
}

} // namespace net
} // namespace ndsl
