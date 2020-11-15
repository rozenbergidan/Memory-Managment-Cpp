//
// Created by spl211 on 02/11/2020.
//

#include <fstream>
#include <iostream>
#include "../include/Session.h"

using namespace std;
using json = nlohmann::json;

Session::Session(const std::string &path) : g({}), treeType(), agents(), cycleCount(0), infectedQueue() {
    fromJSON(path);

}

//Rule of 5
Session::~Session() {
    for (Agent* agent: agents){
        delete agent;
    }
}

Session:: Session(const Session &other):g(other.g), treeType(other.treeType), agents(), cycleCount(other.cycleCount), infectedQueue(other.infectedQueue){//copy constructor
    int newAgentsSize = other.agents.size();
    for (int i = 0; i < newAgentsSize; i = i + 1){
        addAgent(*other.agents[i]);
    }
}
const Session &Session::operator=(const Session &other){
    if(this != &other) {
        setGraph(other.g);
        treeType = other.treeType;
        for(Agent* agent: agents){
             delete agent;
        }
        agents.clear();
        int newAgentsSize = other.agents.size();
        for (int i = 0; i < newAgentsSize; i++) {
            addAgent(*other.agents[i]);
        }
    }
    return *this;
}


Session:: Session(Session &&other):g(std::move(other.g)), treeType(other.treeType), agents(), cycleCount(other.cycleCount), infectedQueue(other.infectedQueue){//move constructor
    int newAgentsSize = other.agents.size();
    for (int i = 0; i < newAgentsSize; i = i + 1){
        agents.push_back(other.agents[i]);
        other.agents[i] = nullptr;
    }
}

const Session &Session::operator=(Session &&other){
        g=std::move(other.g);
        treeType = other.treeType;
        for(Agent* agent: agents){
            delete agent;
        }
        agents.clear();
        int newAgentsSize = other.agents.size();
        for (int i = 0; i < newAgentsSize; i++) {
            addAgent(*other.agents[i]);
        }
    return *this;
}
//Rule of 5 end

void Session::fromJSON(const std::string &path) {
    ifstream jsonFile(path);
    json js;
    jsonFile >> js;


    //init Graph for g
    std::vector<std::vector<int>> matrix;
    for (std::vector<int> row:js["graph"]) {
        matrix.push_back(row);
    }
    Graph g1(matrix);
    setGraph(g1);


    //init treeType
    if (js["tree"] == "C") treeType = TreeType::Cycle;
    if (js["tree"] == "M") treeType = TreeType::MaxRank;
    if (js["tree"] == "R") treeType = TreeType::Root;

    //init Agents
    for (auto agent:js["agents"]) {
        if (agent[0] == "V") {
            Agent *virus = new Virus(agent[1]);
            addAgent(*virus);
            infectNode(agent[1]);
            delete virus;
        } else {
            Agent *contractTrace = new ContactTracer();
            addAgent(*contractTrace);
            delete contractTrace;
        }
    }
}

void Session::toJson() {
    ofstream jsonFile("./output.json");
    json js;

    js["graph"]=g.graphToJson();
    js["infected"]=g.infectedToJson();

    //std::cout<<js["graph"]<<endl;
    //std::cout<<js["infected"];
    jsonFile<<js;

}

void Session::simulate() {
    while (!isAllActiveOrIsolated()) {
        int agentsSize = agents.size();
        for (int i = 0; i < agentsSize; i = i + 1) {
            agents[i]->act(*this);
        }
        cycleCount = cycleCount + 1;
    }
    toJson();
    //TODO clear all DATA
}

void Session::addAgent(const Agent &agent) {
    Agent *clone = agent.clone();
    agents.push_back(clone);
}

void Session::setGraph(const Graph &graph) {
    g = graph;
}

Tree *Session::BFS(int node) {
    return g.BFS(*this, node);
}


int Session::getNeighborToInfect(int node) {return g.getNeighborToInfect(node);}


int Session::getCycleCount() const { return cycleCount; }


TreeType Session::getTreeType() const {
    return treeType;
}

void Session::isolateNode(int node) {
    g.isolateNode(node);
}
void Session::infectNode(int node) {
    g.infectNode(node);
}


void Session::enqueueInfected(int node) { infectedQueue.push(node); }

int Session::dequeueInfected() {
    int output = -1;
    if(!infectedQueue.empty()){
         output = infectedQueue.front();
        infectedQueue.pop();
    }
    return output;
}

bool Session::isAllActiveOrIsolated() {
    return (g.isAllActiveOrIsolated() && isAllVirusActive());
}

bool Session::isAllVirusActive() {
    for(auto agent: agents){
        if((dynamic_cast<Virus*>(agent) != nullptr) && !(((Virus*)agent)->getActive())) return false;
    }
    return true;
}
