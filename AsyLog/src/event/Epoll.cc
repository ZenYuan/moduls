#include "Epoll.h"
#include "Channel.h"
#include "../log/Logging.h"
#include <cassert>
#include <sys/epoll.h>
#include <unistd.h>
#include <cerrno>

EpollPoller::EpollPoller():
    epfd_(::epoll_create1(EPOLL_CLOEXEC)),
    revents_(MAXEVENT)
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

int EpollPoller::dispatch(int timeout, std::vector<Channel*>& active_channels)
{
    int num_events = ::epoll_wait(epfd_, &(revents_[0]), revents_.size(), timeout);
    int errno_tmp = errno;
    if(num_events > 0)
    {
        LOG_INFO("event num:%d has happing\n", num_events);
        for(int i = 0; i < num_events; i++)
        {
            Channel* channel = static_cast<Channel*>(revents_[i].data.ptr);
            channel->setRevent(revents_[i].events);
            active_channels.push_back(channel);
        }
        if(num_events == static_cast<int>(revents_.size()))
        {
            revents_.resize(revents_.size() * 2);
        }
    }
    else if(0 == num_events)
    {
        LOG_WARN("nothing event happend!\n");
    }
    else
    {
        if(EINTR == errno_tmp)
        {
            errno = errno_tmp;
            LOG_ERROR("dispatch get singal errno!\n");
        }
    }
    return 0;
}

void EpollPoller::updateChannel(Channel* channel)
{
    assert(nullptr != channel);
    int fd = channel->fd();
    int op = 0;
    if(channel->IsNew())
    {
        assert(channels_.find(fd) == channels_.end());
        channels_[fd] = channel;
        op = EPOLL_CTL_ADD;
        EpollCtl(op, channel);
        channel->setAdd();
    }
    else if(channel->IsDelete())
    {
        assert(channels_.find(fd) != channels_.end());
        assert(channels_[fd] = channel);
        op = EPOLL_CTL_ADD;
        EpollCtl(op, channel);
        channel->setAdd();
    }
    else
    {
        assert(channels_.find(fd) != channels_.end());
        assert(channels_[fd] = channel);

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
    assert(channels_.find(channel->fd()) != channels_.end());
    assert(channels_[channel->fd()] = channel);
    int op = 0;
    if(channel->IsAdd())
    {
        op = EPOLL_CTL_DEL;
        EpollCtl(op, channel);
        channels_.erase(channel->fd());
        channel->setNew();
    }
}

void EpollPoller::EpollCtl(int op, Channel* channel)
{
    struct epoll_event event;

    int fd = channel->fd();

    if(channel->events() & EV_READ)
    {
        event.events |= EPOLLIN;
    }
    if(channel->events() & EV_WRITE)
    {
        event.events |= EPOLLOUT;
    }
    event.data.ptr = channel;

    if(::epoll_ctl(epfd_, op, fd, &event) < 0)
    {
        LOG_ERROR("epoll_ctl is error, operation unknow!\n");
    }
}
