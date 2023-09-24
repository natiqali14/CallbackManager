#pragma once

#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
class TimerObject
{
    static TimerObject* make_object(uint64_t time, bool loop);

    enum class TimerState : uint8_t {
        TIMER_STATE_RUNNING,
        TIMER_STATE_STOPPED,
        TIMER_STATE_READY,
        TIMER_STATE_PAUSED,
    };
    TimerObject(unsigned long long time, bool b_is_loop);
    friend class TimerManager;
    TimerState current_state;
    std::vector<std::thread> thread_list;
    std::thread main_thread;
    uint64_t time_to_call;
    uint64_t time_remaining;
    bool b_loop;
    bool b_now;
    bool b_should_pause;
    std::mutex m;
    TimerObject() = default;
    template<typename Object, typename Function, typename ...Args>
    void pass_function(const Object& object, const Function& function, Args&&... args) {
        /**
         * Time manager will call this function with all required arguments.
         * This function will start a thread and program flow will go back to TimerManager and then to the function
         * calling TimerManager.
         * In this function our main_thread variable will call another thread through function start_thread
         * that will call the function passed by the TimerManager.
         * In this way we can have main_thread join at the destruction phase. And our program will not stall here.
         */
        main_thread = std::thread([this, object, function,args...](){
            start_thread(object,function,args...);
        });
    }

    template<typename Object, typename Function, typename ...Args>
    void start_thread(const Object& obj, const Function& function, Args&&... args) {
        /**
         * This is the function that is running in the main_thread "thread".
         * In this function we call another thread "t" that will run the argument function.
         * t "thread" is controlled by the member variable of this class.
         * @param: b_loop : to call the function infinite time.
         * @param: time_to_call : to call function after this time.
         */
        std::thread t = std::thread([&] () {
            do {
                auto begin = std::chrono::high_resolution_clock::now();
                while (b_loop) {
                    auto new_time = std::chrono::high_resolution_clock::now();
                    auto total = std::chrono::duration_cast<std::chrono::microseconds>(new_time - begin).count();
                    if(time_remaining != -1){
                        total = (long long) time_remaining;
                        time_remaining = -1;
                    }
                    if(b_should_pause) {
                        time_remaining = total;
                        while (b_should_pause) {}  // do nothing
                    }
                    if(total >= time_to_call && b_loop) {
                        time_remaining = -1;
                        (obj->*function)(args...);
                        break;
                    }
                }
            } while (b_loop);
        });
        t.join();
    }
    /**
     * @brief: Making this class a state machine. Changing the state will change the behavior of the timer object
     * @param state : 1. TIMER_STATE_RUNNING -> This object will start running
     * 2. TIMER_STATE_STOPPED -> With this timer object will stop and will be deleted.
     * 3. TIMER_STATE_PAUSED -> Timer object will be paused, (to unpause set state to TIMER_STATE_RUNNING )
     * 4. TIMER_STATE_READY -> Initial state of the timer object.
     */
    void set_timer_state(TimerState state);

    /**
     * @brief: Stopping the object and deleting it in the TimerManager class.
     * @param b_stop
     */
    void set_stop_condition(bool b_stop);
    /**
     * @brief: Pausing / un-pausing timer
     * @param b_pause
     */
    void pause_timer(bool b_pause);
public:
    ~TimerObject();
};
