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
#include "ndsl/net/TcpConnection.h"
namespace ndsl {
namespace net {
class Httphandler
{
  private:
    const constexpr static char *HttpHead = "http://";
    static void handleErro(int, Channel *)
    {
        LOG(LOG_ERROR_LEVEL, LOG_SOURCE_ENTITY, "ERROR!!!\n");
    }
    struct hpara
    {
        char *clientbuf = NULL;
        char *serverbuf = NULL;
        ssize_t readlen;
        char hostip[INET_ADDRSTRLEN];
        TcpConnection *conn2c = NULL;
        TcpConnection *conn2s = NULL;
    };

  public:
    static void beginProxy(void *para);
    static void disposeClientMsg(void *para);
    static void disposeServerMsg(void *para);
    static void connectGoalserver(void *para);
};
} // namespace net
} // namespace ndsl
#endif // __HTTPHANDLER_H__