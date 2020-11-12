#ifndef SESSION_H_
#define SESSION_H_

#include "../include/json.hpp"
#include <vector>
#include <queue>
#include <string>
#include "../include/Graph.h"
#include "../include/Agent.h"


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

    //Rule of 5
    ~Session(); //destructor
    Session(const Session &other); //copy constructor
    Session(Session &&other); //move constructor
    const Session& operator=(const Session& other); //copy assignment operator
    const Session& operator=(const Session&& other); //move assignment operator

    void enqueueInfected(int);
    int dequeueInfected(); //return -1 if empty
    TreeType getTreeType() const;
    ///Our Functions
    Tree* BFS(int node); //return the BFS tree from g, reducing coupling

    void isolateNode(int node); //isolate the node from its neighbors, calls to graph::isolateNode

    int getNeighborToInfect(int node) ;// return the node neighbor to getNeighborToInfect, return -1 is all neighbors are infected

    bool isAllActiveOrIsolated(); //return True if all active nodes are isolated or if all nodes are Active

    int getCycleCount() const;

    void infectNode(int node); //make a node active, calls to graph::infectNode


private:
    Graph g;
    TreeType treeType;
    std::vector<Agent*> agents;


    /// Our Data members
    int cycleCount;
    std::queue<int> infectedQueue;

    ///our from/to JSon functions
    void fromJSON(const std::string &path); //read a json file from path, and build objects accordingly
    void toJson(); //write json file at "../output.json"

    //void clearAgents();
};

#endif