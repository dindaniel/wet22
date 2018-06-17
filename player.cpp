//
// Created by 123yt on 11/06/2018.
//

#include "player.h"

Player::Player(int playerId, int score): playerId(playerId), score(score){};

int Player::getPlayerId() { return this->playerId;}
int Player::getScore() { return this->score;}