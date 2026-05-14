#pragma once

#include "heap.h"

// struct to represent Vertex attributes
struct Vertex {
    int pi; // parent index
    char color;
    int dsc, fin;
    float d;   // distance
    int index; // index in heap array
};

// Linked List to represent the edges of the graph
struct Node {
    int v;      // stores vertex id
    float w;    // weight
    Node *next; // pointer to next element
};

class Graph {
public:
    Node **Adj; // array of linked lists, Adj[u] contains all vertices adjacent to u
    Vertex *V;
    MinHeap *Q;
    int vertices;
    int flagFind; // flag ∈{0,1}

    // constructor and destructor
    Graph();
    Graph(int n, int m);
    ~Graph();

    // functions to be implemented in Graph.cpp
    void addEdge(int src, int dest);
    void addEdge(int src, int dest, float w);
    int performDijkstra(int flagFind, int s, int t);
    void initSingleSrce(int src);
    void relax(int u, int v, float w);
    void printGraph();
    bool isGraphVertex(int v);
    bool computeShortestPath(int s, int d, int findCommandDestination);
};