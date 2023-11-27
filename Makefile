CC=gcc
CFLAGS= -Wall -Wextra -g
LDFLAGS= -lncurses
BIN=bin
EXECUTABLE=prog
TEST=test

# Utilisation de la fonction wildcard pour obtenir la liste des fichiers source dans le répertoire Model
SOURCES=$(wildcard Model/*.c)

# Remplacer l'extension .c par .o pour obtenir la liste des fichiers objets
OBJECTS=$(patsubst %.c,$(BIN)/%.o,$(notdir $(SOURCES)))

# La cible par défaut est "main"
all: main

# La règle pour construire l'exécutable
main: $(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ Main.c $^ $(LDFLAGS)

# La règle générique pour construire chaque fichier objet
$(BIN)/%.o: Model/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# La règle pour construire l'exécutable
test: $(BIN)/$(TEST)

$(BIN)/$(TEST): $(OBJECTS)
	$(CC) $(CFLAGS) -o $@ TestMain.c $^ $(LDFLAGS)

# La règle générique pour construire chaque fichier objet
$(BIN)/%.o: Model/%.c
	$(CC) $(CFLAGS) -c $< -o $@

# La cible pour nettoyer les fichiers générés
clean:
	rm -f $(BIN)/$(EXECUTABLE) $(OBJECTS) bin/Main.o bin/TestMain.o bin/test