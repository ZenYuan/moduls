#ifndef _EVENTLOOP_H_
#define _EVENTLOOP_H_
#include <vector>

class Poller;
class Channel;
class EventLoop
{
public:
    EventLoop();
    void updateChannel(Channel* channel);
    void loop();
private:
    Poller* poller_;
    std::vector<Channel*> active_channels_;
};

#endif
