#ifndef TREE_H_
#define TREE_H_

#include <vector>

class Session;

//---------------------------------------Tree Abstract Class--------------------------------------------------------------
class Tree {
public:
    Tree(int rootLabel);

    void addChild(const Tree &child);

    //Rule of 5
    virtual ~Tree();//destructor
    Tree(const Tree &other); //copy constructor
    Tree(Tree &&other); //move constructor
    Tree &operator=(const Tree &other);//copy assignment operator
    Tree &operator=(Tree &&other);//move assignment operator


    virtual Tree *clone() const = 0; //clone

    static Tree *createTree(const Session &session, int rootLabel);

    virtual int traceTree() const = 0;

    Tree* getLastChild();
    int getNode() const;
    void clear();// clear the children vector recurrcively;
    int getNumOfChild() const;
protected:
    std::vector<Tree *> children;
    int node;

};

//---------------------------------CycleTree-------------------------------------------
class CycleTree : public Tree {
public:
    CycleTree(int rootLabel, int currCycle);

    ///Rule of 5
    // destructor - inherited from tree
    CycleTree(const CycleTree &other); //copy constructor
    CycleTree(CycleTree &&other); //move constructor
    CycleTree &operator=(const CycleTree &other);//copy assignment operator
    CycleTree &operator=(CycleTree &&other);//move assignment operator
    //Rule of 5 end.

    virtual CycleTree *clone() const;
    virtual int traceTree() const;

private:
    int currCycle;
};

//---------------------------------MaxRankTree-------------------------------------------
class MaxRankTree : public Tree {
public:
    MaxRankTree(int rootLabel);

    ///Rule of 5
    // destructor - inherited from tree
    MaxRankTree(const MaxRankTree &other); //copy constructor
    MaxRankTree(MaxRankTree &&other); //move constructor
    MaxRankTree &operator=(const MaxRankTree &other);//copy assignment operator
    MaxRankTree &operator=(MaxRankTree &&other);//move assignment operator
    //Rule of 5 end.

    virtual MaxRankTree *clone() const;
    virtual int traceTree() const;
};

//---------------------------------RootTree-------------------------------------------
class RootTree : public Tree {
public:
    RootTree(int rootLabel);

    ///Rule of 5
    //virtual ~RootTree();// destructor - inherent from Tree
    RootTree(const RootTree &other); //copy constructor
    RootTree(RootTree &&other);//move constructor
    RootTree& operator=(const RootTree& other);//copy assignment operator
    RootTree& operator=(RootTree&& other);//move assignment operator
    //Rule of 5 end.

    virtual RootTree *clone() const;
    virtual int traceTree() const;
};
//--------------------------------------------------------------------------------------

#endif