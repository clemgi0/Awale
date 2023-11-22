#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "board.h"

Board *createBoard(void)
{
    Board *newBoard = malloc(sizeof(Board)); // Allouer de la mémoire pour la structure Board

    // Vérifier si l'allocation a réussi
    if (newBoard == NULL)
    {
        perror("Erreur lors de l'allocation de mémoire pour Board");
        exit(EXIT_FAILURE);
    }

    // Allouer un tableau 2D de 2x5
    newBoard->board = (int **)malloc(2 * sizeof(int *));
    for (int i = 0; i < 2; i++)
    {
        newBoard->board[i] = (int *)malloc(5 * sizeof(int));
    }

    // Initialiser le tableau avec des valeurs par défaut
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            newBoard->board[i][j] = 4;
        }
    }

    return newBoard;
}

void showBoard(Board *board)
{
    // printf("%ld", sizeof(board->board));
    // printf("%ld", sizeof(board->board[0]));

    // Afficher le contenu du tableau
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            printf("%d ", board->board[i][j]);
        }
        printf("\n");
    }
}

void freeBoard(Board *board)
{
    // Libérer la mémoire allouée pour le tableau 2D
    for (int i = 0; i < 2; i++)
    {
        free(board->board[i]);
    }
    free(board->board);
}