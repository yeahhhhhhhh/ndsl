////
// @file Plugin.h
// @brief
// plugin头文件
//
// @author zhangsiqi
// @email 1575033031@qq.com
//
#ifndef __NDSL_UTILS_PLUGIN_H__
#define __NDSL_UTILS_PLUGIN_H__

#include <stdio.h>
#include "ndsl/utils/Guid.h"

namespace ndsl {
namespace utils {


struct Plugin
{
    using functype = int (*)(int);
    int doit(functype func,int para);
    int tag;
};

ndsl::utils::Plugin CreatPlugin();




} // namespace utils
} // namespace ndsl

#endif // __NDSL_UTILS_PLUGIN_H__