//
// Created by natiq on 8/27/2023.
//

#ifndef TIMERMANAGER_TESTBED_H
#define TIMERMANAGER_TESTBED_H
class TestBed {
public:
    std::mutex m;
    int i = 1;
    TestBed() ;
    ~TestBed() ;
    void print_string();
};
#endif //TIMERMANAGER_TESTBED_H
