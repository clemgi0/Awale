#include <stdio.h>
#include <stdlib.h>
#include <ncurses.h>
#include <ctype.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>

#include "Model/board.h"
#include "Model/player.h"
#include "Model/game.h"

#define PORT 12345
#define MAX_PSEUDO_LENGTH 50

void sendPseudo(int socket, const char *pseudo)
{
    write(socket, pseudo, strlen(pseudo));
}

// Fonction pour envoyer un coup au serveur
void sendMove(int socket, int move)
{
    char moveStr[2]; // Supposant que chaque coup est représenté par un chiffre
    sprintf(moveStr, "%d", move);
    write(socket, moveStr, strlen(moveStr));
}

int main()
{
    initscr();   // Initialise ncurses
    curs_set(0); // Masque le curseur

    // Création du socket
    int clientSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (clientSocket == -1)
    {
        perror("Socket creation failed...\n");
        exit(0);
    }
    else
        printf("Socket successfully created..\n");

    // Paramètres du serveur
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(PORT);
    serverAddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    // Connexion au serveur
    if (connect(clientSocket, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) != 0)
    {
        perror("Connection with the server failed...\n");
        exit(0);
    }
    else
        printf("Connected to the server..\n");

    // Demander et envoyer le pseudo au serveur
    char pseudo[MAX_PSEUDO_LENGTH];
    printf("Enter your pseudo: ");
    scanf("%s", pseudo);
    sendPseudo(clientSocket, pseudo);

    // Déroulement du jeu
    Board board = createBoard();
    Player player1 = createPlayer(0);
    Player player2 = createPlayer(1);
    Game game = createGame(player1, player2);

    Player actualPlayer = player1;
    int actualPlayerLine = 0;

    int exit = 0;

    while (!exit)
    {
        // Récupérer le mouvement du joueur depuis l'entrée
        int move;
        printw("Select a number between 1 and 6\n");
        scanw("%d", &move);

        // Envoyer le mouvement au serveur
        sendMove(clientSocket, move);

        // Recevoir le mouvement de l'adversaire depuis le serveur
        int opponentMove;
        read(clientSocket, &opponentMove, sizeof(opponentMove));

        if (checkWinner(actualPlayer))
        {
            exit = 1;
        }
    }

    actualPlayerLine++;
    actualPlayerLine = actualPlayerLine % 2;

    if (!actualPlayerLine)
    {
        player2 = actualPlayer;
        actualPlayer = player1;
    }
    else
    {
        player1 = actualPlayer;
        actualPlayer = player2;
    }
}

printw("End of the game.\n");
refresh();

sleep(3);

// Fermeture du socket
close(clientSocket);
endwin();

return 0;
}
