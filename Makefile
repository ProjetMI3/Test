# Nom du compilateur
CC = gcc

# Drapeaux de compilation
CFLAGS = -Wall -Wextra -g

# Dossier contenant les fichiers objets
OBJDIR = obj

# Dossier des fichiers sources
SRCDIR = src

# Dossier des fichiers d'en-tête
INCDIR = include

# Nom du fichier exécutable
EXEC = jeu_cartes

# Fichiers sources
SRC = $(SRCDIR)/main.c $(SRCDIR)/fonctions.c $(SRCDIR)/jouer_partie.c

# Fichiers objets (correspondants aux fichiers sources)
OBJ = $(SRC:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Cibles principales
all: $(EXEC)

# Création du dossier obj si nécessaire
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Règle pour créer l'exécutable
$(EXEC): $(OBJ)
	$(CC) $(OBJ) -o $(EXEC)

# Règle pour compiler les fichiers .c en .o
$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS) -I$(INCDIR) -c $< -o $@

# Cible de nettoyage
clean:
	rm -rf $(OBJDIR) $(EXEC)

# Cible pour nettoyer les fichiers objets uniquement
clean-obj:
	rm -rf $(OBJDIR)

# Cible pour nettoyer l'exécutable
clean-exec:
	rm -f $(EXEC)

# Cible pour recompiler entièrement
rebuild: clean all

