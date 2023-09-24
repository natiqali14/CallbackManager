#include <iostream>
#include "src/TimerManager.h"
#include "TestBed.h"

int main() {

    TestBed* test = new TestBed();
    TimerHandle handle;
    TimerManager::GetInstance()->start_timer(handle,1.0,true,test, &TestBed::print_string);
//    TimerManager::GetInstance()->clear_timer(handle);
//    TimerManager::GetInstance()->clear_timer(handle);
    TimerManager::GetInstance()->pause_timer(handle);
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));
    TimerManager::GetInstance()->unpause_timer(handle);
    while (true) {
        // Imaginary Application Loop


    }
    return 0;
}
