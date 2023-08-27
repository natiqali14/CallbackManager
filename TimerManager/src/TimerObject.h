#pragma once

#include <thread>
#include <iostream>
#include <vector>
#include <mutex>
enum class TimerState : uint8_t {
    TIMER_STATE_RUNNING,
    TIMER_STATE_STOPPED,
    TIMER_STATE_READY,
};
class TimerObject
{
    friend class TimerManager;
    TimerState current_state;
    std::vector<std::thread> thread_list;
    std::thread main_thread;
    unsigned long long time_to_call;
    bool b_loop;
    bool b_now;
    bool b_should_stop;
    std::mutex m;
    TimerObject(unsigned long long time, bool b_is_loop);
    void join_all_threads();

    template<typename Object, typename Function, typename ...Args>
    void pass_function(Object&& object, Function&& function, Args&&... args) {
        main_thread = std::thread([this, object, function,args...](){
            thread_looper(object,function,args...);
        });
    }

    template<typename Object, typename Function, typename ...Args>
    void thread_looper(Object&& obj, Function&& function, Args &&... args) {
        if(b_now) {
            if(b_loop) {
                while (true) {
                    if(b_should_stop) break;
                    std::thread t = std::thread([&]() {
                        (obj->*function)(args...);
                    });
                    thread_list.push_back(std::move(t));
                }
            }
            else {
                std::thread t = std::thread([&]() {
                    (obj->*function)(args...);
                });
                thread_list.push_back(std::move(t));

            }

        }
        auto begin = std::chrono::high_resolution_clock::now();
        while (true) {
            if(b_should_stop) break;
            auto new_time = std::chrono::high_resolution_clock::now();
            auto total = std::chrono::duration_cast<std::chrono::microseconds>(new_time - begin).count();
            if(total >= time_to_call) {
                if(!b_loop) {

                    std::thread t = std::thread([&]() {
                        (obj->*function)(args...);
                    });
                    t.join();
                    thread_list.push_back(std::move(t));

                    break;
                }
                else {

                    std::thread t = std::thread([&]() {
                        (obj->*function)(args...);
                    });
                    t.join();
                    thread_list.push_back(std::move(t));

                    begin = std::chrono::high_resolution_clock::now();
                    continue;

                }
            }
        }
       join_all_threads();
    }
    

    void set_stop_condition(bool b_stop);
public:
    ~TimerObject();

};

