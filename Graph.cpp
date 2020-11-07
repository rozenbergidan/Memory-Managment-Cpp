//
// Created by spl211 on 02/11/2020.
//

#include <queue>
#include "Graph.h"
#include "Tree.h"
using namespace std;
class Tree;
class Session;
Graph::Graph(vector <vector<int>> matrix) :edges(matrix){};

//TODO complete BFS
Tree* Graph ::BFS(const Session& session, int root) { //if you use this func its up to you to delete the tree!!
    queue<Tree*> nodeQueue;
    bool isViseted [edges.size()];
    for (int i = 0; i < edges.size(); i = i + 1){
        isViseted[i] = false;
    }
    isViseted[root] = true;
    Tree* BFStree = Tree::createTree(session, root);
    nodeQueue.push(BFStree);
    while (nodeQueue.size() != 0){
        Tree* tree = nodeQueue.front();
        nodeQueue.pop();
        for (int i = 0; i < edges.size();i = i + 1){
            if(edges[tree->getNode()][i] == 1 & isViseted[i] == false){
                Tree* node = Tree::createTree(session,i);
                nodeQueue.push(node);
                tree->addChild(*node);
                isViseted[i] = true;
            }
        }
        if(tree->getNode() != root) delete tree;
    }


    return BFStree;
}