#include "graph.h"
#include "stack.h"
#include <iostream>

using namespace std;

// default constructor
Graph::Graph() {
    vertices = 0;
    Adj = NULL; // Adj[u] contains all vertices adjacent to u
    V = NULL;
    Q = NULL;
    flagFind = 0;
}

// parameterized constructor
Graph::Graph(int n, int m) {
    vertices = n;
    Adj = (Node **)calloc(n + 1, sizeof(Node *)); // Adj[u] contains all vertices adjacent to u
    V = (Vertex *)calloc(n + 1, sizeof(Vertex));
    Q = NULL;
}

// destructor
Graph::~Graph() {
    // Adj is allocated with calloc in constructor(Node **)
    // use free to deallocate it
    for (int x = 0; x <= vertices; x++) {
        Node *temp = Adj[x];
        while (temp != NULL) {
            Node *current = temp;

            temp = temp->next;
            delete current;
            current = NULL;
        }

        Adj[x] = NULL;
    }
    if (Adj)
        free(Adj);

    // V is allocated with calloc in constructor (Vertex *)
    // use free to deallocate it
    if (V) {
        delete V;
    }

    // Q is allocated in performDijkstraVariant with new operator (MinHeap *Q)
    // use delete to deallocate it
    if (Q)
        delete Q;
}

// function to add unweighted edge
void Graph::addEdge(int s, int dest) {
    Node *node = new Node;
    node->v = dest;
    node->next = Adj[s];
    Adj[s] = node;
}

// function to add weighted edge
void Graph::addEdge(int s, int dest, float w) {
    Node *node = new Node;
    node->v = dest;
    node->w = w;
    node->next = Adj[s];
    Adj[s] = node;
}

void Graph::relax(int u, int v, float w) {
    if (V[v].d > V[u].d + w) {
        float fVal = V[u].d + w;

        // no min-heap operations are printed if flag is 0
        if (flagFind)
            printf("Decrease key of vertex %d, from %12.4f to %12.4f\n", v, V[v].d, fVal);

        V[v].d = V[u].d + w;
        V[v].pi = u;
    }
}

// function to perform DFS on graph
int Graph::performDijkstra(int flagFind, int s, int t) {
    // initialize the min-heap with only the source vertex s
    initSingleSrce(s);

    // insert s into initially empty Q
    Q = new MinHeap(vertices);

    Q->insert(s, V[s].d, V[s].index, flagFind);

    int u;

    while ((Q != NULL) && (Q->size > 0)) {
        u = Q->extractMin(flagFind);

        if (u == 0)
            return 0;
        // u is removed from heap, hence set its index to 0
        V[u].index = 0;

        if (Q->size > 0) {
            V[Q->arr[1]->u].index = 1;
        }
        if (u == t) {
            return 1;
        }

        Node *temp = Adj[u];

        while (temp != NULL) {
            int v = temp->v;
            if (V[v].color == 'W') {
                V[v].d = V[u].d + temp->w;
                V[v].pi = u;
                V[v].color = 'G';
                Q->insert(v, V[v].d, V[v].index, flagFind);
            } else if (V[v].d > V[u].d + temp->w) {
                relax(u, v, temp->w);

                Q->decreaseKey(V[v].index, V[v].d);
            }
            temp = temp->next;
        }
        V[u].color = 'B';
    };
    return 1;
}

void Graph::initSingleSrce(int s) {
    for (int x = 1; x <= vertices; x++) {
        V[x].d = 0;
        V[x].color = 'W';
        V[x].pi = 0;
    }
    V[s].d = 0;
    V[s].color = 'G';
}

// function to print adjacency list of G
void Graph::printGraph() {
    for (int x = 1; x <= vertices; x++) {
        Node *temp = Adj[x];
        cout << x << ": ";
        while (temp != NULL) {
            cout << " --> " << temp->v;
            temp = temp->next;
        }
        cout << "\n";
    }
}

bool Graph::isGraphVertex(int v) {
    bool isVertex = false;
    for (int x = 1; x <= vertices; x++) {
        if (x == v) {
            isVertex = true;
            break;
        }
    }
    return isVertex;
}

// function to compute the shortest path
bool Graph::computeShortestPath(int s, int d, int findCommandDestination) {
    class Stack stack;
    int temp = d;

    while (temp != 0) {
        stack.push(temp);
        temp = V[temp].pi;
        if (temp == s)
            break;
    }
    if (temp != 0 && temp == s) {
        stack.push(temp);

        string pathShortest = "Shortest path: ";
        string pathNotKnownTobeShortest = "Path not known to be shortest: ";

        string pathString;

        //if find command destination is vertex not in graph vertices, then shortest path is ensured
        //since current graph vertices are numbered from 1 to 8, any destination vertex > 8 or < 0 would
        //ensure shortest path
        if (findCommandDestination > vertices || findCommandDestination < 0 || d == findCommandDestination)
            pathString = pathShortest;
        else
            pathString = pathNotKnownTobeShortest;

        cout << pathString << "<";
        while (!stack.isEmpty()) {
            // print top element in stack
            cout << stack.peek();

            // remove top element in stack
            stack.pop();

            if (!stack.isEmpty())
                cout << ", ";
        }
        cout << ">\n";

        printf("The path weight is: % 12.4f\n", V[d].d);

        return 1;
    } else if ((temp == 0) && (temp != s) && (findCommandDestination > vertices)) {
        printf("No %d-%d path exists.\n", s, d);
        return 0;
    } else if ((temp == 0) && (temp != s) && (findCommandDestination <= vertices)) {
        printf("No %d-%d path has been computed.\n", s, d);
        return 0;
    }
    return 0;
}