#ifndef BOARD_H
#define BOARD_H

#include "player.h"

typedef struct
{
    int board[2][6];
} Board;

Board createBoard(void);
void showBoard(Board);
Board makeMove(Board, int, Player);
void freeBoard(Board);

#endif // BOARD_H