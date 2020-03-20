/*
 * Tomomi Nakamura
 * file@ graphm.h
 * Graph & Shortest Path
 */

#include "nodedata.h"
#ifndef PROJECT3_GRAPHM_H
#define PROJECT3_GRAPHM_H

class GraphM {

public:

    //constructor
    GraphM();

    //destructor
    ~GraphM();

    //builds up graph node information and adjacency matrix of
    //edges between each node reading from a data file
    void buildGraph(ifstream &infile);

    //insert an edge into graph between two given nodes
    bool insertEdge(NodeData from, NodeData to, int edge);

    //remove an edge between two given node
    bool removeEdge(NodeData from, NodeData to);

    //find the shortest path between every node to every other
    // node in the graph, i.e., TableType T is updated with
    // shortest path information
    void findShortestPath();

    //uses couts to demonstrate that the algorithm works properly
    void displayAll();

    //uses couts to display the shortest distance with path info
    // between the fromNode to to
    void display(int from, int to);

private:

    struct TableType {

        bool visited;          // whether node has been visited
        int dist;              // shortest distance from source known so far
        int path;              // previous node in path of min dist

    };

    NodeData data[50];     // data for graph nodes
    int C[50][50];            // Cost array, the adjacency matrix
    int size;           // number of nodes in the graph
    TableType T[50][50];      // stores visited, distance, path
    void clearPath(); //clear T
};


#endif //PROJECT3_GRAPHM_H
