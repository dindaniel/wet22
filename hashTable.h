//
// Created by 123yt on 12/06/2018.
//
#ifndef HW3_HASHTABLE_H
#define HW3_HASHTABLE_H
//TODO: this shit

#include "clan.h"
#include "list.h"
class HashTable {

    int tableSize;
    int numofElements;
    List<Clan*> *table;

public:
    HashTable();
    HashTable(int n);
    int getTableSize();
    int getNumofElements();
    void init(int n, Clan **arr);
    void addClan(int clanID);
    Clan* find(int clanID);
    void addClan(Clan* clan);
    void rehash();

    ~HashTable();
};
#endif //HW3_HASHTABLE_H
