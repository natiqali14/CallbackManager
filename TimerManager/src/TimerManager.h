#pragma once
#include <thread>
#include <map>
#include "TimerObject.h"

struct TimerHandle {
	uint32_t index;
};
class TimerManager
{
    TimerManager* instance = nullptr;
    std::map<uint32_t, TimerObject> manager_history;
    TimerObject obj;
	TimerManager();
    ~TimerManager();
public:
    TimerManager(const TimerManager&) = delete;
    TimerManager& operator= (const TimerManager&) = delete;
	TimerManager* GetInstance();
	template <typename Func, typename ...Args>
    void start_timer(TimerHandle handle, Func&& function, Args&&... args, int time, bool b_isLoop );
    template<typename Obj,typename Func, typename... Args>
    void start_timer(TimerHandle handle, Obj&& object ,Func&& function, Args&&... args, int time, bool b_isLoop);
	void clear_timer(TimerHandle handle);



};

