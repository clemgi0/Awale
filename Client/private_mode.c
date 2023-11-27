// Fonctions pour le mode privé.
// Gestion de la liste d'amis pour les observateurs.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "private_mode.h"

typedef struct {
    char friends[MAX_CLIENTS][MAX_USERNAME_LENGTH];
    int numFriends;
    // Autres informations liées au mode privé
} PrivateModeInfo;

static PrivateModeInfo privateModeData[MAX_CLIENTS];

void addFriend(const char *username, const char *friendUsername) {
    // Trouver l'utilisateur dans la liste des clients
    for (int i = 0; i < numClients; ++i) {
        if (strcmp(clients[i].username, username) == 0) {
            // Ajouter un ami à la liste
            if (privateModeData[i].numFriends < MAX_CLIENTS) {
                strcpy(privateModeData[i].friends[privateModeData[i].numFriends], friendUsername);
                privateModeData[i].numFriends++;
            } else {
                // Gérer l'erreur si la liste d'amis est pleine
                printf("Error: Maximum friends reached\n");
            }
            return;
        }
    }

    // Gérer l'erreur si l'utilisateur n'est pas trouvé
    printf("Error: User not found\n");
}

int isFriend(const char *username, const char *potentialFriend) {
    // Trouver l'utilisateur dans la liste des clients
    for (int i = 0; i < numClients; ++i) {
        if (strcmp(clients[i].username, username) == 0) {
            // Vérifier si la personne est dans la liste d'amis
            for (int j = 0; j < privateModeData[i].numFriends; ++j) {
                if (strcmp(privateModeData[i].friends[j], potentialFriend) == 0) {
                    return 1; // La personne est un ami
                }
            }
            return 0; // La personne n'est pas un ami
        }
    }

    // Gérer l'erreur si l'utilisateur n'est pas trouvé
    printf("Error: User not found\n");
    return 0;
}
