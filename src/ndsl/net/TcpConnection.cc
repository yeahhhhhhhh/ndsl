/*
 * File: TcpConnection.cc
 * brief:
 *
 * Author: gyz
 * Email: mni_gyz@163.com
 * Last Modified: Thursday, 29th November 2018 2:23:14 pm
 */

#include "ndsl/net/TcpConnection.h"
#include "ndsl/utils/temp_define.h"
#include <cstring>
#include <unistd.h>

#include <iostream>
using namespace std;

namespace ndsl {
namespace net {

TcpConnection::TcpConnection(int sockfd, EventLoop *pLoop)
{
    createChannel(sockfd, pLoop);
}
TcpConnection::~TcpConnection() {}

int TcpConnection::createChannel(int sockfd, EventLoop *pLoop)
{
    pTcpChannel_ = new TcpChannel(sockfd, pLoop);
    pTcpChannel_->enableReading();
    pTcpChannel_->setCallBack(this);

    cout << "TcpConnection::createChannel" << endl;

    return S_OK;
}

int TcpConnection::handleRead()
{
    cout << "TcpConnection::handleRead" << endl;

    memset(inBuf_, 0, sizeof(inBuf_));
    int sockfd = pTcpChannel_->getFd();

    cout << "fd = " << sockfd << endl;

    if (sockfd < 0) { return -1; }
    int length;
    char line[MAXLINE];
    memset(line, 0, sizeof(line));
    if ((length = read(sockfd, line, MAXLINE)) < 0) {
        if (errno == ECONNRESET) {
            // cout << "ECONNREST closed socket fd:" << sockfd << endl;
            close(sockfd);
        }
    } else if (length == 0) {
        // cout << "read 0 closed socket fd:" << sockfd << endl;
        close(sockfd);
    } else {
        cout << "length = " << length << endl;
        cout << "receive buf = end" << line << endl;

        strcat(inBuf_, line);

        pTcpChannel_->onRead(inBuf_);
    }
    return S_OK;
}

int TcpConnection::handleWrite()
{
    int sockfd = pTcpChannel_->getFd();
    if (sockfd < 0) { return -1; }
    int n, length;
    char temp[MAXLINE];
    memset(temp, 0, sizeof(temp));
    length = strlen(outBuf_);
    if (pTcpChannel_->isWriting()) {
        n = write(sockfd, outBuf_, strlen(outBuf_));
        if (n == length) {
            // log(write n bytes);
            pTcpChannel_->disableWriting();
            pTcpChannel_->onWrite();
        } else {
            // 这一次还没传完
            strncpy(temp, outBuf_ + n, length - n);
            memset(outBuf_, 0, sizeof(outBuf_));
            strcpy(outBuf_, temp);
        }
    }
    return S_OK;
}

int TcpConnection::send(char *outBuf)
{
    int sockfd = pTcpChannel_->getFd();
    if (sockfd < 0) { return -1; }
    int length = strlen(outBuf);
    int n = 0;
    if ((n = write(sockfd, outBuf, strlen(outBuf))) < 0) {
        // log(write error);
        pTcpChannel_->onWrite();
    } else if (n < length) {
        // 一次write没写完
        if (!pTcpChannel_->isWriting()) pTcpChannel_->enableWriting();
        strcat(outBuf_, outBuf + n);
        // memset(outBuf, 0, sizeof(outBuf));
    }
    return S_OK;
}

} // namespace net
} // namespace ndsl
