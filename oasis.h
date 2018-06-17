//
// Created by 123yt on 11/06/2018.
//
#ifndef HW3_OASIS_H
#define HW3_OASIS_H

#include "avltree.h"
#include "player.h"
#include "minHeap.h"
#include "hashTable.h"

class Oasis{
    HashTable allClans;
    minHeap<int> freeClans;
    AVLtree<int, Player*>* allPlayers;

public:
    Oasis();
    Oasis(int numOfClans, int *clanIDs);
    HashTable* getClans();
    int getHashTableSize();
    int getNumOfClans();
    AVLtree<int, Player*>* getPlayers();
    int getNumOfPlayers();

    StatusType addClan(int clanID);
    StatusType addPlayer(int playerID, int score, int clan);
    StatusType clanFight(int clan1, int clan2, int k1, int k2);
    StatusType getMinClan(int *clan);
    ~Oasis();

};
#endif //HW3_OASIS_H
