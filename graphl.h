/*
 * Tomomi Nakamura
 * file@ graphl.h
 * Graph & Shortest Path
 */

#include "nodedata.h"
#include <queue>
#ifndef PROJECT3_GRAPHL_H
#define PROJECT3_GRAPHL_H

class GraphL{

public:
    //constructor
    GraphL();
    //destructor
    ~GraphL();

    //builds up graph node information and adjacency list of edges
    // between each node reading from a data file.
    void buildGraph(ifstream& infile);

    //Displays each node information and edge in the graph
    void displayGraph();

    //Makes a depth-first search and displays each node in depth-first order
    void depthFirstSearch();

    void clear();   // clear all edges
private:
    struct EdgeNode;      // forward reference for the compiler

    struct GraphNode {    // structs used for simplicity, use classes if desired

        EdgeNode* edgeHead; // head of the list of edges

        NodeData* data;     // data information about each node

        bool visited;

    };

    struct EdgeNode {

        int adjGraphNode;  // subscript of the adjacent graph node

        EdgeNode* nextEdge;

    };

    struct Edge {

        int from;  // subscript of the adjacent graph node
        int to;



    };

    struct CompareHeight {
        bool operator()(Edge const& p1, Edge const& p2)
        {
            // return "true" if "p1" is ordered
            // before "p2", for example:
            return p1.to > p2.to;
        }
    };

    int size; // number of total nodes
    GraphNode graph[50];
};


#endif //PROJECT3_GRAPHL_H
