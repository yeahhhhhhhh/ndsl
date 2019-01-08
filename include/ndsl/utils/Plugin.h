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


#if defined(__cplusplus)
extern "C" {
#endif

struct Plugin
{
    using functype = int (*)(int);
    int doit(functype func, int para);
    int tag;
};

Plugin *CreatPlugin(int tag);

#if defined(__cplusplus)
}
#endif

#endif // __NDSL_UTILS_PLUGIN_H__