#ifndef _EPOLLPOLLER_H_
#define _EPOLLPOLLER_H_
#include "Reactor/Poller.h"
#include <vector>

class EpollPoller: public Poller
{
public:
    EpollPoller();
    int add(Channel* channel);
    int del();
    int dispatch();
    ~EpollPoller();
private:
    int addChannel(int operation, Channel* channel);

    int epfd_;
    const int maxEventNum_ = 32;
    vector<struct event> revents_;
};


#endif
