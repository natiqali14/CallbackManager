#include <iostream>
#include <sstream>

template <typename T, typename ...Args>
void Apply(T&& t, Args... args) {
	t(args...);
	
}

void Printer(std::string a, std::string b) {
	std::stringstream ss;
	ss << a;
	ss << b;
	std::cout << ss.str() << std::endl;
}

int main() {
	auto l = []() {};
	Apply(Printer,"a","a");
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

