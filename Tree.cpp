//
// Created by spl211 on 02/11/2020.
//


#include "Tree.h"
using namespace std;

Tree::Tree(int rootLabel) : node(rootLabel){}

void Tree::addChild(const Tree &child) {
    children.push_back(child.clone());
}


Tree::~Tree(){
    for(int i = 0; i < children.size(); i = i + 1){
        if(children[i]) delete children[i];
    }
}

//---------------------------------------CycleTree--------------------------------------------------------------
CycleTree::CycleTree(int rootLabel, int currCycle): Tree(rootLabel), currCycle(currCycle){}

const CycleTree& CycleTree::operator=(const CycleTree &other) {
    children = other.children;
    node = other.node;
    currCycle = other.currCycle;
    return *this;

}

int CycleTree::traceTree() const{
    const CycleTree* outputTree = this;
    for(int i = 0 ; i <= currCycle; i = i + 1){
        outputTree = (CycleTree*)outputTree->children[0];
    }
    return outputTree->node;
}

CycleTree* CycleTree::clone() const {
    return new CycleTree(*this);
}
//---------------------------------------MaxRankTree------------------------------------------------------------

int MaxRankTree::traceTree() const{
    const MaxRankTree* max = this;
    const MaxRankTree* maxInChildren = traceTreeRecursion(children.size());
    if(maxInChildren != nullptr) max = maxInChildren;
    return max->node;
}

const MaxRankTree* MaxRankTree::traceTreeRecursion(int currMax) const{
    const MaxRankTree* output = nullptr;
    if(children.size()>currMax) {
        currMax = children.size();
        output = this;
    }
    for(int i = 0; i < children.size();  i = i + 1){
        const MaxRankTree* maxInChild = ((MaxRankTree*)children[i])->traceTreeRecursion(currMax);
        if (maxInChild != nullptr){
            output = maxInChild;
            currMax = maxInChild->node;
        }
    }
    return output;
}
MaxRankTree* MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}
//---------------------------------------RootTree---------------------------------------------------------------
int RootTree::traceTree() const{
    return node;
}
RootTree* RootTree::clone() const {
    return new RootTree(*this);
}
//--------------------------------------------------------------------------------------------------------------































