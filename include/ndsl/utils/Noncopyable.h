/**
 * @file Noncopyable.h
 * @brief
 * 不可拷贝对象
 *
 * @author Liu GuangRui
 * @email 675040625@qq.com
 */
#ifndef __NDSL_UTILS_NONCOPYABLE_H__
#define __NDSL_UTILS_NONCOPYABLE_H__

namespace ndsl {
namespace utils {

class noncopyable
{
  protected:
    noncopyable();
    ~noncopyable();

  private:
    noncopyable(const noncopyable &);
    noncopyable &operator=(const noncopyable &);
};

} // namespace utils
} // namespace ndsl

#endif // __NDSL_UTILS_NONCOPYABLE_H__