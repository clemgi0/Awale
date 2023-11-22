#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "board.h"

Board createBoard(void)
{
    Board newBoard;

    // Initialiser le tableau avec des valeurs par défaut
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            newBoard.board[i][j] = 4;
        }
    }

    return newBoard;
}

void showBoard(Board board)
{
    // printf("%ld", sizeof(board->board));
    // printf("%ld", sizeof(board->board[0]));

    // Afficher le contenu du tableau
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%d ", board.board[i][j]);
        }
        printf("\n");
    }
}