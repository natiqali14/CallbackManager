#pragma once
#include <thread>
struct TimerHandle {
	int index;
};
class TimerManager
{
	
public:
	template <typename Func, typename ...Args>
	static void start_timer(TimerHandle handle, Func function, Args... args, int time, bool b_isLoop );



};

