#ifndef _EVENTLOOP_H_
#define _EVENTLOOP_H_

class Poller;

class EventLoop
{
public:
    EventLoop();
    void updateChannel();
    void loop();
private:
    Poller* poller_;
};

#endif
