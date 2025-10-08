#ifndef TREE_H_
#define TREE_H

#include "Array.h"

class Tree {
public:
    int n,p[1002];
    Tree(int N,int *P);
    bool next_permutation();
    ~ Tree();
};

#endif