#include "EventLoop.h"
#include "Reactor/Poller.h"
#include "Reactor/Epoll.h"

EventLoop::EventLoop():
    poller_(new EpollPoller())
{

}

void EventLoop::updateChannel()
{
    poller_->add();
}


void EventLoop::loop()
{

}