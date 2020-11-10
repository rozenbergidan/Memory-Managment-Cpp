#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "../include/Session.h"
//---------------------------------------Agent Abstract Class--------------------------------------------------------------
class Agent {
public:
    Agent(Session &session);

    ///Rule of 3
    virtual Agent *clone() const = 0;
    //virtual const Agent& operator=(const Agent& other)=0;

    virtual void act() = 0;



protected:
    Session &session;
};

//---------------------------------------ContactTracer--------------------------------------------------------------
class ContactTracer : public Agent {
public:
    ContactTracer(Session &session);

    ///Rule of 5
    //virtual ~ContactTracer();
    virtual ContactTracer *clone() const;
    virtual const ContactTracer &operator=(const ContactTracer &other);

    virtual void act();




};

//---------------------------------------Virus--------------------------------------------------------------
class Virus : public Agent {
public:
    Virus(int nodeInd, Session &session);

    ///Rule of 5
    //virtual ~Virus();
    virtual Virus *clone() const;
    //virtual const Virus& operator=(const Virus& other);

    virtual void act();



    ///Our function
    const int getNodeInd();

private:
    const int nodeInd;
    ///Our data member
    bool isActive; //to know if the node is infected
};

#endif