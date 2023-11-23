#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "game.h"

Game createGame(Player player1, Player player2)
{
    Game game;
    game.firstPlayer = player1;
    game.secondPlayer = player2;
    game.numberOfMoves = 0;

    return game;
}

Game addMove(Game game, int move)
{
    game.moves[++game.numberOfMoves] = move;

    return game;
}