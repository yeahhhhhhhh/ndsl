////
// @brief 
// unixchanne's shixian
//
// @author ranxaingjun
// @email ranxianshen@gmail.com
//
#include "UnixChannel.h"
#include "UnixConnection.h"

namespace ndsl {
namespace net {

UnixChannel::UnixChannel(int sockfd, EventLoop *loop)
    : BaseChannel(sockfd, loop)
{}

UnixChannel::~UnixChannel()
{
    // 将自身从eventloop上面删掉
    erase();
}

} // namespace net
} // namespace ndsl
