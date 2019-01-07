////
// @file Log.cc
// @brief
// 实现日志
//
// @author zhangsiqi
// @email 1575033031@qq.com
//
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <syslog.h>
#include <stdarg.h>
#include <ndsl/utils/Log.h>
#include <ndsl/utils/TimeStamp.h>

int tag[64] = {0};
int m_file;

void init()
{
    char path[256];
    ndsl::utils::TimeStamp ts;
    ts.now();
    ts.to_string(path, 256);
    int len = ::strlen(path);
    sprintf(path + len, ".log");

    m_file = ::open(
        path,                        // 路径
        O_RDWR | O_APPEND | O_CREAT, // 追加数据
        0666);                       // 其它进程可读
    if (m_file == -1) printf("unable to open %s, error = %d\n", path, errno);
}

void set_ndsl_log_sinks(int sinks)
{
    if (sinks > 64 || sinks < 0) return;

    tag[sinks] = 1;
}
void ndsl_log_into_sink(int level, int source, const char *format, ...)
{
    char buffer[4096];
    set_ndsl_log_sinks(source);
    init();
    ndsl::utils::TimeStamp ts;
    ts.now();
    buffer[0] = '[';
    ts.to_string(buffer + 1, 4096);
    int ret1 = ::strlen(buffer);
    buffer[ret1] = ']';

    int ret2 = sprintf(
        buffer + ret1 + 1,
        " lv=%d pid=%d tid=%lx ",
        level,
        ::getpid(),
        (long) ::pthread_self()); // 毫秒

    // 复制数据
    va_list ap;
    va_start(ap, format);
    int ret3 =
        vsnprintf(buffer + ret1 + ret2 + 1, 512 - ret1 - ret2 - 1, format, ap);
    if (ret3 < 0) return;

    switch (source) {
    case 0:
        ::write(m_file, buffer, ret1 + ret2 + ret3 + 1);
        break;
    case 1:
        ::write(m_file, buffer, ret1 + ret2 + ret3 + 1);
        break;
    case 2:
        ::write(m_file, buffer, ret1 + ret2 + ret3 + 1);
        break;
    case 3:
        ::write(m_file, buffer, ret1 + ret2 + ret3 + 1);
        break;
    case 4:
        ::write(m_file, buffer, ret1 + ret2 + ret3 + 1);
        break;
    case 5:
        ::write(m_file, buffer, ret1 + ret2 + ret3 + 1);
        break;
    default:
        break;
    }

    va_end(ap);
    close(m_file);
}