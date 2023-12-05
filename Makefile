CC=gcc
CFLAGS= -Wall -Wextra -g
LDFLAGS= -lncurses
BIN=bin

# Utilisation de la fonction wildcard pour obtenir les listes des fichiers source dans les répertoires Model, Client et Server
MODELSOURCES=$(wildcard Model/*.c)
SERVERSOURCES=$(wildcard Serveur/*.c)
CLIENTSOURCES=$(wildcard Client/*.c Model/*.c)
CLIENTSOURCES := $(filter-out Model/Main.c, $(CLIENTSOURCES))
TESTSOURCES=$(wildcard *.c)

# Remplacer l'extension .c par .o pour obtenir les listes des fichiers objets
MODELOBJECTS=$(patsubst %.c,$(BIN)/%.o,$(notdir $(MODELSOURCES)))
SERVEROBJECTS=$(patsubst %.c,$(BIN)/%.o,$(notdir $(SERVERSOURCES)))
CLIENTOBJECTS=$(patsubst %.c,$(BIN)/%.o,$(notdir $(CLIENTSOURCES)))
TESTOBJECTS=$(patsubst %.c,$(BIN)/%.o,$(notdir $(TESTSOURCES)))

# La cible par défaut est "main"
all: main

# La règle pour construire l'exécutable
main: $(BIN)/jeu

$(BIN)/jeu: $(MODELOBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# La règle générique pour construire chaque fichier objet
$(BIN)/%.o: Model/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# La règle pour construire l'exécutable
server: $(BIN)/server

$(BIN)/server: $(SERVEROBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# La règle générique pour construire chaque fichier objet
$(BIN)/%.o: Serveur/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# La règle pour construire l'exécutable
client: $(BIN)/client

$(BIN)/client: $(CLIENTOBJECTS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# La règle générique pour construire chaque fichier objet
$(BIN)/%.o: Client/%.c
	$(CC) $(CFLAGS) -c $< -o $@

$(BIN)/%.o: Model/%.c
ifeq (,$(findstring Main.c,$<))
	$(CC) $(CFLAGS) -c $< -o $@
endif

# La cible pour nettoyer les fichiers générés
clean:
	rm -f $(BIN)/*