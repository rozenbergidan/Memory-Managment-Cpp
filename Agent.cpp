//
// Created by spl211 on 02/11/2020.
//

#include "Agent.h"
using namespace  std;
//---------------------------------------Agent---------------------------------------------------------------
Agent::Agent(Session& session) : session(session){}

//---------------------------------------ContactTracer---------------------------------------------------------------
ContactTracer::ContactTracer(Session &session) : Agent(session){};
ContactTracer * ContactTracer::clone() const{
    ContactTracer *output=new ContactTracer(session);
    return output;
}
const ContactTracer& ContactTracer::operator=(const ContactTracer& other){
    session = other.session;
    return *this;
}
void ContactTracer::act(){
    int node=session.dequeueInfected();
    if(node!=-1){
        Tree* tree=session.BFS(node);
        int nodeToDelete=tree->traceTree();
        session.isolateNode(nodeToDelete);
        delete tree;
    }

}
//---------------------------------------Virus---------------------------------------------------------------
Virus::Virus(int nodeInd, Session &session) : Agent(session), nodeInd(nodeInd),isActive(false) {}
Virus * Virus::clone() const{
    Virus *output=new Virus(nodeInd,session);
    return output;
}
void Virus::act() {
    std::printf("asd");////////////////////////////////////////////////////////////////////////////////////
    if(!isActive){
        isActive=true;
        session.enqueueInfected(nodeInd);
    }
    int nodeToInfect= session.getNeighborToInfect(nodeInd);
    if(nodeToInfect!=-1){
        Virus *newVirus=new Virus(nodeToInfect,session);
        session.addAgent(*newVirus);
        session.addInfected(nodeToInfect);
        delete newVirus;
    }

}


