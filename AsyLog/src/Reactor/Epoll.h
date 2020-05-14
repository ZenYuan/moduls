#ifndef _EPOLLPOLLER_H_
#define _EPOLLPOLLER_H_
#include "Reactor/Poller.h"
#include <vector>

#define MAXEVENT (32)

class EpollPoller: public Poller
{
public:
    EpollPoller();
    void updateChannel(Channel* channel);
    void delChannel(Channel* channel);
    void dispatch();
    ~EpollPoller();
private:
    void EpollCtl(int op, Channel* channel);

    int epfd_;
    vector<struct epoll_event> revents_;
};


#endif
