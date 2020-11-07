#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session;

class Tree{
public:
    Tree(int rootLabel);
    void addChild(const Tree& child);

    //my code
    virtual ~Tree();
    virtual const Tree& operator=(const Tree& other);//copy assignment operator

    int getNode() const;
    void setNode(int n);


    static Tree* createTree(const Session& session, int rootLabel);
    virtual int traceTree()=0;

protected:
    std::vector<Tree*> children;
    int node;

};

class CycleTree: public Tree{
public:
    CycleTree(int rootLabel, int currCycle);
    virtual int traceTree();

    //my code
    CycleTree(const CycleTree &other); //copy constructor
    virtual ~CycleTree();// destructor
    virtual const CycleTree& operator=(const CycleTree& other);//copy assignment operator


private:
    int currCycle;
};

class MaxRankTree: public Tree{
public:
    MaxRankTree(int rootLabel);
    virtual int traceTree();

    //my code
    MaxRankTree(const MaxRankTree &other); //copy constructor
    virtual ~MaxRankTree();// destructor
    virtual const MaxRankTree& operator=(const MaxRankTree& other);//copy assignment operator
private:
    MaxRankTree* traceTreeRecursion(int currMax);// returns the node with most childrens that biger then currMax if exsist, and nullptr is not
};

class RootTree: public Tree{
public:
    RootTree(int rootLabel);
    virtual int traceTree();

    //my code
    RootTree(const RootTree &other); //copy constructor
    virtual ~RootTree();// destructor
    virtual const RootTree& operator=(const RootTree& other);//copy assignment operator


//    virtual RootTree* clone() const;
};

#endif