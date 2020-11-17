#include <iostream>
#include "../include/Session.h"

using namespace std;

int main(int argc, char **argv) {
    if (argc != 2) {
        cout << "usage cTrace <config_path>" << endl;
        return 0;
    }

    Session sess(argv[1]);
    sess.simulate();

//    MaxRankTree* t1=((MaxRankTree*)(sess.BFS(1)));
//    MaxRankTree* t2=((MaxRankTree*)(sess.BFS(2)));
//    MaxRankTree* t3=((MaxRankTree*)(sess.BFS(3)));
//t1=t2=t3;
//t1->addChild(t2);
    //    MaxRankTree* t4=((MaxRankTree*)(sess.BFS(4)));
//
//    *t2=std::move(*t1);
//    *t4=*t3;
//    int i=2;
//
//    delete t1;
//    delete t2;
//    delete t3;
//    delete t4;
//    return 0;
}