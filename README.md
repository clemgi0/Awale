# Awale
Programmation d’un serveur de Jeu Awalé

# How to run
1. run sudo apt-get install libncurses5-dev libncursesw5-dev //to install the ncurses library

2. run make clean //to destroy old bin files

3. run make //to create the executable

4. run ./bin/prog //to run the executable named prog
To run client et server
1. run make clean
2. run make
3. run gcc -g Serveur/server2.c -o bin/server
4. run gcc -g Serveur/server2.c -o bin/server
5. run ./bin/server
6. in another terminal, run ./bin/client 127.0.0.1 <pseudo>