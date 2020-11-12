#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include "../include/Tree.h"


class Graph {
public:

    Graph(std::vector<std::vector<int>> matrix);



    void infectNode(int nodeInd);

    bool isInfected(int nodeInd);

    ///Rule of 5
    //virtual ~Graph(); //destructor
    Graph(const Graph &other); //copy constructor
    Graph(Graph &&other); //move constructor
    const Graph &operator=(const Graph &other); //copy assignment operator
    const Graph &operator=(Graph &&other); //move assignment operator



    ///Our Functions
    int getNeighborToInfect(int node); //return the neighbor of infected node which is not yet active

    void isolateNode(int node); //delete all node's edges

    bool isAllActiveOrIsolated(); //return True if all active nodes are isolated or if all nodes are Active

    std::vector<std::vector<int>> graphToJson(); //return the json format for the graph

    std::vector<int> infectedToJson(); //return the json format for infected nodes

    Tree* BFS(const Session& session, int root); //return the BFS Tree from root


private:

    std::vector<std::vector<int>> edges;

    ///Our data members
    int NUM_OF_NODES;
    std::vector<bool> infectedTracer;
};

#endif