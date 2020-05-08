#ifndef _CHANNEL_H_
#define _CHANNEL_H_
#include <functional>

class Channel
{
public:
    typedef void (*Loop_CallBack)(int fd);
    void setCallWrite(Loop_CallBack WriteFunc){ WriteCallBack = WriteFunc; }
    void setCallRead(Loop_CallBack ReadFunc){ ReadCallBack = ReadFunc; }

    void registReadEvent(){ events_ |= POLLIN; update();}
    void registWriteEvent(){ events_ |= POLLOUT; update();}
    void disRegistReadEvent(){ events_ &= ~POLLIN; update();}
    void disRegistWriteEvent(){ events_ &= ~POLLOUT; update();}

    void handleEvent();
private:
    void update();

    EventLoop* loop_;
    int fd_;
    int events_;

    Loop_CallBack ReadCallBack;
    Loop_CallBack WriteCallBack;
};

#endif
