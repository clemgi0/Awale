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

void setPseudo(Player *player, const char *pseudo)
{
    strncpy(player->pseudo, pseudo, 10 - 1);
    player->pseudo[10 - 1] = '\0'; 
}
