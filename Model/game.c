#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "game.h"

Game createGame(Player first, Player second)
{
    Game newGame;
    newGame.firstPlayer = first;
    newGame.secondPlayer = second;
    newGame.numberOfMoves = 0;
    // Initialiser d'autres propriétés au besoin
    return newGame;
}

Game addMove(Game game, int move)
{
    if (game.numberOfMoves < MAX_MOVE)
    {
        game.moves[game.numberOfMoves] = move;
        game.numberOfMoves++;
    }
    // Gérer le cas où le tableau de mouvements est plein
    return game;
}