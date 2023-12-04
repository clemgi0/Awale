#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>

#include "server2.h"

#ifdef _WIN32
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#else
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/select.h>
#include "../
#endif

static void init(void)
{
#ifdef _WIN32
    WSADATA wsa;
    int err = WSAStartup(MAKEWORD(2, 2), &wsa);
    if (err < 0)
    {
        puts("WSAStartup failed !");
        exit(EXIT_FAILURE);
    }
#endif
}

static void end(void)
{
#ifdef _WIN32
    WSACleanup();
#endif
}

static void app(void)
{
    int server_socket = init_connection();
    char buffer[BUF_SIZE];
    int actual = 0;
    int max = server_socket;
    Client clients[MAX_CLIENTS];
    fd_set rdfs;

    while (1)
    {
        int i = 0;
        FD_ZERO(&rdfs);

        /* add the server socket */
        FD_SET(server_socket, &rdfs);

        /* add socket of each client */
        for (i = 0; i < actual; i++)
        {
            FD_SET(clients[i].sock, &rdfs);
        }

        if (select(max + 1, &rdfs, NULL, NULL, NULL) == -1)
        {
            perror("select()");
            exit(errno);
        }

        /* new client */
        if (FD_ISSET(server_socket, &rdfs))
        {
            int csock = accept_connection(server_socket, clients, &actual, &rdfs);
            if (csock > 0)
            {
                max = csock > max ? csock : max;
            }

            send_message_to_client(csock, "\n\n1. Get list of Clients\n2. Defy a Client\n3. Write a bio\n4. Read a bio\n5. Disconnect\n"); // Send menu
        }
        else
        {
            handle_clients(clients, &actual, &rdfs, buffer);
        }
    }

    clear_clients(clients, actual);
    end_connection(server_socket);
}

static int init_connection(void)
{
    int server_socket = socket(AF_INET, SOCK_STREAM, 0);
    struct sockaddr_in sin = {0};

    if (server_socket == -1)
    {
        perror("socket()");
        exit(errno);
    }

    sin.sin_addr.s_addr = htonl(INADDR_ANY);
    sin.sin_port = htons(PORT);
    sin.sin_family = AF_INET;

    if (bind(server_socket, (struct sockaddr *)&sin, sizeof sin) == -1)
    {
        perror("bind()");
        exit(errno);
    }

    if (listen(server_socket, MAX_CLIENTS) == -1)
    {
        perror("listen()");
        exit(errno);
    }

    return server_socket;
}

static int accept_connection(int server_socket, Client *clients, int *actual, fd_set *rdfs)
{
    struct sockaddr_in csin = {0};
    socklen_t sinsize = sizeof csin;
    int csock = accept(server_socket, (struct sockaddr *)&csin, &sinsize);
    if (csock == -1)
    {
        perror("accept()");
        return -1;
    }

    /* after connecting, the client sends its name */
    if (read_client(csock, clients[*actual].name) == -1)
    {
        /* disconnected */
        return -1;
    }

    printf("New connection from %s\n", clients[*actual].name);

    FD_SET(csock, rdfs);

    clients[*actual].sock = csock;
    clients[*actual].in_game = 0;
    clients[*actual].challenger = 0;

    (*actual)++;

    return csock;
}

static void handle_clients(Client *clients, int *actual, fd_set *rdfs, char *buffer)
{
    int i = 0;
    int buf_size = BUF_SIZE;

    for (i = 0; i < *actual; i++)
    {
        if (FD_ISSET(clients[i].sock, rdfs))
        {
            Client client = clients[i];
            int c = read_client(client.sock, buffer);

            /* client disconnected */
            if (c == 0)
            {
                disconnect_client(client, clients, actual, buffer, i);
            }
            else
            {
                if (is_valid_entry(buffer, 1, 5))
                {
                    int selection = atoi(buffer);
                    char message[BUF_SIZE];

                    switch (selection)
                    {
                    case 1: // Get list of clients
                        get_client_list(clients, i, message, actual);

                        break;

                    case 2: // Defy a client
                        // Handle challenge request
                        sscanf(buffer, "/defy %s", message);
                        int challenger_index = find_player_index_by_name(clients, *actual, message);

                        if (challenger_index != -1 && !clients[challenger_index].in_game && clients[challenger_index].challenger == 0)
                        {
                            // Accept the challenge
                            clients[i].in_game = 1;
                            clients[i].challenger = clients[challenger_index].sock;
                            clients[challenger_index].in_game = 1;
                            clients[challenger_index].challenger = clients[i].sock;

                            // Inform both players about the start of the game
                            send_message_to_client(clients[i].sock, "Challenge accepted! Game starts now.\n");
                            send_message_to_client(clients[challenger_index].sock, "Challenge accepted! Game starts now.\n");
                        }
                        else
                        {
                            // Reject the challenge
                            send_message_to_client(clients[i].sock, "Challenge rejected. The player may be in a game or has a pending challenge.\n");
                        }

                        break;

                    case 3: // Write a bio
                        send_message_to_client(client.sock, "Please write your bio :\n");

                        read_client(client.sock, buffer);

                        clients[i].bio = strdup(buffer);
                        send_message_to_client(client.sock, "Bio updated!\n");

                        break;

                    case 4: // Read a bio
                        get_client_list(clients, i, message, actual);
                        send_message_to_client(client.sock, "Please select whose bio you want to read.\n");

                        read_client(client.sock, buffer);

                        while (!is_valid_entry(buffer, 1, *actual))
                        {
                            send_message_to_client(client.sock, "Invalid entry, try again\n");
                            read_client(client.sock, buffer);
                        }

                        int selection = atoi(buffer);
                        selection--;

                        if (clients[selection].bio == NULL)
                        {
                            send_message_to_client(client.sock, "This client doesn't have a bio.\n");
                        }
                        else
                        {
                            send_message_to_client(client.sock, clients[selection].bio);
                        }

                        break;

                    case 5: // Disconnect
                        disconnect_client(client, clients, actual, buffer, i);

                        break;

                    default:
                        break;
                    }

                    send_message_to_client(clients[i].sock, "\n\n1. Get list of Clients\n2. Defy a Client\n3. Write a bio\n4. Read a bio\n5. Disconnect\n"); // Send menu
                }
                else
                {
                    send_message_to_client(clients[i].sock, "Invalid entry, try again\n");
                }
            }
        }
    }
}

static void disconnect_client(Client client, Client *clients, int *actual, char *buffer, int index)
{
    printf("%s disconnected!\n", client.name);
    if (client.in_game)
    {
        // Inform other player if in game
        int other_player_index = find_player_index_by_socket(clients, *actual, client.challenger);
        if (other_player_index != -1)
        {
            send_message_to_client(clients[other_player_index].sock, "Your opponent has disconnected. Game over.\n");
            clients[other_player_index].in_game = 0;
            clients[other_player_index].challenger = 0;
        }
    }
    close_client(clients, index, actual, buffer);
}

static void clear_clients(Client *clients, int actual)
{
    int i = 0;
    for (i = 0; i < actual; i++)
    {
        close(clients[i].sock);
    }
}

static void close_client(Client *clients, int to_remove, int *actual, char *buffer)
{
    /* remove the client from the array */
    printf("Removing client %s\n", clients[to_remove].name);
    memmove(clients + to_remove, clients + to_remove + 1, (*actual - to_remove - 1) * sizeof(Client));
    /* number of clients - 1 */
    (*actual)--;
}

static void get_client_list(Client *clients, int index, char *message, int *actual)
{
    for (int j = 0; j < *actual; j++)
    {
        snprintf(message, BUF_SIZE, "%d. %s | %sin game\n", j + 1, clients[j].name, clients[j].in_game ? "" : "not ");
        send_message_to_client(clients[index].sock, message);
    }
}

static void send_message_to_all_clients(Client *clients, Client sender, int actual, const char *buffer, char from_server)
{
    int i = 0;
    char message[BUF_SIZE];
    message[0] = 0;

    for (i = 0; i < actual; i++)
    {
        /* don't send the message to the sender */
        if (sender.sock != clients[i].sock)
        {
            if (from_server == 0)
            {
                strncpy(message, sender.name, BUF_SIZE - 1);
                strncat(message, " : ", sizeof message - strlen(message) - 1);
            }
            strncat(message, buffer, sizeof message - strlen(message) - 1);
            write_client(clients[i].sock, message);
        }
    }
}

static void send_message_to_client(int sock, const char *message)
{
    write_client(sock, message);
}

static void end_connection(int server_socket)
{
    close(server_socket);
}

static int read_client(int sock, char *buffer)
{
    int n = recv(sock, buffer, BUF_SIZE - 1, 0);
    if (n <= 0)
    {
        if (n < 0)
        {
            perror("recv()");
        }
        /* if recv error or connection closed, disconnect the client */
        return 0;
    }

    buffer[n] = '\0';
    return n;
}

static void write_client(int sock, const char *buffer)
{
    if (send(sock, buffer, strlen(buffer), 0) == -1)
    {
        perror("send()");
        exit(errno);
    }
}

static int is_valid_entry(char *buffer, int min, int max)
{
    int selection = -1;

    if (isdigit(buffer[0]))
    {
        selection = atoi(buffer);

        if (selection >= min && selection <= max)
            return 1;
    }

    return 0;
}

static int find_player_index_by_name(Client *clients, int actual, const char *name)
{
    int i;
    for (i = 0; i < actual; i++)
    {
        if (strcmp(clients[i].name, name) == 0)
        {
            return i;
        }
    }
    return -1; // Not found
}

static int find_player_index_by_socket(Client *clients, int actual, int sock)
{
    int i;
    for (i = 0; i < actual; i++)
    {
        if (clients[i].sock == sock)
        {
            return i;
        }
    }
    return -1; // Not found
}

int main(int argc, char **argv)
{
    init();
    app();
    end();
    return EXIT_SUCCESS;
}
