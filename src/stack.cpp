#include "stack.h"
#include "graph.h"
#include <cmath>
#include <iostream>

using namespace std;

// constructor
Stack::Stack() {
    a = new int[MAX];
    top = -1;
}

// destructor
Stack::~Stack() {
    delete a;
}

// function to check if stack is empty
bool Stack::isEmpty() {
    return (top < 0);
}

bool Stack::push(int x) {
    if (top >= (MAX - 1)) {
        cout << "Stack Overflow";
        return false;
    } else {
        a[++top] = x;
        //cout << x << " pushed into stack\n";
        return true;
    }
}

int Stack::pop() {
    if (top < 0) {
        cout << "Stack Underflow";
        return 0;
    } else {
        int x = a[top--];
        return x;
    }
}

int Stack::peek() {
    if (top < 0) {
        cout << "Stack is Empty";
        return 0;
    } else {
        int x = a[top];
        return x;
    }
}