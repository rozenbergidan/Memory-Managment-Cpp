#ifndef SESSION_H_
#define SESSION_H_

#include <vector>
#include <string>
#include "Graph.h"
#include "Agent.h"//////////////////////////////////////////////////////////
#include "json.hpp"

class Agent;

enum TreeType{
  Cycle,
  MaxRank,
  Root
};

class Session{
public:
    Session(const std::string& path);
    
    void simulate();
    void addAgent(const Agent& agent);
    void setGraph(const Graph& graph);
    
    void enqueueInfected(int);
    int dequeueInfected(); //return -1 if empty
    TreeType getTreeType() const;

    ///our code
    Tree* BFS(int node); //return the BFS tree from g, reducing coupling
    void isolateNode(int node); //isolate the node from its neighbors
    int infect(int node);// return the node neighbor to infect, return -1 is all neighbors are infected
private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;

    //my code
    //Queue infectedQueue;
    //int verticesNum;
    //
};

#endif