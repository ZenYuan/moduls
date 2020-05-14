#include "Reactor/DefaultPoller.h"
#include "Reactor/Poller.h"

void DefaultPoller::updateChannel(Channel* channel)
{
    Poller::updateChannel(channel);
}
void DefaultPoller::delChannel(Channel* channel)
{
    Poller::delChannel(channel);
}
void DefaultPoller::dispatch()
{
    Poller::dispatch();
}