#ifndef SERVER_H
#define SERVER_H

#ifdef WIN32

#include <winsock2.h>

#elif defined(linux)

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h> /* close */
#include <netdb.h>  /* gethostbyname */
#define INVALID_SOCKET -1
#define SOCKET_ERROR -1
#define closesocket(s) close(s)
typedef int SOCKET;
typedef struct sockaddr_in SOCKADDR_IN;
typedef struct sockaddr SOCKADDR;
typedef struct in_addr IN_ADDR;

#else

#error not defined for this platform

#endif

#define CRLF "\r\n"
#define PORT 1977
#define MAX_CLIENTS 100
#define BUF_SIZE 1024

typedef struct
{
    int sock;
    char name[BUF_SIZE];
    char *bio;
    int in_game;    // Indique si le joueur est actuellement en jeu
    int challenger; // Le socket du joueur qui a émis un défi (0 si pas de défi)
} Client;

static void init(void);
static void end(void);
static void app(void);
static int init_connection(void);
static int accept_connection(int server_socket, Client *clients, int *actual, fd_set *rdfs);
static void end_connection(int sock);
static int read_client(SOCKET sock, char *buffer);
static void write_client(SOCKET sock, const char *buffer);
static void disconnect_client(Client client, Client *clients, int *actual, int index);
static void close_client(Client *clients, int to_remove, int *actual);
static void handle_clients(Client *clients, int *actual, fd_set *rdfs, char *buffer);
static void get_client_list(Client *clients, int index, char message[1024], int *actual);
static void send_message_to_client(int sock, const char *message);
static void send_message_to_all_clients(Client *clients, Client client, int actual, const char *buffer, char from_server);
static void clear_clients(Client *clients, int actual);
static int find_player_index_by_socket(Client *clients, int actual, int sock);
static int find_player_index_by_name(Client *clients, int actual, const char *name);
static int is_valid_entry(char *entry, int min, int max);

#endif /* guard */