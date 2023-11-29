#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "Model/board.h"
#include "Model/player.h"

int main()
{
    Board board = createBoard();
    Player player = createPlayer(0);

    char pseudo[MAX_PSEUDO_LENGTH];

    printf("Enter your pseudo: ");
    scanf("%s", pseudo);
    setPseudo(&player, pseudo);

    int exit = 0;
    int selection;

    while (!exit)
    {
        printf("Select an option\n1. Show board\n2. Make move\n3. Exit\n");

        scanf("%d", &selection);

        switch (selection)
        {
        case 1:
            showBoard(board);
            break;

        case 2:
            printf("Select a number between 0 and 5\n");
            int caseSelected;
            scanf("%d", &caseSelected);
            board = makeMove(board, caseSelected, player);
            break;

        case 3:
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
