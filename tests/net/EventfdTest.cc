#include "../catch.hpp"

#include <ndsl/net/EventLoop.h>
#include <ndsl/net/EventfdConnection.h>

#include <sys/eventfd.h>
#include <errno.h>

using namespace ndsl;
using namespace net;

TEST_CASE("createChannel"){
    // 启动服务
    // 初始化EPOLL
    ndsl::net::EventLoop loop;

    // REQUIRE(loop.init() == S_OK);
    
    EventfdConnection *conn = new EventfdConnection();
    int efd;
    int ret = conn->createEventfd(efd);//创建eventfd
    REQUIRE(ret == S_OK);

    ret = conn->createChannel(efd,&loop);//创建channel
    REQUIRE(ret == S_OK);

    //写之前读，设置为非阻塞，会产生EAGAIN的错误
    uint64_t temp = 0;
    ret = read(conn->pEventfdChannel_->getFd(),&temp,sizeof(temp));
    REQUIRE(temp == 0);
    REQUIRE(ret == -1);
    REQUIRE(errno == EAGAIN);

    //写+写+读
    uint64_t count = 2;
    ret = conn->onWrite(count,0,EventfdConnection::handleWrite,NULL);
    conn->onWrite(count,0,EventfdConnection::handleWrite,NULL);
    REQUIRE(ret == S_OK);
    read(conn->pEventfdChannel_->getFd(),&temp,sizeof(temp));
    REQUIRE(temp == 4);



    //再读，会产生EAGAIN的错误
    uint64_t count2 = 1;
    ret = read(conn->pEventfdChannel_->getFd(),&count2,sizeof(count2));
    REQUIRE(ret == S_FALSE);
    REQUIRE(errno == EAGAIN);
    REQUIRE(count2 == 1);

    //写+读
    ret = conn->onWrite(count,0,EventfdConnection::handleWrite,NULL);
    REQUIRE(ret == S_OK);
    ret = conn->onRead(count2,0,EventfdConnection::handleRead,NULL);
    REQUIRE(ret == S_OK);
    REQUIRE(count2 == 2);



}