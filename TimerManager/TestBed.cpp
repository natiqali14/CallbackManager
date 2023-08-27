//
// Created by natiq on 8/27/2023.
//

#include <thread>
#include "TestBed.h"


TestBed::TestBed() {
    i = 0;
}

TestBed::~TestBed() {
    std::cout << "";
}
void TestBed::print_string(int s) {
    std::cout << i << std::endl;
   std::this_thread::sleep_for(std::chrono::seconds(2));

    i++;
}
