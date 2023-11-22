#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "Model/board.h"

int main()
{
    Board *board = createBoard();

    showBoard(board);

    freeBoard(board);

    return 0;
}