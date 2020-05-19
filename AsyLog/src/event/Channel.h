#ifndef _CHANNEL_H_
#define _CHANNEL_H_
#include <functional>
#include <cstdint>

class EventLoop;

const int8_t EV_READ = 0x01;
const int8_t EV_WRITE = 0x02;
const int8_t EV_TIMEOUT = 0x04;
const int8_t EV_SIGNAL = 0x08;

class Channel
{
public:
    Channel(EventLoop* loop, int fd, int events);
    //typedef void (*Loop_CallBack)(int fd);
    typedef std::function<void (int fd)> Loop_CallBack;
    void setCallWrite(Loop_CallBack WriteFunc){ WriteCallBack = WriteFunc; }
    void setCallRead(Loop_CallBack ReadFunc){ ReadCallBack = ReadFunc; }

    void registReadEvent(){ events_ |= EV_READ; update();}
    void registWriteEvent(){ events_ |= EV_WRITE; update();}
    void disRegistReadEvent(){ events_ &= ~EV_READ; update();}
    void disRegistWriteEvent(){ events_ &= ~EV_WRITE; update();}

    void handleEvent();

    int fd() const { return fd_; }
    int events() const{ return events_; }
    void setRevent(int revent) { revents_ |= revent; }

    //设置当前事件状态,在分发器中修改
    void setNew() { code_ = kNew; }
    void setDelete() { code_ = kDelete; }
    void setAdd() { code_ = kAdd; }
    //获取当前事件状态
    bool IsNew() const { return kNew == code(); }
    bool IsDelete() const { return kDelete == code(); }
    bool IsAdd() const { return kAdd == code(); }
private:
    enum Code
    {
        kNew = 0,
        kDelete = 1,
        kAdd = 2
    };

    Code code() const { return code_; }
    void update();

    EventLoop* loop_;
    int fd_;
    int events_;
    Code code_;
    int revents_;

    Loop_CallBack ReadCallBack;
    Loop_CallBack WriteCallBack;
};

#endif
