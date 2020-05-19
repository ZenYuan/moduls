#ifndef _EPOLLPOLLER_H_
#define _EPOLLPOLLER_H_
#include "Poller.h"
#include <vector>

#define MAXEVENT (32)
class Poller;
class EpollPoller: public Poller
{
public:
    EpollPoller();
    void updateChannel(Channel* channel);
    void delChannel(Channel* channel);
    int dispatch(int timeout, std::vector<Channel*>& active_channels);
    ~EpollPoller();
private:
    void EpollCtl(int op, Channel* channel);

    int epfd_;
    std::vector<struct epoll_event> revents_;
};


#endif
