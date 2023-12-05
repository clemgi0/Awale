#ifndef PLAYER_H
#define PLAYER_H

#include "board.h"

typedef struct
{
    int score;
    int playerNumber;
    char *name;
} Player;

Player createPlayer(int, char *);
void showPlayer(Player);
Player addPoint(Board, Player, Case, int);
int checkWinner(Player);

#endif // PLAYER_H