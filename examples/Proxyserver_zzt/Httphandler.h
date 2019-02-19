/**
 * @file Httphandler.h
 * @brief
 *
 * @author zzt
 * @emial 429834658@qq.com
 **/
#ifndef __HTTPHANDLER_H__
#define __HTTPHANDLER_H__

#include "ndsl/utils/Log.h"
#include "ndsl/net/SocketAddress.h"
#include "ndsl/net/EventLoop.h"
#include "ndsl/net/Multiplexer.h"
#include "ndsl/net/TcpConnection.h"

namespace ndsl {
namespace net {

using entityMap = std::map<int, TcpConnection *>;

class Httphandler
{
  private:
    const constexpr static char *HttpHead = "http://";
    static void handleErro(int, Channel *)
    {
        LOG(LOG_ERROR_LEVEL, LOG_SOURCE_ENTITY, "ERROR!!!\n");
    }

  public:
    static void beginProxy(void *para);
    static void disposeClientMsg(void *para);
    static void
    disposeServerMsg(Multiplexer *Multiplexer, char *data, int len, int error);
    static entityMap *getMap();
    // static void connectGoalserver(void *para);
};
} // namespace net
} // namespace ndsl
#endif // __HTTPHANDLER_H__