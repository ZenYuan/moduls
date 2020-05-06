#ifndef __LOGGER_H
#define __LOGGER_H
#include <time.h>

class Buffer
{
public:
    Buffer():cur_(data_){}
    void append(const char* buf, size_t len)   //size_t内置数组长度类型
    {
        if ( len < avail() )
        {
            memcpy(cur_, buf, len);
            cur_ += len;
        }
    }
    int avail() const { return end() - cur_; }
    char* current() { return cur_; }
    void add(int len) { cur_ += len; }
    const char* data() const { return data_; }
    int length() const {return static_cast<int>(cur_ - data_);}
private:
    const char* end() const { return data_ + sizeof(data_); }
    char data_[4000];   //4MB会报错
    char* cur_;
};


class Logger
{
public:
    enum LogLevel
    {
        TRACE,
        DEBUG,
        INFO,
        WARN,
        ERROR,
        FATAL,
        NUM_LOG_LEVELS,
    };

    Logger();
    Logger(const char* fileName, int line, LogLevel level);
    Logger(const char* fileName, int line, const char* func, LogLevel level);
    ~Logger();

    //const Buffer& buffer() const { return buffer_; }
    //将输出的内容写进buffer，建立buffer是为了实现同步异步日志
    void stream(const char* fmt...);

    typedef void (*OutputFunc)(const char* msg, int len);
    void SetOutPut(OutputFunc);

private:
    class Impl
    {
    public:
        Impl(Logger::LogLevel level, const char* fileName, int line, const char* func);
        void formatTime();
        Logger::LogLevel level_;
        int line_;
        const char* func_;
        const char* basename_;  //const如果是底层含义需要在初始化列表中赋值
        char time_[65];
    };

//复合,先调用内部的构造函数，再调用外部的构造函数
    Buffer buffer_; //调用默认构造函数
    Impl impl_;
};

#define LOG_TRACE(...) Logger(__FILE__, __LINE__, __func__, Logger::TRACE).stream(__VA_ARGS__)
#define LOG_DEBUG(...) Logger(__FILE__, __LINE__, __func__, Logger::DEBUG).stream(__VA_ARGS__)
#define LOG_INFO(...) Logger(__FILE__, __LINE__, __func__, Logger::INFO).stream(__VA_ARGS__)
#define LOG_WARN(...) Logger(__FILE__, __LINE__, __func__, Logger::WARN).stream(__VA_ARGS__)
#define LOG_ERROR(...) Logger(__FILE__, __LINE__, __func__, Logger::ERROR).stream(__VA_ARGS__)

#endif
