#include <iostream>
#include "avltree.h"

//
// Created by din on 16/06/2018.
//
int main(){
    AVLtree<int,int> t1;
    t1.insert(2,2,2);
    t1.insert(12,12,12);
    t1.insert(8,8,8);
    t1.insert(14,14,14);
    t1.insert(16,16,16);
    t1.insert(20,20,20);
    t1.insert(26,26,26);
    t1.insert(24,24,24);
    t1.insert(28,28,28);
    t1.insert(4,4,4);
    t1.insert(10,10,10);
    t1.insert(22,22,22);
    t1.insert(30,30,30);
    t1.insert(6,6,6);
    t1.insert(18,18,18);
    std::cout << t1.getSumByRank(7);
}
