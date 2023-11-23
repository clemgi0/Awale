#ifndef BOARD_H
#define BOARD_H

#include "player.h"

typedef struct
{
    int board[2][6];
} Board;

Board createBoard(void);
void showBoard(Board);
Board makeMove(Board, int, int);
int isLegalMove(Board, int, int);

#endif // BOARD_H