#pragma once

struct A {
    A(int inputData);
    void foo();
    friend bool operator==(const A &a1, const A &a2);
    int member;
};