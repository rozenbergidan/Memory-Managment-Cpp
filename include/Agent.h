#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "../include/Session.h"
//---------------------------------------Agent Abstract Class--------------------------------------------------------------
class Agent {
public:
    Agent();

    ///Rule of 3
    virtual ~Agent()=0; //destructor
    virtual Agent *clone() const = 0;
    //Agent(const Agent &other)=0; //copy constructor
    //virtual const Agent& operator=(const Agent& other)=0; //copy assignment operator

    virtual void act(Session &session) = 0;
};

//---------------------------------------ContactTracer--------------------------------------------------------------
class ContactTracer : public Agent {
public:
    ContactTracer();

    ///Rule of 5
    //virtual ~ContactTracer(); //destructor
    virtual ContactTracer *clone() const;
    //ContactTracer(const ContactTracer &other); //copy constructor
    //virtual const ContactTracer &operator=(const ContactTracer &other); //copy assignment operator

    virtual void act(Session &session);

};

//---------------------------------------Virus--------------------------------------------------------------
class Virus : public Agent {
public:
    Virus(int nodeInd);

    ///Rule of 5
    //Virtual ~Virus(); //destructor
    //Virus(const Virus &other); //copy constructor
    virtual Virus *clone() const;
    //virtual const Virus& operator=(const Virus& other); //copy assignment operator

    virtual void act(Session &session);

private:
    const int nodeInd;
    ///Our data member
    bool isActive; //to know if the node is infected
};

#endif