//
// Created by spl211 on 02/11/2020.
//

#include <queue>
#include "Graph.h"

using namespace std;

Graph::Graph(vector<vector<int>> matrix) : edges(matrix) {};

const Graph &Graph::operator=(const Graph &other) {
    edges = other.edges;
}

//TODO complete BFS
Tree *Graph::BFS(const Session &session, int root) { //if you use this func its up to you to delete the tree!!
    queue<Tree *> nodeQueue;
    bool isVisited[edges.size()];
    for (int i = 0; i < edges.size(); i = i + 1) {
        isVisited[i] = false;
    }
    isVisited[root] = true;
    Tree *BFStree = Tree::createTree(session, root);
    nodeQueue.push(BFStree);
    while (nodeQueue.size() != 0) {
        Tree *tree = nodeQueue.front();
        nodeQueue.pop();
        for (int i = 0; i < edges.size(); i = i + 1) {
            if (edges[tree->getNode()][i] == 1 & isVisited[i] == false) {
                Tree *node = Tree::createTree(session, i);
                nodeQueue.push(node);
                tree->addChild(*node);
                isVisited[i] = true;
            }
        }
        if (tree->getNode() != root) delete tree;
    }


    return BFStree;
}

std::vector<int> Graph::getNeighbors(int i) {
    vector<int> output;
    for (int j = 0; j < edges[i].size(); j++) {
        if (edges[i][j] == 1)output.push_back(j);
    }
    return output;
}

void Graph::isolateNode(int node) {
    for (int i = 0; i < edges.size(); i = i + 1) {
        edges[node][i] = 0;
        edges[i][node] = 0;
    }
}

