#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ncurses.h>

#include "board.h"
#include "player.h"

Board createBoard(void)
{
    Board newBoard;

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
    printw("-------------------------\n");

    for (int i = 0; i < 2; i++)
    {
        printw("| ");

        for (int j = 0; j < 6; j++)
        {
            printw("%d | ", board.board[i][j]);
        }

        printw("\n");
        if (i < 1)
            printw("|---|---|---|---|---|---|\n");
    }

    printw("-------------------------\n");

    refresh(); // Rafraîchit l'écran
}

Case nextCase(Case nextCase)
{
    if (!nextCase.line)
    {
        if (nextCase.col - 1 == -1)
        {
            nextCase.line = 1;
            nextCase.col = 0;

            return nextCase;
        }

        nextCase.col--;

        return nextCase;
    }

    if (nextCase.col + 1 == 6)
    {
        nextCase.line = 0;
        nextCase.col = 5;

        return nextCase;
    }

    nextCase.col++;

    return nextCase;
}

Case getArrivalCase(int numberOfStones, Case actualCase)
{
    for (int i = 0; i < numberOfStones; i++)
    {
        actualCase = nextCase(actualCase);
    }

    return actualCase;
}

Board makeMove(Board board, Case actualCase)
{
    int numberOfStones = board.board[actualCase.line][actualCase.col];

    board.board[actualCase.line][actualCase.col] = 0;

    for (int i = 0; i < numberOfStones; i++)
    {
        actualCase = nextCase(actualCase);

        if (i != 0 && i % 12 == 0)
            actualCase = nextCase(actualCase);

        board.board[actualCase.line][actualCase.col]++;
    }

    return board;
}

int isLegalMove(Board board, Case actualCase)
{
    return (board.board[actualCase.line][actualCase.col] == 0 || actualCase.col < 0 || actualCase.col > 6 || actualCase.line < 0 || actualCase.line > 1) ? 0 : 1;
}

int areCasesTaken(Board board, int playerNumber, Case arrivalCase)
{
    if (arrivalCase.line == playerNumber)
    {
        return 0;
    }

    int numberOfCasesTaken = 0;

    while ((arrivalCase.col > -1 && arrivalCase.col < 6) && (board.board[arrivalCase.line][arrivalCase.col] == 2 || board.board[arrivalCase.line][arrivalCase.col] == 3))
    {
        numberOfCasesTaken++;
        arrivalCase.col = arrivalCase.col + 1 - 2 * arrivalCase.line;
    }

    return numberOfCasesTaken;
}

Board emptyCasesTaken(Board board, Case arrivalCase, int numberOfCasesTaken)
{
    while (numberOfCasesTaken > 0)
    {
        board.board[arrivalCase.line][arrivalCase.col] = 0;
        numberOfCasesTaken--;
        arrivalCase.col = arrivalCase.col + 1 - 2 * arrivalCase.line;
    }

    return board;
}