#ifndef PRIVATE_MODE_H
#define PRIVATE_MODE_H

#define MAX_CLIENTS 100
#define MAX_USERNAME_LENGTH 50

extern int numClients; // Déclarer la variable numClients définie ailleurs

typedef struct
{
    char username[MAX_USERNAME_LENGTH];
    // Autres informations liées au client
} ClientInfo;

// Déclarer la structure PrivateModeInfo
typedef struct
{
    char friends[MAX_CLIENTS][MAX_USERNAME_LENGTH];
    int numFriends;
    // Autres informations liées au mode privé
} PrivateModeInfo;

// Déclarer les fonctions associées au mode privé
void addFriend(const char *username, const char *friendUsername);
int isFriend(const char *username, const char *potentialFriend);

#endif // PRIVATE_MODE_H
