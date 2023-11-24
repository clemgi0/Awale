#ifndef PLAYER_H
#define PLAYER_H

typedef struct
{
    int score;
    int playerNumber;
} Player;

Player createPlayer(int);

#endif // PLAYER_H