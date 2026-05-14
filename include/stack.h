#pragma once

#define MAX 0x7ffff

// create a stack
class Stack {
    int top;

public:
    // constructor and destructor
    Stack();
    ~Stack();

    int *a;

    // functions to be implemented in stack.cpp
    bool push(int x);
    int pop();
    int peek();
    bool isEmpty();
};