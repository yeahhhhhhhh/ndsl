////
// @file UnixAcceptor.cc
// @brief
// unixacceptor shixian
//
// @author ranxaingjun
// @email ransianshen@gmail.com
//
#include <sys/socket.h>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <string>
#include <cstdio>
#include "../../../include/ndsl/utils/temp_define.h"
#include "../../../include/ndsl/net/UnixAcceptor.h"
#include "../../../include/ndsl/net/SocketAddressUn.h"

using namespace std;

namespace ndsl {
namespace net {

UnixAcceptor::UnixAcceptor(EventLoop *pLoop)
    : listenfd_(-1)
    , pLoop_(pLoop)
{}

UnixAcceptor::~UnixAcceptor() { delete pUnixChannel_; }

UnixAcceptor::UnixAcceptor(Callback cb, EventLoop *pLoop) : pLoop_(pLoop), cb_(cb)
{}

UnixAcceptor::UnixAcceptor(
    EventLoop *pLoop,
    UnixConnection *pCon,
    struct sockaddr *addr,
    socklen_t *addrlen,
    Callback cb,
    void *param)
    : listenfd_(-1)
    , pLoop_(pLoop)
{
    info.pCon_ = pCon;
    info.addr_ = addr;
    info.addrlen_ = addrlen;
    info.cb_ = cb;
    info.param_ = param;
    info.inUse_ = true;
}

int UnixAcceptor::start(const string& path)
{
    listenfd_ = createAndListen( path);
    pUnixChannel_ = new UnixChannel(listenfd_, pLoop_);
    pUnixChannel_->setCallBack(handleRead, NULL, this);
    pUnixChannel_->regist(false);
    // pUnixChannel_->enableReading();

    return S_OK;
}

int UnixAcceptor::createAndListen(const string& path)
{
    listenfd_ = socket(AF_LOCAL, SOCK_STREAM, 0);
    struct SocketAddressUn servaddr(path);

	// in case the address was used
	unlink(path.c_str());
    // 设置非阻塞
    fcntl(listenfd_, F_SETFL, O_NONBLOCK);

    if (-1 ==
        bind(listenfd_, (struct sockaddr *) &servaddr, sizeof(servaddr))) {
    }

    if (-1 == listen(listenfd_, LISTENQ)) {
    }

    return listenfd_;
}

int UnixAcceptor::handleRead(void *pthis)
{
	UnixAcceptor *pThis = static_cast<UnixAcceptor *>(pthis);

    int connfd;
    struct sockaddr_un cliaddr;
    socklen_t clilen = sizeof(struct sockaddr_un);
    connfd =
        accept(pThis->listenfd_, (struct sockaddr *) &cliaddr, (socklen_t *) &clilen);
    if (connfd > 0) {
        // 连接成功
    } else {
        // 连接失败

    }

    // 设置非阻塞io
    fcntl(connfd, F_SETFL, O_NONBLOCK);
    UnixConnection *uCon =pThis-> pUnixChannel_->newConnection(connfd);

    if (pThis->info.inUse_) {
        pThis->info.pCon_ = uCon;
        pThis->info.addr_ = (struct sockaddr *) &cliaddr;
        pThis->info.addrlen_ = (socklen_t *) &clilen;
        if (pThis->info.cb_ != NULL) pThis->info.cb_(pThis->info.param_);
        pThis->pUnixChannel_->disableReading();

        pThis->~UnixAcceptor();
    }

	// test use
	pThis->cb_(NULL);
    return S_OK;
}

// 空函数 无功能
// int UnixAcceptor::handleWrite() { return S_OK; }

} // namespace net
} // namespace ndsl
