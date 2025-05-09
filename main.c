#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "structures.h"
#include "fonctions.h"
#include "jouer_partie.h"

int main() {
    srand(time(NULL));  // Initialisation du générateur de nombres aléatoires
    int nb_joueurs, nb_cartes;

    printf("Bienvenue sur CardYard (version française) !\n");
    printf("VARIANTE ACTIVE : Nombre de cartes personnelles défini par l'utilisateur (CARD_USER).\n\n");

    // Demande du nombre de joueurs
    do {
        printf("Entrez le nombre de joueurs (entre 2 et 8) : ");
        if (scanf("%d", &nb_joueurs) != 1) {
            while (getchar() != '\n'); // vide le buffer
            nb_joueurs = -1; // force la répétition
        }

        if (nb_joueurs < 2 || nb_joueurs > 8) {
            fprintf(stderr, "Entrée invalide.\n");
        }
    } while (nb_joueurs < 2 || nb_joueurs > 8);

    // Variante CARD_USER : Choix du nombre de cartes personnelles
    do {
        printf("Combien de cartes personnelles voulez-vous distribuer à chaque joueur ? (1 à 10) : ");
        if (scanf("%d", &nb_cartes) != 1) {
            while (getchar() != '\n'); // vide le buffer
            nb_cartes = -1; // force la répétition
            fprintf(stderr, "Entrée invalide.\n");
            continue;
        }
        if (nb_cartes < 1 || nb_cartes > 10) {
            fprintf(stderr, "Entrée invalide.\n");
        }
    } while (nb_cartes < 1 || nb_cartes > 10);

    Joueur joueurs[NB_JOUEURS_MAX];
    Pile pioche;
    initialiser_pioche(&pioche);

    // Initialisation des joueurs
    for (int i = 0; i < nb_joueurs; i++) {
        char nom_temp[256];
        printf("Nom du joueur %d : ", i + 1);
        scanf("%255s", nom_temp);
        joueurs[i].nom = malloc(strlen(nom_temp) + 1);
        if (!joueurs[i].nom) {
            fprintf(stderr, "Erreur d'allocation mémoire.\n");
            exit(1);
        }
        strcpy(joueurs[i].nom, nom_temp);
        initialiser_joueur(&joueurs[i], nom_temp, &pioche, nb_cartes);
    }

    // Démarrer la partie
    jouer_partie(joueurs, nb_joueurs, &pioche, nb_cartes);

    // Libérer la mémoire allouée pour les joueurs
    for (int i = 0; i < nb_joueurs; i++) {
        free(joueurs[i].nom);
        free(joueurs[i].main);  // Libérer les cartes du joueur
    }

    return 0;
}
