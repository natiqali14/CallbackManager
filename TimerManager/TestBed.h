//
// Created by natiq on 8/27/2023.
//

#ifndef TIMERMANAGER_TESTBED_H
#define TIMERMANAGER_TESTBED_H
#include <mutex>
class TestBed {
public:
    std::mutex m;
    std::mutex m2;
    int i = 1;
    TestBed() ;
    ~TestBed() ;
    void print_string();
    void test_function_call();
};
#endif //TIMERMANAGER_TESTBED_H
