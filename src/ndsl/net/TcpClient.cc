/**
 * @file TcpClient.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#include <arpa/inet.h>
#include <errno.h>
#include "ndsl/net/SocketAddress.h"
#include "ndsl/net/TcpClient.h"
#include "ndsl/utils/temp_define.h"
#include "ndsl/utils/Error.h"
#include "ndsl/config.h"

namespace ndsl {
namespace net {

int TcpClient::onConnect(Callback cb)
{
    // 设置回调
    onConnect_ = cb;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // 设置非阻塞
    fcntl(sockfd, F_SETFL, O_NONBLOCK);

    servaddr_.setPort(SERV_PORT);

    inet_pton(AF_INET, "127.0.0.1", &servaddr_.sin_addr);

    int n;
    if ((n = connect(sockfd, (SA *) &servaddr_, sizeof(servaddr_))) < 0) {
        if (errno == EALREADY) {
            return sockfd;
        } else {
            // connect出错 由于还没有建立连接，故返回-1
            errorHandle_(errno, -1);
            return S_FALSE;
        }
    }
    // createChannel(sockfd, );
    return sockfd;
}

int TcpClient::disConnect() {}

int TcpClient::createChannel(int sockfd, EventLoop *pLoop)
{
    pTcpChannel_ = new TcpChannel(sockfd, pLoop);
    pTcpChannel_->setCallBack(handleConnect, NULL, this);
    pTcpChannel_->enrollIn(true);

    return S_OK;
}

int TcpClient::handleConnect(void *pthis)
{
    TcpConnection *pThis = static_cast<TcpConnection *>(pthis);
    int sockfd = pThis->pTcpChannel_->getFd();
    if (sockfd < 0) { return S_FALSE; }

    int n;
    if ((n = connect(
             sockfd, (SA *) &(pThis->servaddr_), sizeof(pThis->servaddr_))) <
        0) {
        // 出错 通知用户
        pThis->errorHandle_(errno, pThis->pTcpChannel_->getFd());
        return S_FALSE;
    } else {
        // 连接成功 通知用户
        pThis->onConnect_();
        return S_OK;
    }
}

// pingpong测试专用 TODO:
int TcpClient::handleRead(void *pthis)
{
    TcpConnection *pThis = static_cast<TcpConnection *>(pthis);
    int sockfd = pThis->pTcpChannel_->getFd();
    if (sockfd < 0) { return S_FALSE; }
}

// 错误处理 交给用户
int TcpClient::onError(ErrorHandle cb)
{
    errorHandle_ = cb;
    return S_OK;
}

} // namespace net
} // namespace ndsl
