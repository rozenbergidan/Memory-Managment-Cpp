#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "Session.h"

class Agent{
public:
    Agent(Session& session);

    virtual void act()=0;
    virtual Agent* clone() const =0;
    //virtual const Agent& operator=(const Agent& other)=0;

protected:
    Session& session;
};

class ContactTracer: public Agent{
public:
    ContactTracer(Session& session);
    //virtual ~ContactTracer();
    virtual void act();
    virtual ContactTracer* clone() const;
    virtual const ContactTracer& operator=(const ContactTracer& other);
};


class Virus: public Agent{
public:
    Virus(int nodeInd, Session &session);
    //virtual ~Virus();
    virtual void act();
    virtual Virus* clone() const;
    virtual const Virus& operator=(const Virus& other);

private:
    const int nodeInd;
    bool isActive; //to know if the node is infected
};

#endif