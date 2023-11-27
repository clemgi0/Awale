#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>

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
    int exit = 0;

    while (!exit)
    {
        clear();

        showPlayer(actualPlayer);
        showBoard(board);

        printw("Select a number between 1 and 6\n");
        int colSelected;
        scanw("%d", &colSelected);

        colSelected--;

        while (!isLegalMove(board, colSelected, actualPlayerLine))
        {
            printw("\nPlease select a legal move.\n\n");
            printw("Select a number between 1 and 6\n");
            scanw("%d", &colSelected);

            colSelected--;
        }

        Case actualCase = {actualPlayerLine, colSelected};

        Case arrivalCase = getArrivalCase(board.board[actualPlayerLine][colSelected], actualCase);
        board = makeMove(board, actualCase);
        game = addMove(game, colSelected);
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