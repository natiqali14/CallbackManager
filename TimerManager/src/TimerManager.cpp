#include <iostream>
#include "TimerManager.h"

TimerManager::TimerManager() {
    std::cout << "Timer Manager Constructed" << std::endl;
}

TimerManager::~TimerManager() {
    std::cout << "Timer Manager Destructed" << std::endl;
}

TimerManager* TimerManager::GetInstance() {
    if(!instance) return new TimerManager();
    return instance;
}

void TimerManager::clear_timer(TimerHandle handle) {

}

template<typename Func, typename... Args>
void TimerManager::start_timer(TimerHandle handle, Func&& function, Args&&... args, int time, bool b_isLoop) {

}

template<typename Obj,typename Func, typename... Args>
void TimerManager::start_timer(TimerHandle handle, Obj&& object ,Func&& function, Args&&... args, int time, bool b_isLoop) {

}
