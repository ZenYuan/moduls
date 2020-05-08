#ifndef _POLLER_H_
#define _POLLER_H_
#include <map>
#include <vector>

class Channel;

class Poller
{
public:
    Poller();
    virtual int add() = 0;
    virtual int del() = 0;
    virtual int dispatch() = 0;
    virtual ~Poller() = 0;
protected:
    std::map<int, channel*> ChannelMap;
};

#endif
