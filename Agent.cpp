//
// Created by spl211 on 02/11/2020.
//

#include "Agent.h"
using namespace  std;

Agent::Agent(Session& session) : session(session){};


ContactTracer::ContactTracer(Session &session) : Agent(session){};
ContactTracer * ContactTracer::clone() const{
    ContactTracer *output=new ContactTracer(session);
    return output;
};



Virus::Virus(int nodeInd, Session &session) : Agent(session), nodeInd(nodeInd) {};
Virus * Virus::clone() const{
    Virus *output=new Virus(nodeInd,session);
    return output;
};


