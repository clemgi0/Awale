// Fonctions pour la gestion du chat.
// Échange de messages.
// Bio ASCII.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "chat.h"

#define MAX_MESSAGE_LENGTH 256
#define BIO_LENGTH 10

typedef struct {
    char messages[MAX_MESSAGE_LENGTH];
    char bio[BIO_LENGTH];
    // Autres informations liées au chat
} ChatInfo;

static ChatInfo chatData[MAX_CLIENTS];

void sendMessage(const char *sender, const char *receiver, const char *message) {
    // Trouver le destinataire dans la liste des clients
    for (int i = 0; i < numClients; ++i) {
        if (strcmp(clients[i].username, receiver) == 0) {
            // Envoyer le message au destinataire
            // Vous devrez implémenter la communication via sockets ici
            printf("[%s] to [%s]: %s\n", sender, receiver, message);
            return;
        }
    }

    // Si le destinataire n'est pas trouvé, gérer l'erreur
    printf("Error: Receiver not found\n");
}

void setBio(const char *username, const char *bio) {
    // Trouver l'utilisateur dans la liste des clients
    for (int i = 0; i < numClients; ++i) {
        if (strcmp(clients[i].username, username) == 0) {
            // Copier la bio ASCII dans la structure de données
            strncpy(chatData[i].bio, bio, BIO_LENGTH - 1);
            chatData[i].bio[BIO_LENGTH - 1] = '\0'; // Assurer la null-termination
            return;
        }
    }

    // Si l'utilisateur n'est pas trouvé, gérer l'erreur
    printf("Error: User not found\n");
}

void displayBio(const char *username) {
    // Trouver l'utilisateur dans la liste des clients
    for (int i = 0; i < numClients; ++i) {
        if (strcmp(clients[i].username, username) == 0) {
            // Afficher la bio ASCII de l'utilisateur
            printf("Bio for [%s]: %s\n", username, chatData[i].bio);
            return;
        }
    }

    // Si l'utilisateur n'est pas trouvé, gérer l'erreur
    printf("Error: User not found\n");
}
