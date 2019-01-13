/**
 * @file TcpClient.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#include <sys/socket.h>

#include "ndsl/net/SocketAddress.h"
#include "ndsl/net/TcpClient.h"
#include "ndsl/net/TcpChannel.h"
#include "ndsl/config.h"
#include "ndsl/utils/Error.h"
#include "ndsl/utils/Log.h"

namespace ndsl {
namespace net {

TcpClient::TcpClient() {}
TcpClient::~TcpClient() {}

TcpConnection *TcpClient::onConnect(EventLoop *loop)
{
    sockfd_ = socket(AF_INET, SOCK_STREAM, 0);

    struct SocketAddress4 servaddr;
    servaddr.setPort(SERV_PORT);

    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    int n;
    if ((n = connect(sockfd_, (SA *) &servaddr, sizeof(servaddr))) < 0) {
        // connect出错 返回
        // LOG(LOG_INFO_LEVEL, LOG_SOURCE_TCPCLIENT, "connect fail\n");
        return NULL;
    }

    // 创建一个TcpConnection
    TcpConnection *conn = new TcpConnection();
    if (NULL == conn) {
        // LOG(LOG_INFO_LEVEL, LOG_SOURCE_TCPCLIENT, "new TcpConnection
        // fail\n");
        return NULL;
    }

    conn->pTcpChannel_ = new TcpChannel(sockfd_, loop);
    if (NULL == conn->pTcpChannel_) {
        // LOG(LOG_INFO_LEVEL, LOG_SOURCE_TCPCLIENT, "new TcpChannel fail\n");
        return NULL;
    }
    conn->pTcpChannel_->setCallBack(TcpConnection::handleRead, NULL, conn);
    n = conn->pTcpChannel_->enrollIn(true);
    if (n < 0) {
        // LOG(LOG_INFO_LEVEL, LOG_SOURCE_TCPCLIENT, "enrollIn fail\n");
        return NULL;
    }

    return conn;
}

int TcpClient::disConnect()
{
    close(sockfd_);
    return S_OK;
}

} // namespace net
} // namespace ndsl
