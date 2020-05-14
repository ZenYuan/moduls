#include "Reactor/Channel.h"
#include "Reactor/EpollPoller.h"


Channel::Channel((EventLoop* loop, int fd, int events)
    :loop_(loop), fd_(fd), events_(events),code_(kNew)
{
    LOG_INFO("channel set success!\n");
}


void Channel::update()
{
    loop_->updateChannel();
}


void Channel::handleEvent()
{

}