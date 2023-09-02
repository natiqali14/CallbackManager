#include <iostream>
#include "TimerManager.h"

TimerManager* TimerManager::instance = nullptr;

TimerManager::TimerManager() : next_index(0),useful_Indexes(),manager_history() {
    std::cout << "Timer Manager Constructed" << std::endl;
}

TimerManager::~TimerManager() {
    std::cout << "Timer Manager Destructed" << std::endl;
}

TimerManager* TimerManager::GetInstance() {
    if (!instance) {
        instance = new TimerManager();
    } 
    return instance;
}

void TimerManager::clear_timer(TimerHandle& handle) {
   if(manager_history[handle]) {
       std::cout << "Handle:" << handle.index << " cleared" << std::endl;
       manager_history[handle]->set_stop_condition(true);
       manager_history.erase(handle);
   }
}

uint32_t TimerManager::get_index_for_handle() {
    if(!useful_Indexes.empty()) {
        uint32_t index = useful_Indexes[0];
        useful_Indexes.erase(useful_Indexes.begin());
        std::cout << "Handle index is " << index << std::endl;
        return index;
    }
    next_index++;
    std::cout << "Handle index is " << next_index << std::endl;
    return next_index;
}

void TimerManager::delete_Timer_Manager() {

}

bool TimerManager::timer_exist(TimerHandle &handle) {
    if(manager_history[handle]) return true;
    return false;
}
