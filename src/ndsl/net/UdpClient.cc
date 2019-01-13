////
// @file  UdpClient.cc
// @brief
//
//
// @author lanry
// @email luckylanry@163.com
//
#include <arpa/inet.h>
#include "ndsl/net/SocketAddress.h"
#include "ndsl/net/UdpClient.h"
#include "ndsl/utils/temp_define.h"
#include "ndsl/utils/Error.h"

namespace ndsl {
namespace net {

int UdpClient::start()
{
    sockfd_ = socket(AF_INET, SOCK_STREAM, 0);

    struct SocketAddress4 servaddr;
    servaddr.setPort(SERV_PORT);

    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);

    return S_OK;
}

} // namespace net
} // namespace ndsl
