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
        for (int j = 0; j < 6; j++)
        {
            newBoard.board[i][j] = 4;
        }
    }

    return newBoard;
}

void showBoard(Board board)
{
    // printf("%ld", sizeof(board.board));
    // printf("%ld", sizeof(board.board[0]));

    // Afficher le contenu du tableau
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 6; j++)
        {
            printf("%d ", board.board[i][j]);
        }
        printf("\n");
    }
}

Board makeMove(Board board, int actualCase, int actualLine)
{
    int numberOfStones = board.board[actualLine][actualCase];

    board.board[actualLine][actualCase] = 0;

    for (int i = 0; i < numberOfStones; i++)
    {
        if (!actualLine)
        {
            if (actualCase - 1 == -1)
            {
                actualLine = 1;
                actualCase = 0;
                board.board[actualLine][actualCase]++;

                continue;
            }

            board.board[actualLine][--actualCase]++;

            continue;
        }

        if (actualCase + 1 == 6)
        {
            actualLine = 0;
            actualCase = 5;
            board.board[actualLine][actualCase]++;

            continue;
        }

        board.board[actualLine][++actualCase]++;
    }

    return board;
}

int isLegalMove(Board board, int actualCase, int line)
{
    return (board.board[line][actualCase] == 0 || actualCase < 0 || actualCase > 6 || line < 0 || line > 1) ? 0 : 1;
}