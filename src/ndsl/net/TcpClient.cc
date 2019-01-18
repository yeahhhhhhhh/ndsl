/**
 * @file TcpClient.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#include <sys/socket.h>
#include <fcntl.h>

#include "ndsl/net/SocketAddress.h"
#include "ndsl/net/TcpClient.h"
#include "ndsl/net/TcpChannel.h"
#include "ndsl/config.h"
#include "ndsl/utils/Error.h"
#include "ndsl/utils/Log.h"

#include <cstdio>

namespace ndsl {
namespace net {

TcpClient::TcpClient() {}
TcpClient::~TcpClient() {}

TcpConnection *TcpClient::onConnect(
    EventLoop *loop,
    bool isConnNoBlock,
    struct SocketAddress4 *servaddr)
{
    sockfd_ = socket(AF_INET, SOCK_STREAM, 0);

    // struct SocketAddress4 servaddr;
    // servaddr.setPort(SERV_PORT);

    // inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    // 设成非阻塞
    if (isConnNoBlock) fcntl(sockfd_, F_SETFL, O_NONBLOCK);

    int n;
    if ((n = connect(sockfd_, (SA *) servaddr, sizeof(struct SocketAddress4))) <
        0) {
        if (errno != EINPROGRESS) {
            // connect出错 返回
            LOG(LOG_ERROR_LEVEL, LOG_SOURCE_TCPCLIENT, "connect fail");
            return NULL;
        }
    }
    // 设成非阻塞
    if (!isConnNoBlock) fcntl(sockfd_, F_SETFL, O_NONBLOCK);

    // 创建一个TcpConnection
    TcpConnection *conn = new TcpConnection();
    if (NULL == conn) {
        LOG(LOG_ERROR_LEVEL, LOG_SOURCE_TCPCLIENT, "new TcpConnection fail");
        return NULL;
    }

    if ((n = conn->createChannel(sockfd_, loop)) < 0) {
        LOG(LOG_ERROR_LEVEL, LOG_SOURCE_TCPCLIENT, "createChannel fail");
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
