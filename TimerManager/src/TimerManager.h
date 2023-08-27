#pragma once
#include <thread>
#include <map>
#include "TimerObject.h"
struct TimerHandle {
	uint32_t index = 0;
};
class TimerManager
{
    static TimerManager* instance;
    std::map<uint32_t , TimerObject*> manager_history;
    uint32_t next_index = 0;
    TimerManager();

public:
    ~TimerManager();
    TimerManager(const TimerManager&) = delete;
    TimerManager& operator= (const TimerManager&) = delete;
	static TimerManager* GetInstance();

    template<typename Obj,typename Func, typename... Args>
    void start_timer(TimerHandle& handle, double time, bool b_isLoop, Obj&& object ,Func&& function, Args&&... args) {
        handle.index = next_index;
        next_index++;

        auto time_in_micro = static_cast<unsigned long long> (time *1e6);
        TimerObject* obj = new TimerObject(time_in_micro,b_isLoop);
        manager_history.insert(std::make_pair(handle.index,obj));
        obj->pass_function(object,function,args...);
    }

	void clear_timer(TimerHandle handle);
    void print();
};

