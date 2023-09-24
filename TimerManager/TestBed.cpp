//
// Created by natiq on 8/27/2023.
//

#include "TestBed.h"
#include "src/TimerManager.h"
#include <iostream>

TestBed::TestBed() {
    i = 0;
    TimerHandle handle;
    TimerManager::GetInstance()->start_timer(handle,3.0,true,this,&TestBed::test_function_call);
}
TestBed::~TestBed() {
    std::cout << "Test Bed object destroyed" << std::endl;
}
void TestBed::print_string() {
    m.lock();
    for(int j = 0; j < 100000; j++) i++;
    std::cout << i << std::endl;
    m.unlock();
}

void TestBed::test_function_call() {
    m2.lock();
    std::cout << "Test Function call" << "\n";
    m2.unlock();
}
