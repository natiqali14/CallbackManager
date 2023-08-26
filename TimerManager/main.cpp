#include <iostream>
#include <sstream>
#include <thread>

template <typename T,typename Func, typename ...Args>
void Apply(T&& t, Func&& f, Args&&... args) {
    (t.*f)(args...);
}

void Printer(std::string a, std::string b) {
	std::stringstream ss;
	ss << a;
	ss << b;
	std::cout << ss.str() << std::endl;
}
class TestThread {
    int counter;
    std::thread t;
public:
    TestThread(int c) : counter(c) {
        t = std::thread(&TestThread::fun,this);
        std::cout << "Created Thread" << std::endl;
    }
    void fun() {
        while(counter-- > 0) {
            std::cout << counter << std::endl;
        }
    }
    ~TestThread() {if(t.joinable()){t.join();} std::cout << "Destroyed thread";}
};
class A {
public:
    int i;
    A(int inte) : i(inte){}
    void fun(){std::cout << "Called" << std::endl;}

};
int main() {
    A obj {2};
    Apply(obj,&A::fun);
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

