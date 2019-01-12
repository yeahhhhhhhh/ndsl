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
namespace ndsl{
namespace net{

class Entity
{
  private:
    int id_;
    Multiplexer *multiplexer_;
    Multiplexer::Callback cb_;
    
  public:
    Entity(int id,
    Callback cb,
    Multiplexer *Multiplexer)
    : id_(id), cb_(cb), multiplexer_(Multiplexer)
}

} // namespace net
} // namespace ndsl 
#endif // __NDSL_NET_ENTITY_H__