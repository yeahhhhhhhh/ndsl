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
#include "../incluce/ndsl/net/TcpConnection.h"

TcpConnection::TcpConnection(int sockfd, EventLoop *pLoop)
{
    createChannel(sockfd, pLoop);
}
TcpConnection::~TcpConnection() {}

int TcpConnection::createChannel(int sockfd, EventLoop *pLoop)
{
    pTcpChannel_ = new TcpChannel(sockfd, pLoop);
    pTcpChannel_->enableReading();
}

int TcpConnection::read()
{
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
int TcpConnection::write() { append(); }