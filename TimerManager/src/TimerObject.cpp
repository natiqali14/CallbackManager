#include "TimerObject.h"
#include <iostream>
TimerObject::TimerObject(unsigned long long time, bool b_is_loop) : time_to_call(time), b_loop(b_is_loop),
                       b_now(false),b_should_stop(false), current_state(TimerState::TIMER_STATE_READY) {
    if(time_to_call == 0) b_now = true;
    std::cout << "TimerObject::TimerObject -> constructed" << std::endl;
}

TimerObject::~TimerObject() {



    std::cout << "TimerObject::~TimerObject -> destructed" << std::endl;
}

void TimerObject::set_stop_condition(bool b_stop) {
    b_should_stop = b_stop;
}

void TimerObject::join_all_threads() {
    std::cout << "Join" << std::endl;
}