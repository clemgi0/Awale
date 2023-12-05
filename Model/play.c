#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <ctype.h>
#include <unistd.h>

#include "board.h"
#include "player.h"
#include "game.h"

Game play(Game game)
{
    int actualPlayerLine = game.actualPlayer.playerNumber;

    char colSelectedString[100];
    scanw("%s", colSelectedString);

    Case actualCase = {actualPlayerLine, -1};

    if (isdigit(colSelectedString[0]))
    {
        int colSelected = atoi(colSelectedString);
        colSelected--;
        actualCase.col = colSelected;
    }

    while (!isdigit(colSelectedString[0]) || !isLegalMove(game.board, actualCase))
    {
        printw("\nInvalid entry.");
        printw("\nSelect a number between 1 and 6:\n");

        refresh();

        scanw("%s", colSelectedString);

        if (isdigit(colSelectedString[0]))
        {
            int colSelected = atoi(colSelectedString);
            colSelected--;
            actualCase.col = colSelected;
        }
    }

    Case arrivalCase = getArrivalCase(game.board.board[actualCase.line][actualCase.col], actualCase);
    game.board = makeMove(game.board, actualCase);
    game = addMove(game, actualCase.col);
    int numberOfCasesTaken = areCasesTaken(game.board, actualPlayerLine, arrivalCase);

    if (numberOfCasesTaken)
    {
        game.actualPlayer = addPoint(game.board, game.actualPlayer, arrivalCase, numberOfCasesTaken);
        game.board = emptyCasesTaken(game.board, arrivalCase, numberOfCasesTaken);

        if (checkWinner(game.actualPlayer))
        {
            game.winner = 1 + game.actualPlayer.playerNumber;
        }
    }

    if (checkDraw(&game, numberOfCasesTaken))
    {
        game.winner = 3;
    }

    actualPlayerLine++;
    actualPlayerLine = actualPlayerLine % 2;

    if (!actualPlayerLine)
    {
        game.secondPlayer = game.actualPlayer;
        game.actualPlayer = game.firstPlayer;
    }
    else
    {
        game.firstPlayer = game.actualPlayer;
        game.actualPlayer = game.secondPlayer;
    }

    printw("\n");

    return game;
}

Game playOpponent(Game game, int move)
{
    int actualPlayerLine = game.actualPlayer.playerNumber;
    Case actualCase = {actualPlayerLine, move};

    Case arrivalCase = getArrivalCase(game.board.board[actualCase.line][actualCase.col], actualCase);
    game.board = makeMove(game.board, actualCase);
    game = addMove(game, actualCase.col);
    int numberOfCasesTaken = areCasesTaken(game.board, actualPlayerLine, arrivalCase);

    if (numberOfCasesTaken)
    {
        game.actualPlayer = addPoint(game.board, game.actualPlayer, arrivalCase, numberOfCasesTaken);
        game.board = emptyCasesTaken(game.board, arrivalCase, numberOfCasesTaken);

        if (checkWinner(game.actualPlayer))
        {
            game.winner = game.actualPlayer.playerNumber;
        }
    }

    if (checkDraw(&game, numberOfCasesTaken))
    {
        game.winner = 3;
    }

    actualPlayerLine++;
    actualPlayerLine = actualPlayerLine % 2;

    if (!actualPlayerLine)
    {
        game.secondPlayer = game.actualPlayer;
        game.actualPlayer = game.firstPlayer;
    }
    else
    {
        game.firstPlayer = game.actualPlayer;
        game.actualPlayer = game.secondPlayer;
    }

    return game;
}