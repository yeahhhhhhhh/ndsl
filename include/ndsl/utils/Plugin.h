////
// @file Log.h
// @brief
// plugin头文件
//
// @author zhangsiqi
// @email 1575033031@qq.com
//
#ifndef __NDSL_UTILS_PLUGIN_H__
#define __NDSL_UTILS_PLUGIN_H__

#include <stdio.h>
namespace ndsl {
namespace utils {
  
struct Plugin
{
    using functype = int (*)(int);
    int doit(functype func,int para);
    
};

} // namespace utils
} // namespace ndsl

#endif // __NDSL_UTILS_PLUGIN_H__