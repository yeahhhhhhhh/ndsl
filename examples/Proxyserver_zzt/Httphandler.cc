/**
 * @file Httphandler.cc
 * @brief
 * 处理HTTP报文
 * @author zzt
 * @emial 429834658@qq.com
 **/
#include <netdb.h>
#include <stdio.h>
#include <string.h>
#include "malloc.h"
#include <arpa/inet.h>
#include "Httphandler.h"
#include "ndsl/net/TcpConnection.h"
#include "ndsl/net/TcpChannel.h"
#include "ndsl/net/TcpClient.h"
namespace ndsl {
namespace net {

// 开始代理，作为onaccept函数的回调
void Httphandler::beginProxy(void *para)
{
    TcpConnection *conn2c = (TcpConnection *) para;
    char *recvbuf = (char *) malloc(sizeof(char) * MAXLINE); // TODO: 内存释放
    struct hpara *p = new struct hpara(); // TODO: 内存释放
    p->databuf = recvbuf;
    p->readlen = 0;
    p->conn2c = conn2c;
    printf("before onRecv\n");
    conn2c->onRecv(
        recvbuf,
        &(p->readlen),
        0,
        disposeClientMsg,
        reinterpret_cast<void *>(p));
    conn2c->onError(handleErro);
}

// 解析从客户端发来的http报文
void Httphandler::disposeClientMsg(void *para)
{
    struct hpara *pa = reinterpret_cast<struct hpara *>(para);
    LOG(LOG_INFO_LEVEL, LOG_SOURCE_ENTITY, "\nClientMsg = \n%s\n", pa->databuf);
    LOG(LOG_INFO_LEVEL, LOG_SOURCE_ENTITY, "rlen = %lu\n", pa->readlen);
    char *FirstLocation = strstr(pa->databuf, HttpHead) + strlen(HttpHead);

    char *LastLocation = strstr(FirstLocation, "/");

    //得到目标服务器的名称
    char Servername[50];
    memset(Servername, 0, 50);
    memcpy(Servername, FirstLocation, LastLocation - FirstLocation);
    LOG(LOG_INFO_LEVEL, LOG_SOURCE_ENTITY, "Servername = %s\n", Servername);

    // DNS域名转换
    struct hostent *hp = gethostbyname(Servername);
    if (hp == NULL)
        LOG(LOG_ERROR_LEVEL,
            LOG_SOURCE_ENTITY,
            "gethostname error for host%s\n",
            Servername);
    LOG(LOG_INFO_LEVEL, LOG_SOURCE_ENTITY, "\tofficial: %s", hp->h_name);
    // 输出IP地址
    switch (hp->h_addrtype) {
    case AF_INET: {
        char **iptr = hp->h_addr_list;
        for (; *iptr != NULL; iptr++) {
            LOG(LOG_INFO_LEVEL,
                LOG_SOURCE_ENTITY,
                "\taddress:%s\n",
                inet_ntop(AF_INET, hp->h_addr, pa->hostip, sizeof(pa->hostip)));
        }
        break;
    }
    default:
        LOG(LOG_ERROR_LEVEL, LOG_SOURCE_ENTITY, "unknown addrtype\n");
        break;
    }
    connectGoalserver(reinterpret_cast<void *>(pa));
}

// 连接目标服务器
void Httphandler::connectGoalserver(void *para)
{
    struct hpara *pa = reinterpret_cast<struct hpara *>(para);

    struct SocketAddress4 clientservaddr(pa->hostip, 80);
    TcpConnection *Conn2s;
    TcpClient *pCli = new TcpClient();

    Conn2s = pCli->onConnect(
        pa->conn2c->pTcpChannel_->pLoop_, false, &clientservaddr);
    if (Conn2s != NULL) {
        LOG(LOG_INFO_LEVEL,
            LOG_SOURCE_ENTITY,
            "success connect to Goalserver\n");
        pa->conn2s = Conn2s;
    } else {
        LOG(LOG_ERROR_LEVEL, LOG_SOURCE_ENTITY, "cant connect to Goalserver\n");
    }

    Conn2s->onSend(pa->databuf, pa->readlen, 0, NULL, NULL);
    Conn2s->onRecv(
        pa->databuf,
        &(pa->readlen),
        0,
        disposeServerMsg,
        reinterpret_cast<void *>(pa));
}

// 解析从服务器端发来的http报文
void Httphandler::disposeServerMsg(void *para)
{
    struct hpara *pa = reinterpret_cast<struct hpara *>(para);
    LOG(LOG_INFO_LEVEL, LOG_SOURCE_ENTITY, "\nServerMsg = \n%s\n", pa->databuf);
    pa->conn2c->onSend(pa->databuf, pa->readlen, 0, NULL, NULL);
}

} // namespace net
} // namespace ndsl
