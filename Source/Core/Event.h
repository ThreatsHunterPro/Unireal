#pragma once
#include <functional>

template <typename... Types>
class Event
{
public:
    using Action = std::function<void(Types...)>;
    
private:
    std::list<Action> callbacks;
    
public:
    Event()
    {
        
    }
    Event(Action _action)
    {
        callbacks.push_back(_action);
    }
    
    void Invoke(Types... _args)
    {
        for (const auto& _callBack : callbacks)
        {
            _callBack(_args...);
        }
    }

    void operator+=(Action _callback)
    {
        callbacks.push_back(_callback);
    }
    void operator-=(Action _callback)
    {
        callbacks.remove(_callback);
    }
};

using Action = Event<>::Action;