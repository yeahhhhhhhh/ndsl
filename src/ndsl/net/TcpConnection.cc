/*
 * File: TcpConnection.cc
 * brief:
 *
 * Author: gyz
 * Email: mni_gyz@163.com
 * Last Modified: Saturday, 20th October 2018 3:42:20 pm
 * -----
 * Copyright 2018 - 2018
 */
#include "ndsl/net/TcpConnection.h"

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
}

int TcpConnection::read()
{
    memset(inBuf_, 0, sizeof(inBuf_));
    int sockfd = pTcpChannel_->getFd();
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
        strcat(inBuf_, line);
        pTcpChannel_->onRead(this, &inBuf_);
    }
}

int TcpConnection::write()
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
            memsset(outBuf_, 0, sizeof(outBuf_));
            strcpy(outBuf_, temp);
        }
    }
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
        memset(outBuf, 0, sizeof(outBuf));
    }
}