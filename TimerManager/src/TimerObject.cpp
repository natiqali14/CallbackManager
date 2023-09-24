#include "TimerObject.h"
#include <iostream>
TimerObject::TimerObject(unsigned long long time, bool b_is_loop) : time_to_call(time), b_loop(b_is_loop),
                       b_now(false), current_state(TimerState::TIMER_STATE_READY), b_should_pause(false),
                       time_remaining(-1){
    if(time_to_call == 0) b_now = true;
    std::cout << "TimerObject::TimerObject -> constructed" << std::endl;
}

TimerObject::~TimerObject() {
    if(main_thread.joinable()) main_thread.join();
    std::cout << "TimerObject::~TimerObject -> destructed" << std::endl;
}

void TimerObject::set_stop_condition(bool b_stop) {
    b_loop = !b_stop;
}

void TimerObject::set_timer_state(TimerObject::TimerState state) {
    if(state == TimerState::TIMER_STATE_RUNNING) {
        if(current_state == TimerState::TIMER_STATE_PAUSED) {
            pause_timer(false);
        }
        current_state = TimerState::TIMER_STATE_RUNNING;

    }
    else if (state == TimerState::TIMER_STATE_STOPPED) {
        if(current_state == TimerState::TIMER_STATE_PAUSED) pause_timer(false);
        current_state = TimerState::TIMER_STATE_STOPPED;
        set_stop_condition(true);
    }
    else if(state == TimerState::TIMER_STATE_PAUSED) {
        current_state = TimerState::TIMER_STATE_PAUSED;
        pause_timer(true);
    }
}

void TimerObject::pause_timer(bool b_pause) {
    b_should_pause = b_pause;
}

TimerObject* TimerObject::make_object(uint64_t time, bool loop) {
    return new TimerObject(time, loop);
}
