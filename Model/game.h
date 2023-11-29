#ifndef GAME_H
#define GAME_H

#include "player.h"

#define MAX_MOVE 1000

typedef struct
{
    Player firstPlayer;
    Player secondPlayer;
    int numberOfMoves;
    int moves[MAX_MOVE];
} Game;

Game createGame(Player, Player);
Game addMove(Game, int);

#endif // GAME_H