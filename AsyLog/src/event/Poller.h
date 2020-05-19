#ifndef _POLLER_H_
#define _POLLER_H_
#include <map>
#include <vector>

class Channel;
class Poller
{
public:
    //增加和修改
    virtual void updateChannel(Channel* channel)= 0;
    virtual void delChannel(Channel* channel) = 0;
    virtual int dispatch(int timeout, std::vector<Channel*>& active_channels) = 0;
    virtual ~Poller() = default;
protected:
    //记录加入到reactor的和没有监听事件的fd
    std::map<int, Channel*> channels_;
};

#endif
