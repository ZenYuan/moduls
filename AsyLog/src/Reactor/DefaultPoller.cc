#ifndef __DEFAULT_POLLER_H_
#define __DEFAULT_POLLER_H_

class Poller;

class DefaultPoller:public Poller
{
public:
    void updateChannel(Channel* channel);
    void delChannel(Channel* channel);
    void dispatch();
};

#endif
