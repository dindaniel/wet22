//
// Created by 123yt on 11/06/2018.
//
#ifndef HW3_CLAN_H
#define HW3_CLAN_H

#include "avltree.h"
#include "player.h"
#include "library2.h"
#include "comperators.h"

class Clan{
    int clanId;
    AVLtree<ClanKey, Player*> playerTree; //all of the players in this clan (ranks)
    bool is_conquered;
    int clanSize;

public:
    Clan();
    explicit Clan(int clanId);
    int getClanId();
    AVLtree<ClanKey,Player*>* getPlayers();
    bool isConqured();
    int getClanSize();
    void surrender();

    StatusType addPlayerToClan(Player* pl);
    bool isEmpty();
    bool operator==(Clan& other);
    bool operator<(Clan& other);
    /**
     * this method returns the sum of the k highest ranking players in the clan.
     * shouldn't be a problem once we add the ranks and sums to the tree
     * @param k - the number of players
     * @return sum of k best players' scores
     */
    int getFightScore(int k); //for clanFight, after finishing rank tree
};
#endif //HW3_CLAN_H
