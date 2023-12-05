#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <ncurses.h>

#include "client2.h"
#include "../Model/board.h"
#include "../Model/player.h"
#include "../Model/game.h"
#include "../Model/play.h"

static void init(void)
{
#ifdef WIN32
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
#ifdef WIN32
   WSACleanup();
#endif
}

static void app(const char *address, const char *name)
{
   int out = 0;
   SOCKET sock = init_connection(address);
   char buffer[BUF_SIZE];

   fd_set rdfs;

   /* send our name */
   write_server(sock, name);

   while (!out)
   {
      FD_ZERO(&rdfs);

      /* add STDIN_FILENO */
      FD_SET(STDIN_FILENO, &rdfs);

      /* add the socket */
      FD_SET(sock, &rdfs);

      if (select(sock + 1, &rdfs, NULL, NULL, NULL) == -1)
      {
         perror("select()");
         exit(errno);
      }

      /* something from standard input : i.e keyboard */
      if (FD_ISSET(STDIN_FILENO, &rdfs))
      {
         fgets(buffer, BUF_SIZE - 1, stdin);

         char *p = NULL;
         p = strstr(buffer, "\n");
         if (p != NULL)
         {
            *p = 0;
         }
         else
         {
            /* fclean */
            buffer[BUF_SIZE - 1] = 0;
         }

         write_server(sock, buffer);
      }
      else if (FD_ISSET(sock, &rdfs))
      {
         int n = read_server(sock, buffer);
         /* server down */
         if (n == 0)
         {
            printf("Server disconnected !\n");
            out = 1;
            break;
         }

         if (-1 == atoi(buffer))
         {
            printf("Disconnected !\n");
            out = 1;
            break;
         }
         else if (strncmp(buffer, "Challenge accepted! Game starts now.\n", 100) == 0)
         {
            char input[BUF_SIZE];
            char *token;
            read_server(sock, input);

            token = strtok(input, "|");
            char *player1_name = token;

            token = strtok(NULL, "|");
            char *player2_name = token;

            initscr();   // Initialise ncurses
            curs_set(0); // Masque le curseur
            clear();

            Game game = createGame(createPlayer(0, player1_name), createPlayer(1, player2_name), createBoard());

            if (strncmp(name, player1_name, 100) != 0)
            {
               showPlayer(game.actualPlayer);
               showBoard(game.board);
               printw("\nWaiting for opponent to play...\n");
               refresh();

               read_move(sock, buffer);
               game = playOpponent(game, atoi(buffer));
            }

            while (game.winner == 0)
            {
               clear();
               showPlayer(game.actualPlayer);
               showBoard(game.board);
               printw("Select a number between 1 and 6\n");
               refresh();

               game = play(game);

               clear();
               showPlayer(game.actualPlayer);
               showBoard(game.board);
               refresh();

               if (game.winner == 0)
               {
                  // Let the client handle the move and update the game
                  snprintf(buffer, BUF_SIZE, "%d", game.moves[game.numberOfMoves - 1]);
                  write_server(sock, buffer);
                  printw("\nWaiting for opponent to play...\n");
                  refresh();

                  read_move(sock, buffer);
                  game = playOpponent(game, atoi(buffer));
                  refresh();
               }
            }

            snprintf(buffer, BUF_SIZE, "%d", game.moves[game.numberOfMoves - 1]);
            write_server(sock, buffer);

            printw("End of the game.\n");
            refresh();

            sleep(3);

            endwin();

            write_server(sock, "-1");
         }
         else
            puts(buffer);
      }
   }

   end_connection(sock);
}

static int init_connection(const char *address)
{
   SOCKET sock = socket(AF_INET, SOCK_STREAM, 0);
   SOCKADDR_IN sin = {0};
   struct hostent *hostinfo;

   if (sock == INVALID_SOCKET)
   {
      perror("socket()");
      exit(errno);
   }

   hostinfo = gethostbyname(address);
   if (hostinfo == NULL)
   {
      fprintf(stderr, "Unknown host %s.\n", address);
      exit(EXIT_FAILURE);
   }

   sin.sin_addr = *(IN_ADDR *)hostinfo->h_addr;
   sin.sin_port = htons(PORT);
   sin.sin_family = AF_INET;

   if (connect(sock, (SOCKADDR *)&sin, sizeof(SOCKADDR)) == SOCKET_ERROR)
   {
      perror("connect()");
      exit(errno);
   }

   return sock;
}

static void end_connection(int sock)
{
   closesocket(sock);
}

static int read_server(SOCKET sock, char *buffer)
{
   buffer[BUF_SIZE - 1] = 0;
   int n = 0;

   if ((n = recv(sock, buffer, BUF_SIZE - 1, 0)) < 0)
   {
      perror("recv()");
      exit(errno);
   }

   buffer[n] = '\0';

   return n;
}

static int read_move(SOCKET sock, char *buffer)
{
   int n = 0;
   char temp[BUF_SIZE];

   if ((n = recv(sock, temp, BUF_SIZE - 1, 0)) < 0)
   {
      perror("recv()");
      exit(errno);
   }

   snprintf(buffer, BUF_SIZE, "%s", temp);

   while (!is_valid_entry(buffer, 0, 5))
   {
      if ((n = recv(sock, temp, BUF_SIZE - 1, 0)) < 0)
      {
         perror("recv()");
         exit(errno);
      }

      snprintf(buffer, BUF_SIZE, "%s", temp);
   }

   buffer[n] = '\0';

   return n;
}

static void write_server(SOCKET sock, const char *buffer)
{
   if (send(sock, buffer, strlen(buffer), 0) < 0)
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

int main(int argc, char **argv)
{
   if (argc < 3)
   {
      printf("Usage : %s [address] [pseudo]\n", argv[0]);
      return EXIT_FAILURE;
   }

   init();

   app(argv[1], argv[2]);

   end();

   return EXIT_SUCCESS;
}
