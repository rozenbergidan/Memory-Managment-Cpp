//
// Created by spl211 on 02/11/2020.
//
#include "../include/Tree.h"
#include "../include/Session.h"

using namespace std;

Tree::Tree(int rootLabel) : children(), node(rootLabel){}

///========Rule of 3
Tree::Tree(const Tree &other) : children(), node(other.node) {
    int other_number_of_Children=other.children.size();
    for (int i = 0; i < other_number_of_Children; i = i + 1) {
        children.push_back(other.children[i]->clone());
    }
}

Tree::Tree(Tree &&other):children(), node(other.node){
    int other_number_of_Children = other.children.size();
    for (int i = 0; i < other_number_of_Children; i = i + 1) {
        children.push_back(other.children[i]);
        other.children[i] = nullptr;
    }
}

Tree::~Tree() {
    int number_of_Children=children.size();
    for (int i = 0; i < number_of_Children; i = i + 1) {
        if (children[i]) delete children[i];
    }
}


const Tree &Tree::operator=(const Tree &other) {
    if (this != &other) {
        node = other.node;
        int other_number_of_Children = other.children.size();
        clear();//delete the children.
        for (int i = 0; i < other_number_of_Children; i = i + 1) {
            addChild(*other.children[i]);
        }
    }
    return *this;
}

const Tree& Tree::operator=(Tree &&other) {
        node = other.node;
        int other_number_of_Children = other.children.size();
        clear();//delete the children.
        for (int i = 0; i < other_number_of_Children; i = i + 1) {
            children.push_back(other.children[i]);
            other.children[i]=nullptr;
        }
    return *this;
}


void Tree:: clear(){
    int num_of_child = children.size();
    for(int i = 0; i < num_of_child; i = i + 1){
        delete children[i];
    }
    children.clear();
}
void Tree::addChild(const Tree &child) {
    children.push_back(child.clone());
}

Tree* Tree::getLastChild(){
return children[children.size()-1];
}

int Tree::getNode() const {
    return node;
}
int Tree::getNumOfChild() const { return children.size();}

Tree *Tree::createTree(const Session &session, int rootLabel) {
    if (session.getTreeType() == TreeType::Cycle) return new CycleTree(rootLabel, session.getCycleCount());
    else if (session.getTreeType() == TreeType::MaxRank) return new MaxRankTree(rootLabel);
    else  return new RootTree(rootLabel);
}

//---------------------------------------CycleTree--------------------------------------------------------------
CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {}

///========Rule of 5
CycleTree::CycleTree(const CycleTree &other) : Tree(other), currCycle(other.currCycle) {}

const CycleTree &CycleTree::operator=(const CycleTree &other) {
    currCycle = other.currCycle;
    Tree::operator=(other);
    return *this;
}

const CycleTree &CycleTree::operator=(CycleTree &&other) {
    currCycle = other.currCycle;
    Tree::operator=(other);
//    node = other.node;
//    int other_number_of_Children = other.children.size();
//    clear();//delete the children.
//    for (int i = 0; i < other_number_of_Children; i = i + 1) {
//        children.push_back(other.children[i]);
//        other.children[i]=nullptr;
//    }
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

//========Rule of 5
MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}

MaxRankTree *MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}

int MaxRankTree::traceTree() const {
//    const MaxRankTree *max = this;
//    const MaxRankTree *maxInChildren = traceTreeRecursion(children.size());
//    if (maxInChildren != nullptr) max = maxInChildren;
//    return max->node;
    MaxRankTree* firstTree = clone();
    std::queue<MaxRankTree*> TreeTravel;
    TreeTravel.push(firstTree);
    int maxRank = children.size();
    int maxNode = node;
    while(!TreeTravel.empty()){
        MaxRankTree* tree = TreeTravel.front();
        TreeTravel.pop();
        if(tree->getNumOfChild() > maxRank){
            maxRank = tree->getNumOfChild();
            maxNode = tree->getNode();
        }
        for(int i = 0; i < tree->getNumOfChild(); i = i + 1){
            TreeTravel.push((MaxRankTree*)tree->children[i]);
        }
    }
    delete firstTree;
    return  maxNode;
}

//const MaxRankTree *MaxRankTree::traceTreeRecursion(int currMax) const {
//    const MaxRankTree *output = nullptr;
//    int number_of_Children=children.size();
//    if (number_of_Children > currMax) {
//        currMax = children.size();
//        output = this;
//    }
//    for (int i = 0; i < number_of_Children; i = i + 1) {
//        const MaxRankTree *maxInChild = ((MaxRankTree *) children[i])->traceTreeRecursion(currMax);
//        if (maxInChild != nullptr) {
//            output = maxInChild;
//            currMax = maxInChild->node;
//        }
//    }
//    return output;
//}

//---------------------------------------RootTree---------------------------------------------------------------
RootTree::RootTree(const RootTree &other) : Tree(other) {}

///========Rule of 3
RootTree::RootTree(int rootLabel) : Tree(rootLabel)  {}

RootTree *RootTree::clone() const {
    return new RootTree(*this);
}

int RootTree::traceTree() const {
    return node;
}

