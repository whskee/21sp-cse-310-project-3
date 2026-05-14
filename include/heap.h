#pragma once

// struct elements for the head
struct Element {
    int u; // points to vertex V[vertex]
    float key;
};

// create a HEAP
class MinHeap {
public:
    int capacity;
    int size;
    Element **arr;
    MinHeap *Q;

    // constructor and destructor
    MinHeap();
    MinHeap(int n);
    ~MinHeap();

    // function to be implemented in heap.cpp
    void buildHeap(Element *arr, int size);
    void insert(int u, float key, int &index, int flagFind);
    int extractMin(int flagFind);
    void decreaseKey(int index, float newKey);
    void minHeapify(int index);
    void printHeap();
    void swap(int x, int y);
    int getLeft(int i);
    int getRight(int i);
    int getParent(int i);
};
