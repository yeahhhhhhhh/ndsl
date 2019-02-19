/**
 * @file Httphandler.cc
 * @brief
 * 处理HTTP报文
 * @author zzt
 * @emial 429834658@qq.com
 **/
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "malloc.h"
#include <arpa/inet.h>
#include "Httphandler.h"
#include "ndsl/net/Multiplexer.h"
#include "ndsl/net/Entity.h"
#include "ndsl/net/TcpConnection.h"
#include "ndsl/net/TcpChannel.h"
#include "ndsl/net/TcpClient.h"
#include "Protbload.pb.h"
#include "./var.h"

namespace ndsl {
namespace net {
using namespace Protbload;
// 开始代理，作为onAccept函数的回调
void Httphandler::beginProxy(void *para)
{
    struct hpara *p = (struct hpara *) para;
    char *recvbuf =
        (char *) malloc(sizeof(char) * MAXLINE); // 在disposeClientMsg函数中释放

    p->clientbuf = recvbuf;
    p->readlen = 0;
    p->conn->con2c->onRecv(
        recvbuf, &(p->readlen), 0, disposeClientMsg, (void *) p);
    p->conn->con2c->onError(handleErro);

    struct sockaddr_in rservaddr;
    bzero(&rservaddr, sizeof(rservaddr));
    socklen_t addrlen;
    TcpConnection *conn2c = new TcpConnection(); // TODO: 内存释放
    printf("con2c = %p\n", conn2c);
    struct hpara *hp = new struct hpara(); // TODO:内存释放
    hp->map = Httphandler::getMap();
    hp->conn = conPtr;
    hp->tAc = p->tAc;
    hp->tAc->onAccept(
        conn2c,
        (SA *) &rservaddr,
        &addrlen,
        Httphandler::beginProxy,
        (void *) hp);
}

// 解析从客户端发来的http报文
void Httphandler::disposeClientMsg(void *para)
{
    struct hpara *hp = reinterpret_cast<struct hpara *>(para);
    LOG(LOG_INFO_LEVEL, LOG_SOURCE_ENTITY, "\nClientMsg = \n%s", hp->clientbuf);
    LOG(LOG_INFO_LEVEL, LOG_SOURCE_ENTITY, "rlen = %lu\n", hp->readlen);

    // 得到第一个参数
    char *FirstLocation = strstr(hp->clientbuf, "num1=") + strlen("num1=");
    char *LastLocation = strstr(FirstLocation, "&");
    char num[4];
    memset(num, 0, 4);
    memcpy(num, FirstLocation, LastLocation - FirstLocation);
    int a = atoi(num);
    LOG(LOG_INFO_LEVEL, LOG_SOURCE_ENTITY, "num1 = %d\n", a);

    // 得到第二个参数
    FirstLocation = strstr(FirstLocation, "num2=") + strlen("num2=");
    LastLocation = strstr(LastLocation, " ");
    memset(num, 0, 4);
    memcpy(num, FirstLocation, LastLocation - FirstLocation);
    int b = atoi(num);
    LOG(LOG_INFO_LEVEL, LOG_SOURCE_ENTITY, "num2 = %d\n", b);

    if (hp->clientbuf != NULL) {
        delete hp->clientbuf;
        LOG(LOG_INFO_LEVEL, LOG_SOURCE_ENTITY, "delete clientbuf\n");
    }

    std::string pstr;
    Protbload::ADD *addmessage = new Protbload::ADD; // 在本函数最后释放
    addmessage->set_agv1(a);
    addmessage->set_agv2(b);
    addmessage->set_id(1);
    addmessage->SerializeToString(&pstr);
    int mlen = pstr.size();

    // extern Multiplexer *multi2s;    printf("before mendMag to server\n");
    printf("multi = %p\n", hp->conn->multi2s);
    if (hp->conn->multi2s != NULL) {
        // Entity *myent =
        //     new Entity(1, Httphandler::disposeServerMsg, pa->conn->multi2s);
        //     //TODO:这里有问题，对方消息都发回来了我的id还没有注册
        // myent->pri();
        struct para *mp = new struct para; // 在insert()中释放
        mp->id = 1;
        mp->cb = Httphandler::disposeServerMsg;
        mp->pthis = hp->conn->multi2s;
        Multiplexer::insert((void *) mp);

        std::map<int, TcpConnection *>::iterator iter =
            hp->map->lower_bound(mp->id);

        printf("hp->enMap = %p\n", hp->map);
        if (iter == hp->map->end() || iter->first != mp->id) {
            hp->map->insert(std::make_pair(mp->id, hp->conn->con2c));
        }
        LOG(LOG_INFO_LEVEL, LOG_SOURCE_ENTITY, "insert entityMap\n");

        hp->conn->multi2s->sendMessage(1, mlen, pstr.c_str());
        if (addmessage != NULL) {
            delete addmessage;
            LOG(LOG_INFO_LEVEL, LOG_SOURCE_ENTITY, "delete addmessage\n");
        }
    }
}

// 解析从服务器端发来的消息
void Httphandler::disposeServerMsg(
    Multiplexer *Multiplexer,
    char *data,
    int len,
    int error)
{
    TcpConnection *conec2c = NULL;
    Protbload::RESULT *resultmessage = new Protbload::RESULT;
    resultmessage->ParseFromString(data);
    printf("result==%d \n", resultmessage->answer());
    entityMap *map = Httphandler::getMap();
    printf("enMap = %p\n", map);
    std::map<int, TcpConnection *>::iterator iter =
        map->find(resultmessage->id());
    printf("id = %d\n", resultmessage->id());
    if (iter != map->end()) {
        conec2c = iter->second;
        printf("con2c = %p\n", iter->second);
    }
    std::string s = std::to_string(resultmessage->answer());
    printf("result==%d \n", resultmessage->answer());
    // conec2c->onSend((void *) (s.c_str()), s.size(), 0, NULL, NULL);
    std::string str = "HTTP/1.0 200 "
                      "OK\r\nConnection:close\r\nContent-type:text/"
                      "plain\r\n";
    s = "the result is=" + s;
    str += "Content-Length: " + std::to_string(s.size()) + "\r\n\r\n";
    str += s;

    printf("%s\n", str.c_str());
    conec2c->onSend((void *) (str.c_str()), str.size(), 0, NULL, NULL);
    // conec2c->onSend((void *) (s.c_str()), s.size(), 0, NULL, NULL);
}

entityMap *Httphandler::getMap()
{
    static entityMap *map = new entityMap;
    return map;
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
    char *FirstLocation = strstr(pa->clientbuf, HttpHead) +
strlen(HttpHead); char *LastLocation = strstr(FirstLocation, "/"); char
Servername[50]; memset(Servername, 0, 50); memcpy(Servername, FirstLocation,
LastLocation - FirstLocation); LOG(LOG_INFO_LEVEL, LOG_SOURCE_ENTITY,
"Servername = %s\n", Servername);

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
//         LOG(LOG_INFO_LEVEL, LOG_SOURCE_ENTITY, "malloc new
serverbuffer\n");
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
