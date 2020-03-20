/*
 * Tomomi Nakamura
 * file@ myDriver.cpp
 * Graph & Shortest Path
 */

#include <iostream>
#include <fstream>
#include "graphl.h"
#include "graphm.h"
#include "nodedata.h"
#include "nodedata.cpp"
using namespace std;

// ------------------------------------ Test1() -----------------------------------------------

// Description

// Test1():         testing Nodedata constructor, GraphM constructor, buildGraph, removEdge
//                  findShortestPath, display, displayAll
//
// --------------------------------------------------------------------------------------------
void Test1(ifstream& infile)
{

    for (;;){
        GraphM G;

        G.buildGraph(infile);
        if (infile.eof())
            break;
        G.findShortestPath();
        G.displayAll();              // display shortest distance, path to cout


        NodeData from1("Woodland Park Zoo\r");
        NodeData to1("Green Lake Starbucks\r");
        NodeData from4("ccc\r");
        NodeData to4("bbb\r");
        G.removeEdge(from1, to1);
        G.removeEdge(from4, to4);
        cout << "After removing an edge 3 to 2" << endl;
        G.display(3, 2);

        NodeData from2("Aurora and 85th\r");
        NodeData to2("PCC\r");
        cout << "After removing an edge 1 to 5" << endl;
        G.removeEdge(from2, to2);
        G.display(1, 5);
        G.displayAll();

        NodeData from3("bbb\r");
        NodeData to3("aaa\r");
        NodeData from5("Green Lake Starbucks\r");
        NodeData to5("Aurora and 85th\r");
        cout << "After inserting an edge 2 to 1" << endl;
        G.insertEdge(from3, to3, 11);
        G.insertEdge(from5, to5, 11);
        G.display(2, 1);
        G.displayAll();
    }

}

// ------------------------------------ Test2() -----------------------------------------------

// Description

// Test2():         testing GraphL constrctor, buildGraph, deptFirstSearch, clear
//
// --------------------------------------------------------------------------------------------
void Test2(ifstream& infile)
{

    for (;;) {

        GraphL G;
        G.buildGraph(infile);
        if (infile.eof())
            break;
        G.displayGraph();
        G.depthFirstSearch();    // find and display depth-first ordering to cout
    }

}

int main() {

    ifstream infile1("data31.txt");
    if (!infile1) {
        cout << "File could not be opened." << endl;
        return 1;
    }
    Test1(infile1);

    // part 2
    ifstream infile2("data32.txt");
    if (!infile2) {
        cout << "File could not be opened." << endl;
        return 1;
    }
    Test2(infile2);

    return 0;
}