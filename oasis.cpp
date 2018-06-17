//
// Created by 123yt on 12/06/2018.
//
#include "oasis.h"

Oasis::Oasis(): allClans(HashTable()), allPlayers(),
    freeClans(){}

Oasis::Oasis(int numOfClans, int *clanIDs): allClans(HashTable(numOfClans)),
    allPlayers(AVLtree<int, Player*>()){

    Clan** clanArr = new Clan*[numOfClans];
    for(int i = 0; i<numOfClans; i++){
        int id = clanIDs[i];
        clanArr[i] = new Clan(id);
    }
    this->allClans.init(numOfClans, clanArr);
    this->freeClans = minHeap<Clan*>(clanArr, numOfClans);
    delete[] clanArr;
}

HashTable* Oasis::getClans() {
    return &this->allClans;
}

int Oasis::getHashTableSize() {
    return this->allClans.getTableSize();
}

int Oasis::getNumOfClans() {
    return this->allClans.getNumofElements();
}

minHeap<Clan*>* Oasis::getFreeClans() {
    return &this->freeClans;
}

AVLtree<int, Player*>* Oasis::getPlayers() {
    return &this->allPlayers;
}

int Oasis::getNumOfPlayers() {
    return this->allPlayers.getSize();
}

StatusType Oasis::addClan(int clanID) {
    if(clanID < 0){
        return INVALID_INPUT;
    }
    if(this->allClans.find(clanID) != NULL){
        return FAILURE;
    }
    Clan* cl;
    try{
        cl = new Clan(clanID);
    }catch (std::bad_alloc&){
        return ALLOCATION_ERROR;
    }
    this->allClans.addClan(clanID);
    this->freeClans.insert(&cl);
    return SUCCESS;
}

StatusType Oasis::addPlayer(int playerID, int score, int clan){
    if(playerID<0 || score <0 || clan<0){
        return INVALID_INPUT;
    }
    if(this->allPlayers.contains(playerID) || this->allClans.find(clan) != NULL){
        return FAILURE;
    }
    Player *pl;
    try{
        pl = new Player(playerID, score);
    } catch(std::bad_alloc&){
        return ALLOCATION_ERROR;
    }
    this->allPlayers.insert(score, pl); //rank tree for simplicity??
    Clan *cl = this->allClans.find(clan);
    cl->addPlayerToClan(pl);
    return SUCCESS;
}

StatusType Oasis::clanFight(int clan1, int clan2, int k1, int k2) {
    if(k1 <= 0 || k2 <= 0 || clan1 < 0 || clan2 < 0){
        return INVALID_INPUT;
    }
    if(clan1==clan2){
        return FAILURE;
    }
    Clan *cl1 = this->allClans.find(clan1);
    Clan *cl2 = this->allClans.find(clan2);
    if(cl1 == NULL || cl2 == NULL){
        return FAILURE;
    }
    if(cl1->isConqured() || cl2->isConqured()){
        return FAILURE;
    }
    if(cl1->getClanSize() < k1 || cl2->getClanSize() < k2){
        return FAILURE;
    }
    int fightScore1 = cl1->getFightScore(k1);
    int fightScore2 = cl2->getFightScore(k2);
    if(fightScore1 == fightScore2){
        if(clan1 < clan2){
            cl2->surrender();
            this->freeClans.remove(&cl2);
            return SUCCESS;
        }
        cl1->surrender();
        this->freeClans.remove(&cl1);
        return SUCCESS;
    }
    if(fightScore1<fightScore2){
        cl1->surrender();
        this->freeClans.remove(&cl1);
        return SUCCESS;
    }
    cl2->surrender();
    this->freeClans.remove(&cl2);
    return SUCCESS;
}

StatusType Oasis::getMinClan(int *clan) {
    if(clan == NULL){
        return INVALID_INPUT;
    }
    if(this->freeClans.getNumofElements() == 0){
        return FAILURE; //implicit
    }
    *clan = this->freeClans.getMin()->getClanId();
    return SUCCESS;
}
