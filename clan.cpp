//
// Created by 123yt on 11/06/2018.
//
#include "clan.h"

Clan::Clan(): clanId(-1), is_conquered(false), clanSize(0) {
    this->playerTree = new AVLtree<ClanKey, Player*>();
}

Clan::Clan(int clanId): clanId(clanId),is_conquered(false), clanSize(0){
    this->playerTree = new AVLtree<ClanKey, Player*>();
}

int Clan::getClanId() {
    return this->clanId;
}

AVLtree<ClanKey, Player*>* Clan::getPlayers() {
    return this->playerTree;
}

bool Clan::isConqured() {
    return this->is_conquered;
}

bool Clan::isEmpty() {
    return (this->clanSize == 0);
}

int Clan::getClanSize() {
    return this->clanSize;
}

void Clan::surrender() {
    this->is_conquered = true;
}

StatusType Clan::addPlayerToClan(Player *pl) {
    ClanKey key = ClanKey(pl->getPlayerId(),pl->getScore());
    if(!this->playerTree->contains(key)){
        this->playerTree->insert(key,pl, pl->getScore());
    }
    this->clanSize++;
    return SUCCESS;
}

bool Clan::operator==(Clan &other) {
    return (this->clanId == other.clanId);
}

bool Clan::operator<(Clan &other) {
    return this->clanId < other.clanId;
}

int Clan::getFightScore(int k) {
    return this->playerTree->getSumByRank(k);
}

