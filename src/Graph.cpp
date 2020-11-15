//
// Created by spl211 on 02/11/2020.
//

#include <queue>
#include "../include/Graph.h"

using namespace std;


Graph::Graph(vector <vector<int>> matrix) :edges(matrix), NUM_OF_NODES(edges.size()),infectedTracer({}){

    for(int i = 0; i < NUM_OF_NODES; i = i + 1){
        infectedTracer.push_back(false);
    }
}

///========Rule of 5
//const Graph &Graph::operator=(const Graph &other) {
//    edges = other.edges;
//    infectedTracer = other.infectedTracer;
//    NUM_OF_NODES = other.NUM_OF_NODES;
//    return *this;
//}
//
//Graph::Graph(const Graph &other) :edges(other.edges), NUM_OF_NODES(other.NUM_OF_NODES),infectedTracer(other.infectedTracer){}
//
//Graph::Graph(Graph &&other) : edges(std::move(other.edges)/*TODO*/), NUM_OF_NODES(other.NUM_OF_NODES), infectedTracer((std::move(other.infectedTracer))){}
//
//const Graph &Graph::operator=(Graph &&other) {
//    edges = std::move(other.edges);/*TODO*/
//    infectedTracer = other.infectedTracer;
//    NUM_OF_NODES = other.NUM_OF_NODES;
//    return *this;
//}

Tree *Graph::BFS(const Session &session, int root) { //if you use this func its up to you to delete the tree!!
    queue<Tree *> nodeQueue;
    bool isVisited[NUM_OF_NODES];
    for (int i = 0; i < NUM_OF_NODES; i = i + 1) {
        isVisited[i] = false;
    }
    isVisited[root] = true;
    Tree *BFStree = Tree::createTree(session, root);
    nodeQueue.push(BFStree);
    while (nodeQueue.size() != 0) {
        Tree *tree = nodeQueue.front();
        nodeQueue.pop();
        for (int i = 0; i < NUM_OF_NODES; i = i + 1) {
            if ((edges[tree->getNode()][i] == 1) & !isVisited[i] ) {
                Tree *node = Tree::createTree(session, i);
                tree->addChild(*node);
                nodeQueue.push(tree->getLastChild());

                isVisited[i] = true;
                if (node->getNode() != root) delete node;
            }
        }

    }


    return BFStree;
}


void Graph::isolateNode(int node) {
    for (int i = 0; i < NUM_OF_NODES; i = i + 1) {
        edges[node][i] = 0;
        edges[i][node] = 0;
    }
}

void Graph::infectNode(int nodeInd){
    if((0<= nodeInd) & (nodeInd < NUM_OF_NODES)) infectedTracer[nodeInd] = true;
}

bool Graph::isInfected(int nodeInd){
    if((0<= nodeInd) & (nodeInd < NUM_OF_NODES)) return infectedTracer[nodeInd];
    return false; // if nodeInd is not in the graph, return false.
}

int Graph::getNeighborToInfect(int node) {// return the nodeInd to infect, -1 if no one exist
    for(int i = 0; i < NUM_OF_NODES; i = i + 1){
        if((edges[node][i] == 1) & !isInfected(i)) return i;
    }
    return -1;
}

bool Graph::isAllActiveOrIsolated() {
    bool isAllHealthy = true;
    for (int i = 0; i < NUM_OF_NODES; i++) {
        if (infectedTracer[i] & (getNeighborToInfect(i) != -1)) return false;
        if (infectedTracer[i]) isAllHealthy = false;
    }
    if(isAllHealthy) return false;
    return true;
}

std::vector<std::vector<int>> Graph::graphToJson() {
    return edges;
}

std::vector<int> Graph::infectedToJson() {
    std::vector<int> output({});
    for(int i=0; i<NUM_OF_NODES;i++){
        if(isInfected(i)) output.push_back(i);
    }
    return output;
}