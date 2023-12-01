#ifndef GAME_H
#define GAME_H

#include "player.h"

#define MAX_MOVE 10000

typedef struct
{
    Player firstPlayer;
    Player secondPlayer;
    int numberOfMoves;
    int moves[MAX_MOVE];
    int lastScoringTour;
} Game;

Game createGame(Player, Player);
Game addMove(Game, int);
int checkDraw(Game *, int);

#endif // GAME_H