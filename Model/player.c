#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ncurses.h>

#include "player.h"
#include "board.h"

Player createPlayer(int playerNb, char *name)
{
    Player player;
    player.playerNumber = playerNb;
    player.score = 0;
    player.name = name;

    return player;
}

void showPlayer(Player player)
{
    printw("\n\nPlayer : %s | Score: %d\n", player.name, player.score);

    refresh();
}

Player addPoint(Board board, Player player, Case arrivalCase, int numberOfCasesTaken)
{
    while (numberOfCasesTaken > 0)
    {
        player.score += board.board[arrivalCase.line][arrivalCase.col];
        numberOfCasesTaken--;
        arrivalCase.col = arrivalCase.col + 1 - 2 * arrivalCase.line;
    }

    return player;
}

int checkWinner(Player player)
{
    if (player.score >= 25)
    {
        printw("\n\n----------------------------------------------\nPlayer %s has won the game with %d points!! GGs\n----------------------------------------------", player.name, player.score);
        refresh();

        return 1;
    }

    return 0;
}