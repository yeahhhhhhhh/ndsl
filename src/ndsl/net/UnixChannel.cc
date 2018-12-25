////
// @brief 
// unixchanne's shixian
//
// @author ranxaingjun
// @email ranxianshen@gmail.com
//
#include "../../../include/ndsl/net/UnixChannel.h"
#include "../../../include/ndsl/net/UnixConnection.h"

namespace ndsl {
namespace net {

UnixChannel::UnixChannel(int sockfd, EventLoop *loop)
    : BaseChannel(sockfd, loop)
{}

UnixChannel::~UnixChannel()
{
    // 将自身从eventloop上面删掉
    del();
}

UnixConnection *UnixChannel::newConnection(int connfd)
{
    UnixConnection *pCon = new UnixConnection();
    pCon->createChannel(connfd, getEventLoop());
    return pCon;
}

} // namespace net
} // namespace ndsl
