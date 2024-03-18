#pragma once

#include <iostream>

class EntryPoint {
public:
    EntryPoint() : test(0) {}
    ~EntryPoint() = default;

    void Test();

private: 
    int test;
};

