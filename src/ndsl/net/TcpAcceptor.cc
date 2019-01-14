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

#include "ndsl/config.h"
#include "ndsl/net/TcpAcceptor.h"
#include "ndsl/net/SocketAddress.h"
#include "ndsl/net/TcpConnection.h"
#include "ndsl/utils/Log.h"

namespace ndsl {
namespace net {

TcpAcceptor::TcpAcceptor(EventLoop *pLoop)
    : listenfd_(-1)
    , pLoop_(pLoop)
    , pTcpChannel_(NULL)
{
    info.inUse_ = false;

    // 将测试用回调函数置为空
    cb_ = NULL;
}

TcpAcceptor::~TcpAcceptor() { delete pTcpChannel_; }

// 测试专用构造函数
TcpAcceptor::TcpAcceptor(Callback cb, EventLoop *pLoop)
    : listenfd_(-1)
    , pLoop_(pLoop)
    , pTcpChannel_(NULL)
    , cb_(cb)
{
    info.inUse_ = false;
}

int TcpAcceptor::setInfo(
    TcpConnection *pCon,
    struct sockaddr *addr,
    socklen_t *addrlen,
    Callback cb,
    void *param)
{
    memset(&info, 0, sizeof(struct Info));

    info.pCon_ = pCon;
    info.addr_ = addr;
    info.addrlen_ = addrlen;
    info.cb_ = cb;
    info.param_ = param;
    info.inUse_ = true;

    return S_OK;
}

int TcpAcceptor::start(struct SocketAddress4 servaddr)
{
    int n = createAndListen(servaddr);
    if (n < 0) {
        LOG(LOG_INFO_LEVEL, LOG_SOURCE_TCPACCETPOR, "createAndListen fail\n");
        return S_FALSE;
    }

    pTcpChannel_ = new TcpChannel(listenfd_, pLoop_);
    if (pTcpChannel_ == NULL) {
        LOG(LOG_INFO_LEVEL, LOG_SOURCE_TCPACCETPOR, "new TcpChannel fail\n");
        return S_FALSE;
    } else {
        pTcpChannel_->setCallBack(handleRead, NULL, this);
        pTcpChannel_->enroll(false);
    }

    return S_OK;
}

int TcpAcceptor::createAndListen(struct SocketAddress4 servaddr)
{
    listenfd_ = socket(AF_INET, SOCK_STREAM, 0);
    if (listenfd_ < 0) {
        LOG(LOG_INFO_LEVEL, LOG_SOURCE_TCPACCETPOR, "socket fail\n");
        return S_FALSE;
    }

    // 在这初始化 IP+PORT
    // struct SocketAddress4 servaddr;

    // 设置非阻塞
    fcntl(listenfd_, F_SETFL, O_NONBLOCK);
    // setsockopt(listenfd_, SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on));

    // servaddr.setPort(SERV_PORT);

    if (-1 ==
        bind(listenfd_, (struct sockaddr *) &servaddr, sizeof(servaddr))) {
        LOG(LOG_INFO_LEVEL, LOG_SOURCE_TCPACCETPOR, "TcpAcceptor bind error");
        LOG(LOG_INFO_LEVEL, LOG_SOURCE_TCPACCETPOR, strerror(errno));
        return S_FALSE;
    }

    if (-1 == listen(listenfd_, LISTENQ)) {
        LOG(LOG_INFO_LEVEL,
            LOG_SOURCE_TCPACCETPOR,
            "TcpAcceptor listen error\n");
        return S_FALSE;
    }

    return S_OK;
}

int TcpAcceptor::handleRead(void *pthis)
{
    TcpAcceptor *pThis = static_cast<TcpAcceptor *>(pthis);
    int connfd;
    struct sockaddr_in cliaddr;
    socklen_t clilen = sizeof(struct sockaddr_in);
    connfd = accept(
        pThis->listenfd_, (struct sockaddr *) &cliaddr, (socklen_t *) &clilen);

    if (connfd > 0) {
        // 连接成功
        LOG(LOG_INFO_LEVEL,
            LOG_SOURCE_TCPACCETPOR,
            "TcpAcceptor::connect succ\n");
    } else {
        // 连接失败
        LOG(LOG_INFO_LEVEL, LOG_SOURCE_TCPACCETPOR, "connect fail\n");
        return S_FALSE;
    }

    // 设置非阻塞io
    fcntl(connfd, F_SETFL, O_NONBLOCK);

    if (pThis->info.inUse_) {
        ((pThis->info).pCon_)
            ->createChannel(connfd, pThis->pTcpChannel_->pLoop_);
        pThis->info.addr_ = (struct sockaddr *) &cliaddr;
        pThis->info.addrlen_ = (socklen_t *) &clilen;

        if (pThis->info.cb_ != NULL) pThis->info.cb_(pThis->info.param_);

        // proactor模式，需要循环注册
        pThis->info.inUse_ = false;
    }

    // 测试专用
    if (pThis->cb_ != NULL) pThis->cb_(NULL);

    return S_OK;
}

} // namespace net
} // namespace ndsl
