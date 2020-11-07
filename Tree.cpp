//
// Created by spl211 on 02/11/2020.
//


#include "Tree.h"
using namespace std;

Tree::Tree(int rootLabel) : node(rootLabel){}

void Tree::addChild(const Tree &child) {
    //children.push_back((Tree*)&child);
}
int Tree::getNode() const {
    return node;
}


Tree::~Tree(){
    for(int i = 0; i < children.size(); i = i + 1){
        if(children[i]) delete children[i];
    }
}
//---------------------------------------CycleTree--------------------------------------------------------------
const CycleTree& CycleTree::operator=(const CycleTree &other) {
    children = other.children;
    setNode(other.getNode());
    currCycle = other.currCycle;
    return *this;

}

int CycleTree::traceTree() {
    CycleTree* outputTree = this;
    for(int i = 0 ; i <= currCycle; i = i + 1){
        outputTree = (CycleTree*)outputTree->children[0];
    }
}
//---------------------------------------MaxRankTree------------------------------------------------------------

int MaxRankTree::traceTree() {
    MaxRankTree* max = this;
    MaxRankTree* maxInchilds = traceTreeRecursion(children.size());
    if(maxInchilds != nullptr) max = maxInchilds;
    return max->node;
}

MaxRankTree* MaxRankTree::traceTreeRecursion(int currMax) {
    MaxRankTree* output = nullptr;
    if(children.size()>currMax) {
        currMax = children.size();
        output = this;
    }
    for(int i = 0; i < children.size();  i = i + 1){
        MaxRankTree* maxInChild = ((MaxRankTree*)children[i])->traceTreeRecursion(currMax);
        if (maxInChild != nullptr){
            output = maxInChild;
            currMax = maxInChild->node;
        }
    }
    return output;
}
//---------------------------------------RootTree---------------------------------------------------------------
int RootTree::traceTree() {
    return getNode();
}




























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



