#ifndef TREE_H_
#define TREE_H_

#include <vector>
//my code
/////////////////
#include "Graph.h"
///////////////
class Session;

class Tree{
public:
    Tree(int rootLabel);
    void addChild(const Tree& child);

    //my code
    //////////////////////////////////////////////////
    virtual ~Tree();//destructor
    virtual const Tree& operator=(const Tree& other);//copy assignment operator
    virtual Tree* clone() const = 0;

    int getNode() const;
    /////////////////////////////////////////////////
    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree() const =0;

protected:
    std::vector<Tree*> children;
    int node;

};
//---------------------------------CycleTree-------------------------------------------
class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree() const;

    //my code
    CycleTree(const CycleTree &other); //copy constructor
    virtual ~CycleTree();// destructor
    virtual const CycleTree& operator=(const CycleTree& other);//copy assignment operator
    virtual CycleTree* clone() const;

private:
    int currCycle;
};
//-------------------------------------------------------------------------------------
//---------------------------------MaxRankTree-------------------------------------------
class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree() const;

    //my code
    MaxRankTree(const MaxRankTree &other); //copy constructor
    virtual ~MaxRankTree();// destructor
    virtual const MaxRankTree& operator=(const MaxRankTree& other);//copy assignment operator
    virtual MaxRankTree* clone() const;
private:
    const MaxRankTree* traceTreeRecursion(int currMax) const;// returns pointer to the node with most childrens that biger then currMax if exsist, and nullptr is not
};
//---------------------------------RootTree-------------------------------------------
class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree() const;

    //my code
    RootTree(const RootTree &other); //copy constructor
    virtual ~RootTree();// destructor
    virtual const RootTree& operator=(const RootTree& other);//copy assignment operator


    virtual RootTree* clone() const;
};
//--------------------------------------------------------------------------------------

#endif