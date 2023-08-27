#include <iostream>
#include "src/TimerManager.h"
#include "TestBed.h"

int main() {
    TestBed* test = new TestBed();

    TimerHandle handle;
    TimerManager::GetInstance()->start_timer(handle,3.0,false,test, &TestBed::print_string,1);
    TimerHandle handle2;
    TimerManager::GetInstance()->start_timer(handle2,.50,true,test, &TestBed::print_string,1);
    while (true) {
        // Imaginary Application Loop

    }
    return 0;
}

/**
* Plan of Action
* 1. Timer manager
* Timer manager will be a simple singleton
* Will manage all timers, garabage collection
* TODO: ?
* a. Timer starter, b. looping timer, c. Deleting timer, d. garbage collection of timer.
* For timer should use delgates to call function .
* Function can have n numbers of Vars
* Will have a timer handle for timer objects mapping
* 
*/

