#ifndef AGENT_H_
#define AGENT_H_

#include <vector>
#include "../include/Session.h"
//---------------------------------------Agent Abstract Class--------------------------------------------------------------
class Agent {
public:
    Agent();

    ///Rule of 3
    virtual ~Agent(); //destructor
    virtual Agent *clone() const = 0;
    //Agent(const Agent &other)=0; //copy constructor -DEFAULT
    //virtual const Agent& operator=(const Agent& other)=0; //copy assignment operator -DEFAULT

    virtual void act(Session &session) = 0;
};

//---------------------------------------ContactTracer--------------------------------------------------------------
class ContactTracer : public Agent {
public:
    ContactTracer();

    ///Rule of 5
    //~ContactTracer(); //destructor --INHERITED
    virtual ContactTracer *clone() const;
    //ContactTracer(const ContactTracer &other); //copy constructor -DEFAULT
    //virtual const ContactTracer &operator=(const ContactTracer &other); //copy assignment operator -DEFAULT

    virtual void act(Session &session);

};

//---------------------------------------Virus--------------------------------------------------------------
class Virus : public Agent {
public:
    Virus(int nodeInd);

    ///Rule of 5
//    ~Virus(); //destructor --INHERITED
//    Virus(const Virus &other); //copy constructor -DEFAULT
    virtual Virus *clone() const;
    //virtual const Virus& operator=(const Virus& other); //copy assignment operator -DEFAULT

    virtual void act(Session &session);

    bool getActive() const;

private:
    const int nodeInd;
    bool isActive; //to know if the node is infected
};

#endif