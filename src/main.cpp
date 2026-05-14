#include "graph.h"
#include "heap.h"
#include "util.h"
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, char *argv[]) {
    // std::cout << argv[0] << std::endl;

    // if (argc < 2) {
    //     // Tell the user how to run the program
    //     std::cerr << "Usage: " << argv[0] << " NAME" << std::endl;
    // }

    // input variables
    int input;
    string command, strInput, graphType;
    ifstream file;

    // graph variables
    Graph *graph;
    int n, m; // V and E represent the number of vertices and edges respectively
    int src, dest;
    float weight;
    int flag;

    int source, destination; // from find command
    int s, d;                // from 'write path' command

    // read command line arguments
    if (argc > 0) {
        strInput = argv[1];
        graphType = argv[2];
        file.open(strInput);
    } else {
        cin >> strInput;
        cin >> graphType;
    }

    if (file) {
        file >> n; // get number of vertices
        file >> m; // get number of edges
        graph = new Graph(n, m);

        // get input from file
        while (file >> input) {
            file >> src;
            file >> dest;
            file >> weight;
            graph->addEdge(src, dest, weight);
            if (graphType == "undirected") {
                graph->addEdge(dest, src, weight);
            }
        }
        file.close();
    } else {
        cout << "Error: cannot open file for reading\n";
        exit(0);
    }

    int validFindCommandFlag = 0;

    while (1) {
        // get user input and pass by reference
        command = nextCommand(strInput, src, dest, flag);

        if (command == "write path") {
            // write path <s> <d>
            // store s and d
            s = src;
            d = dest;

            if (validFindCommandFlag == 0) {
                cout << "Error: no path computation done\n";
                continue; // wait for the next query
            }

            // if s != source or d not ∈ V \{s}, your program should write a message to stdout using the following format and wait for the next query.
            else if ((s != source) || (!graph->isGraphVertex(d))) {
                cout << "Error: invalid source destination pair\n";
                continue; //wait for the next query
            }

            graph->computeShortestPath(s, d, destination);
        }

        if (command == "find") {
            // this query is valid if source ∈ V , destination is an integer not equal to source, and flag ∈{0,1}.
            if ((src == dest) || (flag != 1 && flag != 0) || (!graph->isGraphVertex(src))) {
                cout << "Error: invalid find query\n";
                continue;
            }

            // store the src and dest for possible use in 'write path' command
            source = src;
            destination = dest;

            // store flag value to be verified during printing
            graph->flagFind = flag;

            graph->performDijkstra(flag, src, dest);

            // set the flag indicating valid find command is executed
            validFindCommandFlag = 1;
        }

        if (command == "stop") {
            // delete graph. graph object is allocated with new in main
            if (graph)
                delete graph;

            exit(0);
        }
    }
}