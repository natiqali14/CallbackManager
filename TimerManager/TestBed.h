//
// Created by natiq on 8/27/2023.
//

#ifndef TIMERMANAGER_TESTBED_H
#define TIMERMANAGER_TESTBED_H
#include <iostream>
#include <atomic>

class TestBed {
public:
    std::atomic<int> i {1};
    TestBed() ;
    ~TestBed() ;

    void print_string(int s);
};


#endif //TIMERMANAGER_TESTBED_H
