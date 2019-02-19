/**
 * @file Httphandler.h
 * @brief
 *
 * @author zzt
 * @emial 429834658@qq.com
 **/
#ifndef __VAR_H__
#define __VAR_H__
namespace ndsl {
namespace net {
struct con
{
    TcpConnection *con2c;
    Multiplexer *multi2s;
};
struct hpara
{
    char *clientbuf = NULL;
    char *serverbuf = NULL;
    struct con *conn;
    ssize_t readlen;
    // char hostip[INET_ADDRSTRLEN];
    std::map<int, TcpConnection *> *map = NULL;
    TcpAcceptor *tAc;
};

} // namespace net
} // namespace ndsl
#endif // __VAR_H__