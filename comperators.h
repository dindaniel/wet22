//
// Created by 123yt on 11/05/2018.
//

#ifndef HW1_COMPERATORS_H
#define HW1_COMPERATORS_H
/**|
 * this is the key we'll be using in the player tree in each clan
 */
class ClanKey{
    int score;
    int playerID;
public:
    ClanKey():score(0), playerID(0){};
    ClanKey(int playerId, int score): score(score),playerID(playerId){};
    int getScore(){
        return this->score;
    }
    int getPlayerId(){
        return this->playerID;
    }
    bool operator==(ClanKey other){
        return (this->score == other.score) && (this->playerID == other.playerID);
    }
    bool operator<(ClanKey other){
        if(this->score==other.score){
            return
                    (this->playerID < other.playerID);
        }
        return this->score < other.score;
    }
};

#endif //HW1_COMPERATORS_H


