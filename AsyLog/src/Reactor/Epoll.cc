#include "Reactor/Epoll.h"
#include "Readtor/Channel.h"
#include <cassert>

EpollPoller::EpollPoller():
    epfd_(::epoll_create1(EPOLL_CLOEXEC))
{
    if(epfd_ < 0)
    {
        LOG_ERROR("EpollPoller error!\n");
        abort();
    }
}

EpollPoller::~EpollPoller()
{
    ::close(epfd_);
}


int EpollPoller::dispatch()
{

}

void EpollPoller::updateChannel(Channel* channel)
{
    assert(nullptr != channel);
    int fd = channel->fd();
    int op = 0;
    if(channel->IsNew())
    {
        assert(channels.find(fd) == channels.end());
        channels[fd] = channel;
        op = EPOLL_CTL_ADD;
        EpollCtl(op, channel);
        channel->setAdd();
    }
    else if(channel->IsDelete())
    {
        assert(channels.find(fd) != channels.end());
        assert(channels[fd] = channel);
        op = EPOLL_CTL_ADD;
        EpollCtl(op, channel);
        channel->setAdd();
    }
    else
    {
        assert(channels.find(fd) != channels.end());
        assert(channels[fd] = channel);

        //处理不监听任何事件的描述符，只保留添加过的记录不占用描述符
        if(0 == channel->events())
        {
            op = EPOLL_CTL_DEL;
            EpollCtl(op, channel);
            channel->setDelete();
        }
        else
        {
            op = EPOLL_CTL_MOD;
            EpollCtl(op, channel);
        }

    }

}

void EpollPoller::delChannel(Channel* channel)
{
    assert(channels.find(fd) != channels.end());
    assert(channels[fd] = channel);
    if(channel->IsAdd())
    {
        op = EPOLL_CTL_DEL;
        EpollCtl(op, channel);
        channles_.erase(channel->fd());
        channel->setNew();
    }
}

void EpollPoller::EpollCtl(int op, Channel* channel)
{
    struct epoll_event event;

    int fd = channel->fd();
    event.events = channel->events();
    event.data.ptr = channel;

    if(::epoll_ctl(epfd_, op, fd, event) < 0)
    {
        LOG_ERROR("epoll_ctl is error, operation unknow!\n");
        abort();
    }
}
