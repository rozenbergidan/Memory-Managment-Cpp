#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include "Tree.h"


class Graph {
public:
    Graph(std::vector<std::vector<int>> matrix);

    const Graph &operator=(const Graph &other); //copy assignment operator
    void infectNode(int nodeInd);

    bool isInfected(int nodeInd);

    void isolateNode(int node);

    //my code
    /////////////////////////////////////////////////////////////////////////
    Tree *BFS(const Session &session, int root);
    /////////////////////////////////////////////////////////////////////////
    std::vector<int> getNeighbors(int i); //return thr neighbors of i
private:
    std::vector<std::vector<int>> edges;
    bool *infectedTracer;
};

#endif