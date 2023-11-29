// Fonctions pour la sauvegarde et la relecture des parties.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "awale.h" // Inclusion du fichier qui définit la structure du plateau

typedef struct {
    AwaleBoard board;
    // Autres informations liées à la sauvegarde de la partie
} SavedGame;

static SavedGame savedGames[MAX_CLIENTS * 2]; // Adapté à votre besoin

int saveGame(const char *playerA, const char *playerB, const AwaleBoard *board) {
    // Recherche d'un emplacement libre pour sauvegarder la partie
    for (int i = 0; i < MAX_CLIENTS * 2; ++i) {
        if (savedGames[i].board == NULL) {
            // Copie du plateau de jeu
            memcpy(&(savedGames[i].board), board, sizeof(AwaleBoard));
            // Ajouter ici noms des joueurs, scores, classement
            return 1; // La sauvegarde a réussi
        }
    }

    // Gérer l'erreur si aucun emplacement libre n'est trouvé
    printf("Error: No available slots for saving games\n");
    return 0;
}

int loadGame(const char *playerA, const char *playerB, AwaleBoard *board) {
    // Recherche de la partie sauvegardée
    for (int i = 0; i < MAX_CLIENTS * 2; ++i) {
        // Comparaison des noms des joueurs (adapté à votre besoin)
        if (savedGames[i].board != NULL &&
            strcmp(savedGames[i].playerA, playerA) == 0 &&
            strcmp(savedGames[i].playerB, playerB) == 0) {
            // Copie du plateau de jeu
            memcpy(board, &(savedGames[i].board), sizeof(AwaleBoard));
            return 1; // Le chargement a réussi
        }
    }

    // Gérer l'erreur si la partie sauvegardée n'est pas trouvée
    printf("Error: Saved game not found\n");
    return 0;
}
