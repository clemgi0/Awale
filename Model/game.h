#ifndef GAME_H
#define GAME_H

#include "player.h"
#include "board.h"

#define MAX_MOVE 10000

typedef struct
{
    Player firstPlayer;
    Player secondPlayer;
    Player actualPlayer;
    Board board;
    int numberOfMoves;
    int moves[MAX_MOVE];
    int lastScoringTour;
    int winner;
} Game;

Game createGame(Player, Player, Board);
Game setGame(Game, Player, Player, Board);
Game addMove(Game, int);
int checkDraw(Game *, int);

#endif // GAME_H