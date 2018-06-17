//
// Created by 123yt on 16/06/2018.
#include "library2.h"
#include "oasis.h"

void* init(int n, int* clanIDs){
    if(n<2)
        return NULL;
    for(int i = 0; i < n; i++){
        if(clanIDs[i]<0) return NULL;
    }
    Oasis* DS = new Oasis(n, clanIDs);
    return (void*)DS;
}

StatusType addClan(void* DS, int clanID){
    if(DS == NULL){
        return INVALID_INPUT;
    }
    return ((Oasis*)DS)->addClan(clanID);
}

StatusType addPlayer(void* DS, int playerID, int score, int clan){
    if(DS == NULL){
        return INVALID_INPUT;
    }
    return ((Oasis*)DS)->addPlayer(playerID, score, clan);
}

StatusType clanFight(void* DS, int clan1, int clan2, int k1, int k2){
    if(DS == NULL){
        return INVALID_INPUT;
    }
    return ((Oasis*)DS)->clanFight(clan1, clan2, k1,k2);
}
StatusType getMinClan(void* DS, int* clan){
    if(DS == NULL){
        return INVALID_INPUT;
    }
    return ((Oasis*)DS)->getMinClan(clan);
}

void quit(void** DS){
    if(DS == NULL || *DS == NULL){
        return;
    }
    delete(*DS);
}