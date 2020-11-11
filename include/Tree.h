#ifndef TREE_H_
#define TREE_H_

#include <vector>
//#include "../include/Session.h"

class Session;

//---------------------------------------Tree Abstract Class--------------------------------------------------------------
class Tree {
public:
    Tree(int rootLabel);

    void addChild(const Tree &child);

    ///Rule of 3
    Tree(const Tree &other); //copy constructor
    virtual ~Tree();//destructor
    virtual const Tree &operator=(const Tree &other);//copy assignment operator
    virtual Tree *clone() const = 0; //clone

    static Tree *createTree(const Session &session, int rootLabel);

    virtual int traceTree() const = 0;

    ///Out Functions
    Tree* getLastChild(); //TODO: check in office hours if i should return const reffernce.
    int getNode() const;
    void clear();// clear the children vector recurrcively;

protected:
    std::vector<Tree *> children;
    int node;

};

//---------------------------------CycleTree-------------------------------------------
class CycleTree : public Tree {
public:
    CycleTree(int rootLabel, int currCycle);

    virtual int traceTree() const;

    ///Rule of 3
    CycleTree(const CycleTree &other); //copy constructor
    virtual const CycleTree &operator=(const CycleTree &other);//copy assignment operator
    virtual CycleTree *clone() const;

private:
    int currCycle;
};

//---------------------------------MaxRankTree-------------------------------------------
class MaxRankTree : public Tree {
public:
    MaxRankTree(int rootLabel);

    virtual int traceTree() const;

    //Rule of 5
    MaxRankTree(const MaxRankTree &other); //copy constructor ------ TODO: check if nesesary to override the copy constructor
    //virtual ~MaxRankTree();// destructor------ TODO: check if nesesary to override the destrudtor
    //virtual const MaxRankTree& operator=(const MaxRankTree& other);//copy assignment operator ------ TODO: check if nesesary to override
    virtual MaxRankTree *clone() const;

private:
    ///Our Function
    const MaxRankTree *traceTreeRecursion(int currMax) const;// returns pointer to the node with most childrens that biger then currMax if exsist, and nullptr is not
};

//---------------------------------RootTree-------------------------------------------
class RootTree : public Tree {
public:
    RootTree(int rootLabel);

    virtual int traceTree() const;

    ///Rule of 3
    RootTree(const RootTree &other); //copy constructor ------ TODO: check if nesesary to override
    //virtual ~RootTree();// destructor------ TODO: check if nesesary to override the destrudtor
    //virtual const RootTree& operator=(const RootTree& other);//copy assignment operator ------ TODO: check if nesesary to override
    virtual RootTree *clone() const;
};
//--------------------------------------------------------------------------------------

#endif