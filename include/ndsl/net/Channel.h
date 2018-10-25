/*
 * File: Channel.h
 * brief:
 *
 * Author: gyz
 * Email: mni_gyz@163.com
 * Last Modified: Saturday, 20th October 2018 3:46:24 pm
 * -----
 * Copyright 2018 - 2018
 */

#ifndef __CHANNEL_H__
#define __CHANNEL_H__

class Channel
{
    virtual int onRead() = 0;
    virtual int onWrite() = 0;
};

#endif // __CHANNEL_H__