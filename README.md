# Awale
Programmation d’un serveur de Jeu Awalé

# How to run
1. run sudo apt-get install libncurses5-dev libncursesw5-dev //to install the ncurses library

2. run make clean //to destroy old bin files

3. run make //to create the executable

4. run ./bin/prog //to run the executable named prog

5. run gcc -g Serveur/server2.c -o bin/server //to open the server in one terminal

6. run (in another terminal) .bin/client 127.0.0.1 <pseudo-player1>  //to connect the first player to the server

7. run (in another terminal) .bin/client 127.0.0.1 <pseudo-player2>  //to connect the second player to the server

8. Enjoy the game :) 