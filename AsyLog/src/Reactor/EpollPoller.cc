#include "Reactor/EpollPoller.h"

EpollPoller::EpollPoller():
    epfd_(::epoll_create()),
    revents_(maxEventNum_)
{
    if(epfd_ < 0)
    {
        LOG_ERROR("EpollPoller error!\n");
    }
}

EpollPoller::~EpollPoller()
{
    ::close(epfd_);
}


int EpollPoller::dispatch()
{

}

int EpollPoller::add(Channel* channel)
{

}

int EpollPoller::del()
{

}

