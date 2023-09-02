//
// Created by natiq on 8/27/2023.
//
#include <mutex>
#include "TestBed.h"
#include <iostream>
TestBed::TestBed() {
    i = 0;
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
