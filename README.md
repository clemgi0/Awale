# Awale
Programmation d’un serveur de Jeu Awalé

# Firstly

1. run sudo apt-get install libncurses5-dev libncursesw5-dev //to install the ncurses library if you don't already have it

# How to run in solo mode
2. run make clean //to clean bin folder

3. run make //to create the server executable

4. run ./bin/jeu //to run the executable named jeu

5. Enjoy :)

# To run in client & server
1. run make clean //to clean bin folder

2. run make server //to create the server executable

3. run make client //to create the client executable

4. run ./bin/server //in your server's terminal to launch the server

5. In another terminal, run ./bin/client 127.0.0.1 <pseudo> //to connect with your client to the server on local mode

6. In a third terminal, re-run ./bin/client 127.0.0.1 <pseudo> //so that you'll have to clients connected to the server and you'll be able to play