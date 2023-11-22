#ifndef BOARD_H
#define BOARD_H

#ifndef PLAYER_H
#define PLAYER_H

#include "player.h"

#endif // PLAYER_H

typedef struct
{
    int board[2][5];
} Board;

Board createBoard(void);
void showBoard(Board);
// void makeMove(Board, int, Player);

#endif // BOARD_H