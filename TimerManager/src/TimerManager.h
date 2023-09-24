#pragma once
#include <thread>
#include <map>
#include "TimerObject.h"

/**
 * This struct works as a simple identifier for a @class: TimerObject object.
 * @param: index holds the identifier for TimerHandle;
 */
struct TimerHandle {
private:
    friend class TimerManager;
	uint32_t index = -1;
public:
    bool operator==(const TimerHandle& other) const {
        return index == other.index;
    }
    bool operator!=(const TimerHandle& other) const {
        return index!=other.index;
    }
    bool operator<(const TimerHandle& other) const {
        return index < other.index;
    }
};

/**
 * @brief: This class manages all the TimerObject objects.
 * It's a singleton class.
 * Use @function: start_timer to start a timer object
 * To stop / delete a timer call @function clear_timer.
 */
class TimerManager
{
    static TimerManager* instance; // singleton instance for this class
    std::map<TimerHandle , std::unique_ptr<TimerObject>> manager_history; // Manages all the timer objects
    uint32_t next_index; // simple identifier generator variable;
    std::vector<uint32_t> useful_Indexes; // This takes past identifier index if some timers are stopped / deleted.
    uint32_t get_index_for_handle(); // Function to populate TimerHandle object i.e. to give an identifier to the handle.
    void delete_Timer_Manager(); // This will delete the timer manger class and stops all the TimerObject objects.
    TimerManager();
    ~TimerManager();

public:

    TimerManager(const TimerManager&) = delete;
    TimerManager& operator= (const TimerManager&) = delete;
	static TimerManager* GetInstance();

    /**
     *
     * @tparam Obj : templated object pointer for the function to be called.
     * @tparam Func : templated function pointer for calling the function.
     * @tparam Args : templated Arguments for the function. variable amount can be [0 ,N]. Using variadic variables
     * @param handle : TimerHandle for identifier. It expects a l-value
     * @param time : time after which it will be called
     * @param b_isLoop : boolean to check if function will be called continuously after time seconds.
     * @param object : object pointer for the function to be called. Uses universal reference can take both l, r, values
     * @param function : function pointer for calling the function. Uses universal reference can take both l, r, values
     * @param args :  Arguments for the function. variable amount can be [0 ,N] Using variadic variables.
     * Uses universal reference can take both l, r, values
     * @return : boolean if handle is not unique then return false without creating a TimerObject.
     * @brief: This function first check if the handle is already in use or not.
     * Then it populates the new unique handle. after than it changes the time from seconds (double) to micro-seconds
     * (uint64_t). Then it makes a TimerObject object and then pass the object and function pointer to the timer object
     * where it starts a thread to call the function given to it.
     */
    template<typename Obj,typename Func, typename... Args>
    bool start_timer(TimerHandle& handle, double time, bool b_isLoop, const Obj& object , const Func& function, Args&&... args) {
        if (manager_history.count(handle)) {
            std::cout << "Timer handle already exist. Every new timers need its own specific Timer handle."
                      << std::endl;
            return false;
        }
        handle.index = get_index_for_handle();
        auto time_in_micro = static_cast<uint64_t> (time * 1e6);
        std::unique_ptr<TimerObject> obj =
                std::unique_ptr<TimerObject>(TimerObject::make_object(time_in_micro,b_isLoop));

        manager_history.insert(std::make_pair(handle, std::move(obj)));
        manager_history[handle]->pass_function(object, function, args...);
        return true;
    }

    /**
     * @param handle : unique identifier for the TimerObject.
     * Use this function to stop / delete a timer.
     *
     */
	void clear_timer(TimerHandle& handle);
    /**
     * @param handle : nique identifier for the TimerObject.
     * @return boolean true if timer exists else false
     */
    bool timer_exist(TimerHandle& handle);
    /**
     * @brief: Pausing timer object
     * @param handle : unique identifier for the TimerObject.
     */
    void pause_timer(TimerHandle& handle);
    /**
     * @brief: Un-Pausing timer object
     * @param handle : unique identifier for the TimerObject.
     */
    void unpause_timer(TimerHandle& handle);
};

