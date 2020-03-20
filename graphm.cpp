/*
 * Tomomi Nakamura
 * file@ graphm.cpp
 * Graph & Shortest Path
 */


#include "nodedata.h"
#include "graphm.h"
#include <climits>
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>

using namespace std;
// ------------------------------------ constructor -----------------------------------------------

// Description

// constructor: constructor to initialize 'GraphM'
// preconditions:
// postconditions: the data member T is initialized to sets all dist to infinity, sets all visited
//                 to false, and sets all path to 0.
//

// --------------------------------------------------------------------------------------------
GraphM::GraphM() {
    TableType tt;
    tt.dist = INT_MAX;
    tt.path = 0;
    tt.visited = false;
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            T[i][j] = tt;
            //C[i][j] = INT_MAX;
        }
    }


}

GraphM::~GraphM() {

}

// ------------------------------------ buildGraph -----------------------------------------------

// Description

// buildGraph:      build graph from input file
// preconditions:   infile is ifstream to pass the input from textfile
// postconditions: builds up graph node information and adjacency matrix of edges between each node
////               reading from a data file
//

// --------------------------------------------------------------------------------------------
void GraphM::buildGraph(ifstream &infile) {
    string line;
    if (getline(infile, line))
    {
        size = stoi(line);
    }
    else {
        return;
    }
    for (int i = 1; i <= size; i++)
    {
        NodeData nd;
        nd.setData(infile);
        data[i] = nd;
    }

    int from, to, weight;
    while (from != 0 && getline(infile, line))
    {
        istringstream ss(line);

            ss >> from;
            ss >> to;
            ss >> weight;

            C[from][to] = weight;


    }


}

// ------------------------------------ insertEdge -----------------------------------------------

// Description

// insertEdge:      set an edge into graph between two given nodes
// preconditions:   from and to are vertexes where the new edge is inserted between
// postconditions:  insert a new edge in a adjacency matrix C where low is from and col is to
//

// --------------------------------------------------------------------------------------------
bool GraphM::insertEdge(NodeData from, NodeData to, int edge) {
    int low = 0, col = 0;
    for (int i = 1; i <= size; i++)
    {
        if (data[i] == from)
            low = i;
        if (data[i] == to)
            col = i;
        if (low != 0 && col != 0)
            break;
    }

    if (low == 0 || col == 0)
        return false;

    C[low][col] = edge;
    clearPath();
    findShortestPath();
    return true;
}

// ------------------------------------ removeEdge -----------------------------------------------

// Description

// removeEdge:      remove an edge into graph between two given nodes
// preconditions:   from and to are vertexes where the edge is removed between
// postconditions:  insert a edge of weight 0 in a adjacency matrix C where low is from and col is to
//

// --------------------------------------------------------------------------------------------
bool GraphM::removeEdge(NodeData from, NodeData to) {
    int low = 0, col = 0;
    for (int i = 1; i <= size; i++)
    {
        if (data[i] == from)
            low = i;
        if (data[i] == to)
            col = i;
        if (low != 0 && col != 0)
            break;
    }

    if (low == 0 || col == 0)
        return false;

    C[low][col] = 0;
    clearPath();
    findShortestPath();
    return true;
}

// ------------------------------------ findShortpath -----------------------------------------------

// Description

// findShortpath:   find the shortest path between every node to every other
// preconditions:   from and to are vertexes where the edge is removed between
// postconditions:  insert a edge of weight 0 in a adjacency matrix C where low is from and col is to
//

// --------------------------------------------------------------------------------------------
void GraphM::findShortestPath() {


    for (int source = 1; source <= size; source++) {

        T[source][source].dist = 0;
        //T[source][source].visited = true;

        // finds the shortest distance from source to all other nodes
        //int v, minEdge = 0; //v is a vertex


        for (int i = 1; i<= size; i++) {

            int v, minEdge = INT_MAX;
            //find v //not visited, shortest distance at this point
            for (int j = 1; j <= size; j++)
            {
                if (!T[source][j].visited && minEdge > T[source][j].dist)
                {
                    minEdge = T[source][j].dist;
                    v = j;
                }
            }
            //mark v visited
            T[source][v].visited = true;

            //for each w adjacent to v
            for (int w = 1; w <= size; w++)
            {
                //if w is not visited yet
                if (!T[source][w].visited) {
                    //change path
                    if (C[v][w] != 0 && T[source][w].dist > T[source][v].dist + C[v][w]) {
                        T[source][w].dist = T[source][v].dist + C[v][w];
                        T[source][w].path = v;
                    }
                }
            }

        }

    }
}

// ------------------------------------ diplayAll -----------------------------------------------

// Description

// displayAll:   display all shortest path between every nodes
// preconditions:
// postconditions:  using cout, print out all shortest paths
//

// --------------------------------------------------------------------------------------------
void GraphM::displayAll() {

    cout << "Description" << setw(25) << "From_node" << setw(15) << "To_node"
    << setw(15) << "Dijstra's" << setw(15) << "Path" << endl;

    for (int i = 1; i <= size; i++)
    {
        cout <<  data[i] << endl;

        for (int j = 1; j <= size; j++)
        {
            if (i != j)
            {
                cout << setw(35) << i << setw(15) << j << setw(15);

                if (T[i][j].dist == INT_MAX)
                    cout << "---";
                else
                    cout << T[i][j].dist;

                cout << setw(15);

                if (T[i][j].path > 0)
                {
                    string path = " " + to_string(T[i][j].path) + " " + to_string(j);
                    int curr = T[i][j].path;
                    while (curr != i) {
                        curr = T[i][curr].path;
                        path = " " + to_string(curr) + path;
                    }
                    cout << path;

                }

                cout << endl;

            }
        }
    }
    cout << endl;
    cout << endl;
    cout << endl;
}

// ------------------------------------ diplay -----------------------------------------------

// Description

// display:   display shortest path between from and to nodes
// preconditions:   from is a start node and to is a end node
// postconditions:  using cout, print out shortest paths between from and to
//

// --------------------------------------------------------------------------------------------
void GraphM::display(int from, int to) {

    cout << from << setw(10) << to << setw(10);

    if (T[from][to].dist == INT_MAX)
        cout << "---";
    else
        cout << T[from][to].dist << setw(10);

    NodeData place[size];
    int idx = 0;
    if (T[from][to].path > 0) {
        string path = " " + to_string(T[from][to].path) + " " + to_string(to);
        place[idx] = data[to];
        int curr = T[from][to].path;
        place[++idx] = data[curr];
        while (curr != from) {
            curr = T[from][curr].path;
            place[++idx] = data[curr];
            path = " " + to_string(curr) + path;
        }
        cout << path;
    }
    cout << endl;

    while (idx >= 0)
    {
        cout << place[idx]  << endl;
        idx--;
    }
    cout << endl;
    cout << endl;

}

// ------------------------------------ clearPath -----------------------------------------------

// Description

// clearPath:   clear all elemets of array T
// preconditions:
// postconditions:  set all th eelement of T to tt
//

// --------------------------------------------------------------------------------------------
void GraphM::clearPath() {
    TableType tt;
    tt.dist = INT_MAX;
    tt.path = 0;
    tt.visited = false;
    for (int i = 0; i < 50; i++)
    {
        for (int j = 0; j < 50; j++)
        {
            T[i][j] = tt;
            //C[i][j] = INT_MAX;
        }
    }
}

