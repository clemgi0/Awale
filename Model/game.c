#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ncurses.h>

#include "game.h"

Game createGame(Player first, Player second)
{
    Game newGame;
    newGame.firstPlayer = first;
    newGame.secondPlayer = second;
    newGame.numberOfMoves = 0;
    newGame.lastScoringTour = 0;

    return newGame;
}

int checkDraw(Game *game, int areCasesTaken)
{
    if (areCasesTaken)
        game->lastScoringTour = 0;
    else
        game->lastScoringTour++;

    if (game->lastScoringTour > 49 || game->numberOfMoves == MAX_MOVE)
    {
        printw("\n\n----------------------------------------------\nNo player has won the game. This is a draw! GGs\n----------------------------------------------");
        refresh();

        return 1;
    }

    return 0;
}

Game addMove(Game game, int move)
{
    game.moves[game.numberOfMoves] = move;
    game.numberOfMoves++;

    return game;
}