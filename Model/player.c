#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ncurses.h>

#include "player.h"
#include "board.h"

Player createPlayer(int playerNb)
{
    Player player;

    player.playerNumber = playerNb;

    player.score = 0;

    return player;
}

void showPlayer(Player player)
{
    printw("\n\nPlayer number: %d | Score: %d\n", player.playerNumber + 1, player.score);

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
        printf("\n\n----------------------------------------------\nPlayer %d has won the game with %d points!! GGs\n----------------------------------------------", player.playerNumber + 1, player.score);

        return 1;
    }

    return 0;
}

void setPseudo(Player *player, const char *pseudo)
{
    strncpy(player->pseudo, pseudo, 10 - 1);
    player->pseudo[MAX_PSEUDO_LENGTH - 1] = '\0'; 
}
