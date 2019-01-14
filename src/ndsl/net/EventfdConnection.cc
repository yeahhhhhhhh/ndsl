/*
 * @file: 
 * @description: file content
 * @Date: 2019-01-12 22:22:04
 * @author: peng jun
 * @email: 785733871@qq.com
 */

#include <sys/eventfd.h>
#include <errno.h>

#include "ndsl/net/EventfdConnection.h"
#include "ndsl/net/EventfdChannel.h"
#include "ndsl/net/EventLoop.h"

namespace ndsl{
namespace net{

    // using ChannelCallBack = int (*)(void *);

    EventfdConnection::EventfdConnection(){}
    EventfdConnection::~EventfdConnection(){}

    int EventfdConnection::createEventfd(int &ev_fd){
        ev_fd = eventfd(0,EFD_NONBLOCK);//非阻塞
        if(ev_fd != -1)
            return 1;//S_OK
        else
            return 0;//S_FALSE
    }

    int EventfdConnection::createChannel(int fd,EventLoop *pLoop){
        // int fd_t = fd;
        //创建一个eventfd，创建一个channel，设置channel的loop/fd/回调函数
        if(createEventfd(fd) == 1){
            pEventfdChannel_ = new EventfdChannel(fd,pLoop);
            pEventfdChannel_ -> setCallBack(handleRead,handleWrite,this);
            pEventfdChannel_ -> enroll(true);

            return 1;//S_OK
        }
        return 0;//S_FALSE
    }

    int EventfdConnection::onWrite(uint64_t &count,int flags,Callback cb,void *param){
        int eventfd = pEventfdChannel_ -> getFd();

        int ret = write(eventfd,&count,sizeof(count));
        if(ret == sizeof(count)){
            return 1;                       
        }else if(ret < 0){
            // printf("error occur...\n");
            errorHandle_(errno,pEventfdChannel_ -> getFd());
            return 0;//S_FALSE
        }else {
            pInfo tsi = new Info;
            // tsi->offset_ = 0;
            tsi->sendBuf_ = count;
            // tsi->readBuf_ = NULL;
            // tsi->len_ = sizeof(count);
            // tsi->flags_ = flags | MSG_NOSIGNAL;
            tsi->cb_ = cb;
            tsi->param_ = param;
            qSendInfo_.push(tsi);
            return 1;//S_OK
        }
        return 0;//S_FALSE
    }

    int EventfdConnection::handleWrite(void *pthis){
        EventfdConnection *pThis = static_cast<EventfdConnection *>(pthis);

        int ev_fd = pThis->pEventfdChannel_->getFd();

        if(ev_fd < 0)return -1;

        if(pThis->qSendInfo_.size() > 0){
            pInfo tsi = pThis -> qSendInfo_.front();
            int len = sizeof(tsi->sendBuf_);
            int ret = write(ev_fd,&(tsi->sendBuf_),len);
            if(ret == len){
                pThis-> qSendInfo_.pop();
                delete tsi;
                return 1;
            }else if(ret < 0){
                // printf("error occur...\n");
                pThis->errorHandle_(errno,pThis->pEventfdChannel_ -> getFd());
                return 0;//S_FALSE
            }else if(ret == 0){
                return 1;//OK
            }
        }
        return 1;//OK
    }

    int EventfdConnection::onRead(uint64_t &count,int flags,Callback cb,void *param){
        int eventfd = pEventfdChannel_ -> getFd();

        int ret = read(eventfd,&count,sizeof(count));
        if(ret == sizeof(count)){
            //close fd
            return 1;
        }else {
            if(errno == EAGAIN || errno == EWOULDBLOCK){
                //加入回调，等待再读
                RecvInfo_.sendBuf_ = 0;
                RecvInfo_.cb_ = cb;
                RecvInfo_.param_ = param;

                return 1;//S_OK
            }
            return 0;//false
        }  
    }

    int EventfdConnection::handleRead(void *pthis){
        EventfdConnection *pThis = static_cast<EventfdConnection *>(pthis);

        int ev_fd = pThis->pEventfdChannel_->getFd();

        if(ev_fd < 0)return -1;


        // pInfo tsi = pThis -> RecvInfo_;
        int len = sizeof(pThis-> RecvInfo_.readBuf_);
        int ret = read(ev_fd,&(pThis-> RecvInfo_.readBuf_),len);
        if(ret == len){
            
            // delete tsi;
            return 1;
        }else if(ret < 0){
            // printf("error occur...\n");
            pThis->errorHandle_(errno,pThis->pEventfdChannel_ -> getFd());
            return 0;//S_FALSE
        }else if(ret == 0){
            return 1;//OK
        }

        return 1;//OK
    }
}
}