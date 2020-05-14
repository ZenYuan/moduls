#ifndef _POLLER_H_
#define _POLLER_H_
#include <map>
#include <vector>

class Channel;
class Poller
{
public:
    //包含增加和修改

    virtual int updateChannel(Channel* channel)= 0;
    virtual int delChannel(Channel* channel) = 0;
    virtual int dispatch() = 0;
    virtual ~Poller() = 0;
protected:
    //记录加入到reactor的和没有监听事件的fd
    typedef std::map<int, Channel*> channel_fd_map;
    channel_fd_map channels_;

};

//TODO:pure virtual可已有一个默认实现
inline int Poller::updateChannel(Channel* channel)
{
    //TODO:
}
inline int delChannel(Channel* channel)
{
    //TODO:
}
inline int dispatch()
{
    //TODO:
}
#endif
