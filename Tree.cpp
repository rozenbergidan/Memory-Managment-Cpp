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

const Tree& Tree::operator=(const Tree &other) {
    node = other.node;
    children = other.children;//TODO: check if the vector = operator is good for us... if not go through all the vector.
}

int Tree::getNode() const {
    return node;
}

//---------------------------------------CycleTree--------------------------------------------------------------
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



























//std::vector<Tree*>* Tree::cloneChildren() const {
//    std::vector<Tree*>* output = new vector<Tree*>(children);
//    return output;
//}
//
//CycleTree* CycleTree::clone() const{
//    CycleTree* output = new CycleTree(this->getNode(),this->currCycle);
//    output->setChildren(this->cloneChildren());
//    return output;
//}
//
//MaxRankTree* MaxRankTree::clone() const{
//    MaxRankTree* output = new MaxRankTree(this->getNode());
//    output->setChildren(this->cloneChildren());
//    return output;
//}

//RootTree* RootTree::clone() const{
//    RootTree* output = new RootTree(this->getNode());
//    output->setChildren(this->cloneChildren());
//    return output;
//}



