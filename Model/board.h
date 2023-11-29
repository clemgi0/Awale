#ifndef BOARD_H
#define BOARD_H

typedef struct
{
    int board[2][6];
} Board;

typedef struct
{
    int line;
    int col;
} Case;

Board createBoard(void);
void showBoard(Board);
Case nextCase(Case);
Case getArrivalCase(int, Case);
Board makeMove(Board, Case);
int isLegalMove(Board, Case);
int areCasesTaken(Board, int, Case);
Board emptyCasesTaken(Board, Case, int);

#endif // BOARD_H