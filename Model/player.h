#ifndef PLAYER_H
#define PLAYER_H
#define MAX_PSEUDO_LENGTH 50


typedef struct
{
    int score;
    int playerNumber;
    char pseudo[MAX_PSEUDO_LENGTH];
} Player;

Player createPlayer(int);

void setPseudo(Player *player, const char *pseudo);

#endif // PLAYER_H