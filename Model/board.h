#ifndef BOARD_H
#define BOARD_H

typedef struct
{
    int **board;
} Board;

Board *createBoard(void);
void showBoard(Board *);
void freeBoard(Board *);

#endif // BOARD_H
