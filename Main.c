#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "Model/board.h"
#include "Model/player.h"
#include "Model/game.h"

int main()
{
    Board board = createBoard();
    Player player1 = createPlayer(0);
    Player player2 = createPlayer(1);
    Game game = createGame(player1, player2);

    int actualPlayer = 0;
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
            printf("Select a number betwenn 0 and 5\n");
            int caseSelected;
            scanf("%d", &caseSelected);

            while (!isLegalMove(board, caseSelected, actualPlayer))
            {
                printf("\nPlease select a legal move.\n\n");
                printf("Select a number betwenn 0 and 5\n");
                int caseSelected;
                scanf("%d", &caseSelected);
            }

            board = makeMove(board, caseSelected, actualPlayer);
            game = addMove(game, caseSelected);
            actualPlayer = (++actualPlayer) % 2;

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