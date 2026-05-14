#include "util.h"
#include <iostream>
#include <string>

using namespace std;

// get user input and evaluate it
string nextCommand(string &strInput, int &src, int &dest, int &flag) {

    string input;
    string path;

    while (1) {
        // get user command and convert it to upper case(remove TBD)
        cin >> input;

        if (input == " " || input == "\t" || input == "\n") {
            continue;
        }

        if (input == "write") {
            cin >> path;
            if (path != "path") {
                cout << "Error: invalid write path query\n";
                break;
            }
            input = input + " " + path;
            cin >> src;
            cin >> dest;
            cout << "Query: write path " << src << " " << dest << "\n";
            break;
        }

        if (input == "stop") {
            input = "stop";
            cout << "Query: stop"
                 << "\n";
            break;
        }

        if (input == "find") {
            cin >> src;
            cin >> dest;
            cin >> flag;
            cout << "Query: find " << src << " " << dest << " " << flag << "\n";
            break;
        }
        break;
    }

    return input;
}
