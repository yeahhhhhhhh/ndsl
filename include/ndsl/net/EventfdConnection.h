/*
 * @file: 
 * @description: file content
 * @Date: 2019-01-13 14:20:23
 * @author: peng jun
 * @email: 785733871@qq.com
 */

#include <queue>

#include "ndsl/net/EventLoop.h"
#include "ndsl/net/EventfdChannel.h"


using namespace ndsl;
using namespace net;

namespace ndsl{
namespace net{

class EventfdConnection{
    public:
        using Callback = int (*)(void *);
        using ErrorHandle = void (*)(int ,int);
        
    private:
        typedef struct SInfo{
            uint64_t sendBuf_;
            uint64_t readBuf_;//回调的时候保存读取的值
            // size_t *len_;//发送long int就没必要设置长度和偏移了
            int flags_;
            Callback cb_;
            void *param_;
            // size_t offset_;//一次没发送完时的偏移量
        }Info,*pInfo;

        std::queue<pInfo> qSendInfo_;//发送队列
        Info RecvInfo_;//代表接收的结构体

        ErrorHandle errorHandle_;//处理错误的回调函数
    public:
        EventfdConnection();
        ~EventfdConnection();

        EventfdChannel *pEventfdChannel_;//fd保存在channel中

        int createEventfd(int &ev_fd);

        int createChannel(int fd,EventLoop *pLoop);
        //flag去掉？
        int onWrite(uint64_t &count,int flags,Callback cb,void *param);
        static int handleWrite(void *pthis);
        int onRead(uint64_t &count,int flags,Callback cb,void *param);
        static int handleRead(void *pthis);
};

}
}