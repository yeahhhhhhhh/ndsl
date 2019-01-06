/**
 * @file TcpClient.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#include <arpa/inet.h>
#include "ndsl/net/SocketAddress.h"
#include "ndsl/net/TcpClient.h"
#include "ndsl/utils/temp_define.h"

namespace ndsl {
namespace net {

int TcpClient::onConnect()
{
    sockfd_ = socket(AF_INET, SOCK_STREAM, 0);

    struct SocketAddress4 servaddr;
    servaddr.setPort(SERV_PORT);

    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
    connect(sockfd_, (SA *) &servaddr, sizeof(servaddr));

    return S_OK;
}

} // namespace net
} // namespace ndsl
