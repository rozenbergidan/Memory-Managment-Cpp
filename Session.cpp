//
// Created by spl211 on 02/11/2020.
//

#include "Session.h"
using namespace  std;

Session::Session(const std::string &path): g(),treeType(), agents(){
    //read json file from path
    //after reading json file
    //addAgents
    //addGraph

};

void Session::addAgent(const Agent &agent) {
    agents.push_back(&agent);
};
void Session::setGraph(const Graph& graph){
    g=graph;
};
