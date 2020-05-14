#ifndef _CHANNEL_H_
#define _CHANNEL_H_
#include <functional>

class EventLoop;

class Channel
{
public:
    Channel(EventLoop* loop, int fd, int events){}
    //typedef void (*Loop_CallBack)(int fd);
    typedef std::function<void (int fd)> Loop_CallBack;
    void setCallWrite(Loop_CallBack WriteFunc){ WriteCallBack = WriteFunc; }
    void setCallRead(Loop_CallBack ReadFunc){ ReadCallBack = ReadFunc; }

    void registReadEvent(){ events_ |= POLLIN; update();}
    void registWriteEvent(){ events_ |= POLLOUT; update();}
    void disRegistReadEvent(){ events_ &= ~POLLIN; update();}
    void disRegistWriteEvent(){ events_ &= ~POLLOUT; update();}

    void handleEvent();

    void fd() const { return fd_; }
    void events() const{ return events_; }

    //设置当前事件状态,在分发器中修改
    void setNew() { code_ = kNew; }
    void setDelete() { code_ = kDelete; }
    void setAdd() { code_ = kAdd; }
    //获取当前事件状态
    bool IsNew const() { return kNew = code(); }
    bool IsDelete const() { return kDelete = code(); }
    bool IsAdd const() { return kAdd = code(); }
private:
    enum Code
    {
        kNew = 0;
        kDelete = 1;
        kAdd = 2;
    };

    Code code() const { return code_; }
    void update();

    EventLoop* loop_;
    int fd_;
    int events_;
    Code code_;

    Loop_CallBack ReadCallBack;
    Loop_CallBack WriteCallBack;
};

#endif
