#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "Model/board.h"
#include "Model/player.h"

int main()
{
    Board board = createBoard();
    int exit = 0;
    int selection;

    while (!exit)
    {
        printf("Select an option\n1. Show board\n2. Exit\n");

        scanf("%d", &selection);

        switch (selection)
        {
        case 1:
            showBoard(board);
            break;

        case 2:
            exit = 1;
            break;

        default:
            break;
        }

        printf("\n");
    }

    printf("End of the game.\n");

    return 0;
}