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
       manager_history[handle]->set_timer_state(TimerObject::TimerState::TIMER_STATE_STOPPED);
       manager_history.erase(handle);
   }
}

uint32_t TimerManager::get_index_for_handle() {
    if(!useful_Indexes.empty()) {
        uint32_t index = useful_Indexes[0];
        useful_Indexes.erase(useful_Indexes.begin());
        return index;
    }
    next_index++;
    return next_index;
}

void TimerManager::delete_Timer_Manager() {
    manager_history.clear();
    delete instance;
}

bool TimerManager::timer_exist(TimerHandle &handle) {
    if(manager_history.count(handle) > 0) return true;
    return false;
}

void TimerManager::pause_timer(TimerHandle &handle) {
    if(!timer_exist(handle)) return;
    manager_history[handle]->set_timer_state(TimerObject::TimerState::TIMER_STATE_PAUSED);
}

void TimerManager::unpause_timer(TimerHandle &handle) {
    if(!timer_exist(handle)) return;
    manager_history[handle]->set_timer_state(TimerObject::TimerState::TIMER_STATE_RUNNING);
}
