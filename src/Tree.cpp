//
// Created by spl211 on 02/11/2020.
//


#include "../include/Tree.h"
#include "../include/Session.h"

using namespace std;

Tree::Tree(int rootLabel) : node(rootLabel) {}

///========Rule of 3
Tree::Tree(const Tree &other) : children(), node(other.node) {
    for (int i = 0; i < other.children.size(); i = i + 1) {
        children.push_back(other.children[i]);
    }
}

Tree::~Tree() {
    for (int i = 0; i < children.size(); i = i + 1) {
        if (children[i]) delete children[i];
    }
}

//const Tree &Tree::operator=(const Tree &other) {
//    node = other.node;
//    int OTHER_NUM_OF_CHILDREN = other.children.size();
//    clear();
//    for (int i = 0; i < OTHER_NUM_OF_CHILDREN; i = i + 1){
//        Tree* toInsert = createTree(other.children[i]->node);
//        children.push_back(toInsert);
//    }
//    //children = other.children;//  TODO: (answer: NO!) check if the vector = operator is good for us... if not go through all the vector.
//}


void Tree::addChild(const Tree &child) {
    children.push_back(child.clone());
}

Tree* Tree::getLastChild(){
return children[children.size()-1];
}

int Tree::getNode() const {
    return node;
}

Tree *Tree::createTree(const Session &session, int rootLabel) {
    if (session.getTreeType() == TreeType::Cycle) return new CycleTree(rootLabel, session.getCycleCount());
    if (session.getTreeType() == TreeType::MaxRank) return new MaxRankTree(rootLabel);
    if (session.getTreeType() == TreeType::Root) return new RootTree(rootLabel);
}

//---------------------------------------CycleTree--------------------------------------------------------------
CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {}

///========Rule of 5
CycleTree::CycleTree(const CycleTree &other) : Tree(other), currCycle(other.currCycle) {}

const CycleTree &CycleTree::operator=(const CycleTree &other) {
    //children = other.children;
    node = other.node;
    currCycle = other.currCycle;

    int OTHER_NUM_OF_CHILDREN = other.children.size();
    clear();
    for (int i = 0; i < OTHER_NUM_OF_CHILDREN; i = i + 1){
        CycleTree* toInsert = nullptr;//new CycleTree(other.children[i]->getNode(),other.currCycle);
        toInsert = (CycleTree*)other.children[i];
        children.push_back(toInsert);
    }
    return *this;
}

CycleTree *CycleTree::clone() const {
    return new CycleTree(*this);
}

int CycleTree::traceTree() const {
    const CycleTree *outputTree = this;
    for (int i = 0; i < currCycle; i = i + 1) {
        if(!outputTree->children.empty()) outputTree = (CycleTree *) outputTree->children[0];
    }
    return outputTree->node;
}



//---------------------------------------MaxRankTree------------------------------------------------------------
MaxRankTree::MaxRankTree(const MaxRankTree &other) : Tree(other) {}

///========Rule of 5
MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}

MaxRankTree *MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}

int MaxRankTree::traceTree() const {
    const MaxRankTree *max = this;
    const MaxRankTree *maxInChildren = traceTreeRecursion(children.size());
    if (maxInChildren != nullptr) max = maxInChildren;
    return max->node;
}

const MaxRankTree *MaxRankTree::traceTreeRecursion(int currMax) const {
    const MaxRankTree *output = nullptr;
    if (children.size() > currMax) {
        currMax = children.size();
        output = this;
    }
    for (int i = 0; i < children.size(); i = i + 1) {
        const MaxRankTree *maxInChild = ((MaxRankTree *) children[i])->traceTreeRecursion(currMax);
        if (maxInChild != nullptr) {
            output = maxInChild;
            currMax = maxInChild->node;
        }
    }
    return output;
}



//---------------------------------------RootTree---------------------------------------------------------------
RootTree::RootTree(const RootTree &other) : Tree(other) {}

///========Rule of 3
RootTree::RootTree(int rootLabel) : Tree(rootLabel) {}

RootTree *RootTree::clone() const {
    return new RootTree(*this);
}

int RootTree::traceTree() const {
    return node;
}

