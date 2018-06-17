//
// Created by 123yt on 12/06/2018.
//

#include "hashTable.h"


HashTable::HashTable():tableSize(0), numofElements(0){}

HashTable::HashTable(int n):numofElements(0){
    int i;
    for(i=1; i <= n; i*=2);
    this->tableSize = i;
    this->table = new List<Clan*>[tableSize];
}

void HashTable::init(int n, Clan** arr){
    for(int i = 0; i < n; i++){
        this->addClan(arr[i]);
    }
}

int HashTable::getTableSize() {
    return this->tableSize;
}

int HashTable::getNumofElements() {
    return this->numofElements;
}

void HashTable::addClan(int clanID) {
    Clan tempClan = Clan(clanID);
    addClan(&tempClan);
}

void HashTable::addClan(Clan* clan) {
    int insertionPlace = (clan->getClanId())%(this->tableSize);
    this->table[insertionPlace].insert(clan);
    this->numofElements++;
    if(this->numofElements == this->tableSize){
        rehash();
    }
}

void HashTable::rehash() {
    int tempsize = this->tableSize;
    List<Clan*> *temptable = this->table;
    this->tableSize *=2;
    this->table = new List<Clan*>[tableSize];
    this->numofElements = 0;
    for(int i = 0 ; i < tempsize; i++){
        for(List<Clan*>::Iterator it = temptable[i].begin();
            it != temptable[i].end(); it++){
            addClan(*it);
        }
    }
    delete[] temptable;
}

Clan* HashTable::find(int clanID) {
    int insertionPlace = clanID % this->tableSize;
    for (List<Clan *>::Iterator iter = this->table[insertionPlace].begin();
         iter != this->table[insertionPlace].end(); iter++) {
        if ((*iter)->getClanId() == clanID) {
            return (*iter);
        }
    }
    return NULL;
}

HashTable::~HashTable(){
    delete[] table;
}