#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

#include "player.h"

Player createPlayer(int playerNb)
{
    Player player;

    player.playerNumber = playerNb;

    return player;
}