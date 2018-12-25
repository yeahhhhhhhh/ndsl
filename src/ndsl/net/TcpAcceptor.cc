/**
 * @file TcpAccepter.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#include <sys/socket.h>
#include <fcntl.h>
#include <string.h>

#include "ndsl/utils/temp_define.h"
#include "ndsl/net/TcpAcceptor.h"
#include "ndsl/net/SocketAddress.h"
#include "ndsl/net/TcpConnection.h"

namespace ndsl {
namespace net {

TcpAcceptor::TcpAcceptor(EventLoop *pLoop)
    : listenfd_(-1)
    , pLoop_(pLoop)
{
    info.inUse_ = false;
}

TcpAcceptor::~TcpAcceptor() { delete pTcpChannel_; }

// 测试专用构造函数
TcpAcceptor::TcpAcceptor(Callback cb, EventLoop *pLoop)
    : listenfd_(-1)
    , pLoop_(pLoop)
    , cb_(cb)
{
    info.inUse_ = false;
}

// TcpAcceptor::TcpAcceptor(
//     EventLoop *pLoop,
//     TcpConnection *pCon,
//     struct sockaddr *addr,
//     socklen_t *addrlen,
//     Callback cb,
//     void *param)
//     : listenfd_(-1)
//     , pLoop_(pLoop)
// {
//     info.pCon_ = pCon;
//     info.addr_ = addr;
//     info.addrlen_ = addrlen;
//     info.cb_ = cb;
//     info.param_ = param;
//     info.inUse_ = true;
// }

int TcpAcceptor::setInfo(
    TcpConnection *pCon,
    struct sockaddr *addr,
    socklen_t *addrlen,
    Callback cb,
    void *param)
{
    info.pCon_ = pCon;
    info.addr_ = addr;
    info.addrlen_ = addrlen;
    info.cb_ = cb;
    info.param_ = param;
    info.inUse_ = true;

    return S_OK;
}

TcpChannel *TcpAcceptor::getTcpChannel() { return pTcpChannel_; }

int TcpAcceptor::start()
{
    createAndListen();
    pTcpChannel_ = new TcpChannel(listenfd_, pLoop_);
    pTcpChannel_->setCallBack(handleRead, NULL, this);
    pTcpChannel_->regist(false);
    pTcpChannel_->enableReading();

    return S_OK;
}

int TcpAcceptor::createAndListen()
{
    // int on = 1;
    listenfd_ = socket(AF_INET, SOCK_STREAM, 0);

    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    // struct SocketAddress4 servaddr;

    // 设置非阻塞
    fcntl(listenfd_, F_SETFL, O_NONBLOCK);
    // setsockopt(listenfd_, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    // servaddr.setPort(SERV_PORT);

    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);

    if (-1 ==
        bind(listenfd_, (struct sockaddr *) &servaddr, sizeof(servaddr))) {
        printf("TcpAcceptor bind error\n");

        // cout << "bind error, errno:" << errno << endl;
    }

    if (-1 == listen(listenfd_, LISTENQ)) {
        printf("TcpAcceptor listen error\n");
        // cout << "listen error, errno:" << errno << endl;
    }

    return S_OK;
}

int TcpAcceptor::handleRead(void *pthis)
{
    TcpAcceptor *pThis = static_cast<TcpAcceptor *>(pthis);
    printf("TcpAcceptor.cc handleRead()\n");

    int connfd;
    struct sockaddr_in cliaddr;
    socklen_t clilen = sizeof(struct sockaddr_in);
    connfd = accept(
        pThis->listenfd_, (struct sockaddr *) &cliaddr, (socklen_t *) &clilen);
    if (connfd > 0) {
        // 连接成功

        printf("connect succ\n");

        // cout << "new connection from "
        //      << "[" << inet_ntoa(cliaddr.sin_addr) << ":"
        //      << ntohs(cliaddr.sin_port) << "]"
        //      << " new socket fd:" << connfd << endl;
    } else {
        printf("connect fail\n");
        // 连接失败

        // cout << "accept error, connfd:" << connfd << " errno:" << errno <<
        // endl;
    }

    // 设置非阻塞io
    fcntl(connfd, F_SETFL, O_NONBLOCK);
    // TcpConnection *tCon = pThis->pTcpChannel_->newConnection(connfd, this);

    if (pThis->info.inUse_) {
        ((pThis->info).pCon_)
            ->createChannel(connfd, pThis->pTcpChannel_->getEventLoop());
        pThis->info.addr_ = (struct sockaddr *) &cliaddr;
        pThis->info.addrlen_ = (socklen_t *) &clilen;
        if (pThis->info.cb_ != NULL) pThis->info.cb_(pThis->info.param_);
        pThis->pTcpChannel_->disableReading();
    }

    // 测试专用
    if (pThis->cb_ != NULL) pThis->cb_(NULL);

    return S_OK;
}

} // namespace net
} // namespace ndsl
