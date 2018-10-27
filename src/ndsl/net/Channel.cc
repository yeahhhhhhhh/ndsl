#include "ndsl/net/Channel.h"

namespace ndsl {
namespace net {

int Channel::setRevents(int revents) { revents_ = revents; }

} // namespace net
} // namespace ndsl
