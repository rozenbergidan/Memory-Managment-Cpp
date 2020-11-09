//
// Created by spl211 on 02/11/2020.
//


#include "Tree.h"
#include "Session.h"

using namespace std;

Tree::Tree(int rootLabel) : node(rootLabel) {}

Tree::Tree(const Tree &other) : children(), node(other.node) {
    for (int i = 0; i < other.children.size(); i = i + 1) {
        children.push_back(other.children[i]);
    }
}

void Tree::addChild(const Tree &child) {
    children.push_back(child.clone());
}


Tree::~Tree() {
    for (int i = 0; i < children.size(); i = i + 1) {
        if (children[i]) delete children[i];
    }
}

const Tree &Tree::operator=(const Tree &other) {
    node = other.node;
    children = other.children;//TODO: check if the vector = operator is good for us... if not go through all the vector.
}

int Tree::getNode() const {
    return node;
}

Tree *Tree::createTree(const Session &session, int rootLabel) {
    if (session.getTreeType() == TreeType::Cycle) return new CycleTree(rootLabel, session.getCycleCount());
    if (session.getTreeType() == TreeType::Root) return new MaxRankTree(rootLabel);
    if (session.getTreeType() == TreeType::MaxRank) return new RootTree(rootLabel);
}

//---------------------------------------CycleTree--------------------------------------------------------------
CycleTree::CycleTree(int rootLabel, int currCycle) : Tree(rootLabel), currCycle(currCycle) {}

CycleTree::CycleTree(const CycleTree &other) : Tree(other), currCycle(other.currCycle) {}


const CycleTree &CycleTree::operator=(const CycleTree &other) {
    children = other.children;
    node = other.node;
    currCycle = other.currCycle;
    return *this;

}

int CycleTree::traceTree() const {
    const CycleTree *outputTree = this;
    for (int i = 0; i <= currCycle; i = i + 1) {
        if(!outputTree->children.empty()) outputTree = (CycleTree *) outputTree->children[0];
    }
    return outputTree->node;
}

CycleTree *CycleTree::clone() const {
    return new CycleTree(*this);
}

//---------------------------------------MaxRankTree------------------------------------------------------------
MaxRankTree::MaxRankTree(const MaxRankTree &other) : Tree(other) {}

MaxRankTree::MaxRankTree(int rootLabel) : Tree(rootLabel) {}

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

MaxRankTree *MaxRankTree::clone() const {
    return new MaxRankTree(*this);
}

//---------------------------------------RootTree---------------------------------------------------------------
RootTree::RootTree(const RootTree &other) : Tree(other) {}

RootTree::RootTree(int rootLabel) : Tree(rootLabel) {}

int RootTree::traceTree() const {
    return node;
}

RootTree *RootTree::clone() const {
    return new RootTree(*this);
}
//--------------------------------------------------------------------------------------------------------------































