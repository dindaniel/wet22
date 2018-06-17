//
// Created by 123yt on 11/06/2018.
//

#ifndef HW3_PLAYER_H
#define HW3_PLAYER_H

class Player{
    int playerId;
    int score;

public:
    Player(int playerId, int score);
    int getPlayerId();
    int getScore();
};
#endif //HW3_PLAYER_H
