//
// Created by spl211 on 02/11/2020.
//

#include <fstream>
#include "Session.h"

using namespace  std;
using json = nlohmann::json;

Session::Session(const std::string &path): g({}),treeType(), agents(){
    ifstream i(path);
    json j;
    j<<i;
    auto a=j["agents"];
    auto g=j["graph"];
    auto t=j["tree"];
    //addAgents
    for(auto elem: a){
        //if(elem[0]=='V') Agent agent=new Virus(elem[1],this)
        //else Agent agent=new ContactTracer(this);
        //addAgent(agent);
    }
    vector<vector<int>> v(g.size());
    for(auto elem: g){
        //v.push_back(elem);
    }
    //Graph graph(v);
    treeType=t;


};
void Session::simulate() {
    while(infectedQueue.size != 0){

    }
}
void Session::addAgent(const Agent &agent) {
    Agent *clone=agent.clone();
    agents.push_back(clone);
};
void Session::setGraph(const Graph& graph){
    g=graph;
};

Tree* Session::BFS(int node) {
    return g.BFS(*this,node);
}
