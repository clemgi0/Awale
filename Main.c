#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <ctype.h>

#include "Model/board.h"
#include "Model/player.h"
#include "Model/game.h"

int main()
{
    initscr();   // Initialise ncurses
    curs_set(0); // Masque le curseur

    Board board = createBoard();
    Player player1 = createPlayer(0);
    Player player2 = createPlayer(1);
    Game game = createGame(player1, player2);

    Player actualPlayer = player1;
    int actualPlayerLine = 0;
    Player player = createPlayer(0);

    char pseudo[MAX_PSEUDO_LENGTH];

    printf("Enter your pseudo: ");
    scanf("%s", pseudo);
    setPseudo(&player, pseudo);

    int exit = 0;

    while (!exit)
    {
        clear();

        showPlayer(actualPlayer);
        showBoard(board);

        printw("Select a number between 1 and 6\n");

        char colSelectedString[100];
        scanw("%s", colSelectedString);

        Case actualCase = {actualPlayerLine, -1};

        while (!isdigit(colSelectedString[0]) || !isLegalMove(board, actualCase))
        {
            printw("\nInvalid entry.");
            printw("\nSelect a number between 1 and 6:\n");

            scanw("%s", colSelectedString);

            if (isdigit(colSelectedString[0]))
            {
                int colSelected = atoi(colSelectedString);
                colSelected--;
                actualCase.col = colSelected;
            }
        }

        Case arrivalCase = getArrivalCase(board.board[actualCase.line][actualCase.col], actualCase);
        board = makeMove(board, actualCase);
        game = addMove(game, actualCase.col);
        int numberOfCasesTaken = areCasesTaken(board, actualPlayerLine, arrivalCase);

        if (numberOfCasesTaken)
        {
            actualPlayer = addPoint(board, actualPlayer, arrivalCase, numberOfCasesTaken);
            board = emptyCasesTaken(board, arrivalCase, numberOfCasesTaken);

            if (checkWinner(actualPlayer))
            {
                exit = 1;
            }
        }

        actualPlayerLine++;
        actualPlayerLine = actualPlayerLine % 2;

        if (!actualPlayerLine)
        {
            player2 = actualPlayer;
            actualPlayer = player1;
        }
        else
        {
            player1 = actualPlayer;
            actualPlayer = player2;
        }

        printw("\n");
    }

    printw("End of the game.\n");

    endwin();

    return 0;
}
