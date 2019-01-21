/**
 * @file Entity.h
 * @brief
 * Entity实体类
 *
 * @author zzt
 * @emial 429834658@qq.com
 **/
#ifndef __NDSL_NET_ENTITY_H__
#define __NDSL_NET_ENTITY_H__

#include "ndsl/net/Multiplexer.h"

namespace ndsl {
namespace net {
class Multiplexer;

class Entity
{
  private:
    using entitycallback =
        void (*)(Multiplexer *Multiplexer, char *buffer, int len, int error);
    int id_;
    entitycallback cb_;

  public:
    Multiplexer *multiplexer_;
    Entity(int id, entitycallback cb, Multiplexer *Multiplexer)
        : id_(id)
        , cb_(cb)
        , multiplexer_(Multiplexer)
    {
        multiplexer_->addInsertWork(id_, cb_);
    }
    // pri函数为测试用
    void pri() { printf("use entity\n"); }
};

} // namespace net
} // namespace ndsl
#endif // __NDSL_NET_ENTITY_H__