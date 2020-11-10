//
// Created by spl211 on 02/11/2020.
//

#include "../include/Agent.h"

using namespace std;

//---------------------------------------Agent---------------------------------------------------------------
Agent::Agent(Session &session) : session(session) {}
///========Rule of 3

//---------------------------------------ContactTracer---------------------------------------------------------------
ContactTracer::ContactTracer(Session &session) : Agent(session) {};

///========Rule of 5
ContactTracer *ContactTracer::clone() const {
    ContactTracer *output = new ContactTracer(session);
    return output;
}

const ContactTracer &ContactTracer::operator=(const ContactTracer &other) {
    session = other.session;
    return *this;
}

void ContactTracer::act() {
    int node = session.dequeueInfected();
    if (node != -1) {
        Tree *tree = session.BFS(node);
        int nodeToDelete = tree->traceTree();
        session.isolateNode(nodeToDelete);
        delete tree;
    }

}

//---------------------------------------Virus---------------------------------------------------------------
Virus::Virus(int nodeInd, Session &session) : Agent(session), nodeInd(nodeInd), isActive(false) {}

///========Rule of 5
Virus *Virus::clone() const {
    Virus *output = new Virus(nodeInd, session);
    return output;
}

void Virus::act() {
    if (!isActive) {
        isActive = true;
        session.enqueueInfected(nodeInd);
        session.infectNode(nodeInd);
    }
    int nodeToInfect = session.getNeighborToInfect(nodeInd);
    if (nodeToInfect != -1) {
        Virus *newVirus = new Virus(nodeToInfect, session);
        session.addAgent(*newVirus);
        session.infectNode(nodeToInfect);
        delete newVirus;
    }

}


