#include "EventLoop.h"
#include "Poller.h"
#include "Epoll.h"
#include "../log/Logging.h"

const int poll_time = 10000;  //MS
EventLoop::EventLoop():
    poller_(new EpollPoller()),
    active_channels_(MAXEVENT * 2)
{
    if(nullptr == poller_)
    {
        LOG_ERROR("poller error!\n");
        abort();
    }
}

void EventLoop::updateChannel(Channel* channel)
{
    poller_->updateChannel(channel);
}

void EventLoop::loop()
{
    poller_->dispatch(poll_time, active_channels_);
}