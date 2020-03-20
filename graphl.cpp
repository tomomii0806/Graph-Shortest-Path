/*
 * Tomomi Nakamura
 * file@ graphl.cpp
 * Graph & Shortest Path
 */

#include <iostream>
#include <sstream>
#include "graphl.h"
#include "nodedata.h"
#include <stack>
#include <queue>
#include <vector>
#include <iomanip>
using namespace std;

GraphL::GraphL() {
    for (int i = 1; i <= size; i++)
    {
        graph[i].visited = false;
        //graph[i].edgeHead->adjGraphNode = 0;
    }
    size = 0;
}

GraphL::~GraphL() {
    if (size != 0)
    {
        for (int i = 1; i <= size; i++)
        {
            EdgeNode* curr = graph[i].edgeHead;
            while (curr != NULL)
            {
                delete curr;
                curr->adjGraphNode = 0;
                curr = curr->nextEdge;
            }
            delete graph[i].data;
            graph[i].data = NULL;

        }
    }


}

// ------------------------------------ buildGraph -----------------------------------------------

// Description

// buildGraph:      build graph from input file
// preconditions:   infile is ifstream to pass the input from textfile
// postconditions: builds up graph node information and adjacency matrix of edges between each node
////               reading from a data file
//

// --------------------------------------------------------------------------------------------
void GraphL::buildGraph(ifstream &infile) {

    string line;
    if (getline(infile, line))
    {
        size = stoi(line);
    }
    else {
        return;
    }


    clear();

    for (int i = 1; i <= size; i++)
    {
        NodeData* nd = new NodeData();
        nd->setData(infile);

        graph[i].data = nd;
    }

    /*for (int i = 1; i <= size; i++)
    {
        graph[i].visited = false;
        graph[i].edgeHead->adjGraphNode = 0;
    }*/

    int from, to, prevFrom;
    bool sameNode;
    //stack<Edge> st;
    vector<Edge> vec;
    priority_queue<int> pq;
    //priority_queue<Edge, vector<Edge>, CompareHeight>* arr;


    /*while (!pq.empty())
    {
        cout << pq.top().from << ", " << pq.top().to << endl;
        pq.pop();
    }*/

    int numOfEdge = 0;
    while (from != 0 && getline(infile, line))
    {
        istringstream ss(line);

        //Edge edge;
        ss >> from;
        ss >> to;
        //from = edge.from;
        if (from == prevFrom)
        {
            pq.push(to);
        }
        else {

            while (!pq.empty())
            {
                Edge e;
                e.from = prevFrom;
                e.to = pq.top();
                vec.push_back(e);
                pq.pop();
                numOfEdge++;
            }
            prevFrom = from;
            pq.push(to);
        }
    }
   // pq.pop(); // pop 0,0
    /*while (!pq.empty())
    {
        cout << pq.top().from << ", " << pq.top().to << endl;
        pq.pop();
    }*/
    /*EdgeNode* head[size + 1];
    for (int i = 1; i <= size; i++)
    {
        graph[i].edgeHead = new EdgeNode;
    }
    for (int i = 1; i <= size; i++)
    {
        head[i] = graph[i].edgeHead;
    }

    while (!pq.empty())
    {
        from = pq.top().from;
        to = pq.top().to;

        graph[from].edgeHead = new EdgeNode();
        graph[from].edgeHead->adjGraphNode = to;
        graph[from].edgeHead = graph[from].edgeHead->nextEdge;

        pq.pop();
        //EdgeNode* curr = graph[from].edgeHead;

    }
    for (int i = 1; i <= size; i++)
    {
        graph[i].edgeHead = head[i];
    }*/
    numOfEdge -= 1;
    int n = 0;
    while (0 <= numOfEdge)
    {
        prevFrom = vec.at(numOfEdge).from;
        graph[prevFrom].edgeHead = new EdgeNode();
        graph[prevFrom].edgeHead->adjGraphNode = 0;

        EdgeNode* curr = graph[prevFrom].edgeHead;
        //EdgeNode* curr = newEdge;

        while (numOfEdge >= 0 && prevFrom == vec.at(numOfEdge).from){
            from = vec.at(numOfEdge).from;
            to = vec.at(numOfEdge).to;
            //EdgeNode* e = new EdgeNode();
            //e->adjGraphNode = to;
            curr->adjGraphNode = to;
            //curr = e;
            curr->nextEdge = new EdgeNode();
            curr = curr->nextEdge;
            prevFrom = from;
            //st.pop();
            //n++;
            numOfEdge--;
        }
    }

}

// ------------------------------------ diplayGraph -----------------------------------------------

// Description

// displayGrah:   display all edges from all nodes
// preconditions:
// postconditions:  using cout, print out all paths from each node
//

// --------------------------------------------------------------------------------------------
void GraphL::displayGraph() {

    /*EdgeNode* head[size + 1];
    for (int i = 1; i <= size; i++)
    {
        head[i] = graph[i].edgeHead;
    }*/
    cout << "Displaying Graph" << endl;

    for (int n = 1; n <= size; n++)
    {
        cout << "Node " << n << "  " << *graph[n].data << endl;
        EdgeNode* curr = graph[n].edgeHead;
        while (curr != NULL && curr->adjGraphNode != 0)
        {
            cout << "Edge " << n << " " << curr->adjGraphNode << endl;
            curr = curr->nextEdge;
        }
    }
    cout << endl;

    /*for (int i = 1; i <= size; i++)
    {
        graph[i].edgeHead = head[i];
    }*/
}

// ------------------------------------ depthFirstSearch -----------------------------------------------

// Description

// depthFirstSearch:   perform DFS and get an order
// preconditions:
// postconditions:
//

// --------------------------------------------------------------------------------------------
void GraphL::depthFirstSearch() {
    stack<int> st;
    queue<int> q;
    int node = 1;
    do
    {

        if (!graph[node].visited)
        {
            st.push(node);
            q.push(node);
            graph[node].visited =  true;
        }

        if (graph[node].edgeHead != NULL && graph[node].edgeHead->adjGraphNode != 0)
        {
            int prev = node;
            node = graph[node].edgeHead->adjGraphNode;
            graph[prev].edgeHead = graph[prev].edgeHead->nextEdge;
        }
        else {

            if (!st.empty())
            {
                st.pop();

                node = !st.empty() ? st.top() : node;
            }
            else {
                for (int i = 1; i <= size; i++)
                {
                    if (!graph[i].visited)
                    {
                        node = i;
                        //st.push(node);
                        //q.push(node);
                        break;
                    }
                }
            }
        }


    }while (q.size() < size);

    cout << "DFS: " ;
    while (!q.empty())
    {
        cout << q.front() << ", ";
        q.pop();
    }

    cout << endl;
    cout << endl;
}

// ------------------------------------ clear -----------------------------------------------

// Description

// clear:   clear all edges
// preconditions:
// postconditions:  set all edges to NULL
//

// --------------------------------------------------------------------------------------------
void GraphL::clear()    {
    for (int i = 1; i <= size; i++)
    {
        graph[i].edgeHead = NULL;

        //curr = NULL;

        //graph[i].data = NULL;

    }
}