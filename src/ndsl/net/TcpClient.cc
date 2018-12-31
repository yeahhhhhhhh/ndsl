/**
 * @file TcpClient.cc
 * @brief
 *
 * @author gyz
 * @email mni_gyz@163.com
 */
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include "ndsl/net/TcpClient.h"
#include "ndsl/utils/temp_define.h"

namespace ndsl {
namespace net {

int TcpClient::onConnect()
{
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in servaddr;
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    inet_pton(AF_INET, "127.0.0.1", &servaddr.sin_addr);
    connect(sockfd, (SA *) &servaddr, sizeof(servaddr));

    return S_OK;
}

} // namespace net
} // namespace ndsl
