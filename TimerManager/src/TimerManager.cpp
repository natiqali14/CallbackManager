#include <iostream>
#include "TimerManager.h"

TimerManager* TimerManager::instance = nullptr;

TimerManager::TimerManager() {
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

void TimerManager::clear_timer(TimerHandle handle) {

}
