#ifndef PLAYER_H
#define PLAYER_H
#define MAX_PSEUDO_LENGTH 50


#include "board.h"

typedef struct
{
    int score;
    int playerNumber;
    char pseudo[MAX_PSEUDO_LENGTH];
} Player;

Player createPlayer(int);
void showPlayer(Player);
Player addPoint(Board, Player, Case, int);
int checkWinner(Player);

void setPseudo(Player *player, const char *pseudo);

#endif // PLAYER_H