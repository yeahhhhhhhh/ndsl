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

// 开始代理，作为onAccept函数的回调
void Httphandler::beginProxy(void *para)
{
    TcpConnection *conn2c = (TcpConnection *) para;
    char *recvbuf = (char *) malloc(sizeof(char) * MAXLINE); // TODO: 内存释放
    struct hpara *p = new struct hpara(); // TODO: 内存释放
    p->clientbuf = recvbuf;
    p->readlen = 0;
    p->conn2c = conn2c;
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
    LOG(LOG_INFO_LEVEL, LOG_SOURCE_ENTITY, "\nClientMsg = \n%s", pa->clientbuf);
    LOG(LOG_INFO_LEVEL, LOG_SOURCE_ENTITY, "rlen = %lu\n", pa->readlen);

    // 得到第一个参数
    char *FirstLocation = strstr(pa->clientbuf, "num1=") + strlen("num1=");
    char *LastLocation = strstr(FirstLocation, "&");
    char num[4];
    memset(num, 0, 4);
    memcpy(num, FirstLocation, LastLocation - FirstLocation);
    int a = atoi(num);
    LOG(LOG_INFO_LEVEL, LOG_SOURCE_ENTITY, "num1 = %d\n", a);

    // 得到第二个参数
    char *FirstLocation = strstr(FirstLocation, "num2=") + strlen("num2=");
    char *LastLocation = strstr(LastLocation ，" ");
    memset(num, 0, 4);
    memcpy(num, FirstLocation, LastLocation - FirstLocation);
    int b = atoi(num);
    LOG(LOG_INFO_LEVEL, LOG_SOURCE_ENTITY, "num2 = %d\n", b);

    Protbload::ADD *addmessage = new Protbload::ADD; // TODO: 内存释放
    addmessage->set_agv1(a);
    addmessage->set_agv2(b);
    addmessage->SerializeToString(&pstr);
    int mlen = pstr.size();

    multi2s->sendMessage(1, mlen, pstr.c_str());
}

// 解析从服务器端发来的http报文
void Httphandler::disposeServerMsg(
    Multiplexer *Multiplexer,
    char *data,
    int len,
    int ero)
{
    struct hpara *pa = reinterpret_cast<struct hpara *>(para);
    LOG(LOG_INFO_LEVEL,
        LOG_SOURCE_ENTITY,
        "\nServerMsg = \n%s\n",
        pa->serverbuf);
    LOG(LOG_INFO_LEVEL, LOG_SOURCE_ENTITY, "\nreadlen = \n%lu\n", pa->readlen);

    pa->conn2c->onSend(pa->serverbuf, pa->readlen, 0, NULL, NULL);
    LOG(LOG_INFO_LEVEL,
        LOG_SOURCE_ENTITY,
        "already send to client,wait for recv\n");

    pa->conn2c->onRecv(
        pa->clientbuf,
        &(pa->readlen),
        0,
        disposeClientMsg,
        reinterpret_cast<void *>(pa));
}

/********** FIXME: 现在建立了到服务器的长连接，不需要这样处理了

// 解析从客户端发来的http报文
void Httphandler::disposeClientMsg(void *para)
{
    struct hpara *pa = reinterpret_cast<struct hpara *>(para);
    LOG(LOG_INFO_LEVEL,
        LOG_SOURCE_ENTITY,
        "\nClientMsg = \n%s\n",
        pa->clientbuf);
    LOG(LOG_INFO_LEVEL, LOG_SOURCE_ENTITY, "rlen = %lu\n", pa->readlen);

    // 得到目标服务器的名称
    char *FirstLocation = strstr(pa->clientbuf, HttpHead) + strlen(HttpHead);
    char *LastLocation = strstr(FirstLocation, "/");
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

    // 将IP地址放入pa
    switch (hp->h_addrtype) {
    case AF_INET: {
        char **iptr = hp->h_addr_list;
        if (*iptr != NULL) {
            LOG(LOG_INFO_LEVEL,
                LOG_SOURCE_ENTITY,
                "\taddress:%s\n",
                inet_ntop(
                    AF_INET,
                    hp->h_addr_list[0],
                    pa->hostip,
                    sizeof(pa->hostip)));
            //将获取的IP地址转为点分十进制后存入pa->hostip
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
// void Httphandler::connectGoalserver(void *para)
// {
//     struct hpara *pa = reinterpret_cast<struct hpara *>(para);

//     struct SocketAddress4 clientservaddr(pa->hostip, 9999);
//     TcpConnection *Conn2s;
//     TcpClient *pCli = new TcpClient();

//     Conn2s = pCli->onConnect(
//         pa->conn2c->pTcpChannel_->pLoop_, false, &clientservaddr);
//     if (Conn2s != NULL) {
//         LOG(LOG_INFO_LEVEL,
//             LOG_SOURCE_ENTITY,
//             "success connect to Goalserver\n");
//         pa->conn2s = Conn2s;
//     } else {
//         LOG(LOG_ERROR_LEVEL, LOG_SOURCE_ENTITY, "cant connect to
Goalserver\n");
//     }

//     Conn2s->onSend(pa->clientbuf, pa->readlen, 0, NULL, NULL);

//     if (pa->serverbuf == NULL) {
//         char *buffer =
//             (char *) malloc(sizeof(char) * MAXLINE); // TODO: 内存释放
//         LOG(LOG_INFO_LEVEL, LOG_SOURCE_ENTITY, "malloc new serverbuffer\n");
//         pa->serverbuf = buffer;
//     }

//     Conn2s->onRecv(
//         pa->serverbuf,
//         &(pa->readlen),
//         0,
//         disposeServerMsg,
//         reinterpret_cast<void *>(pa));
// }
**********/

} // namespace net
} // namespace ndsl
