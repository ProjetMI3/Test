#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "structures.h"

// Créer une carte
Carte creer_carte(int valeur, int visible) {
    Carte c;
    c.valeur = valeur;
    c.visible = visible;
    return c;
}

// Mélanger la pile de cartes
void melanger_pile(Pile* pile) {
    if (pile->top <= 1) return;  // Pas besoin de mélanger si la pile est vide ou a une seule carte.
    
    for (int i = pile->top - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        Carte temp = pile->cartes[i];
        pile->cartes[i] = pile->cartes[j];
        pile->cartes[j] = temp;
    }
}

// Initialiser la pioche avec des cartes
void initialiser_pioche(Pile* pioche) {
    pioche->top = 0;
    int quantites[3] = {5, 10, 15};

    for (int valeur = -2; valeur <= 12; valeur++) {
        int nombre = (valeur == -2) ? quantites[0] :
                     (valeur == -1) ? quantites[1] :
                     (valeur == 0)  ? quantites[2] : 10;

        for (int i = 0; i < nombre; i++) {
            Carte nouvelle = creer_carte(valeur, 0);
            pioche->cartes[pioche->top++] = nouvelle;
        }
    }

    melanger_pile(pioche);
}

// Initialiser un joueur avec un nom et une main de cartes
void initialiser_joueur(Joueur* joueur, const char* nom, Pile* pioche, int nb_cartes) {
    joueur->defausse.top = 0;
    joueur->main = malloc(nb_cartes * sizeof(Carte)); // Allocation dynamique pour les cartes du joueur

    if (!joueur->main) {
        fprintf(stderr, "Erreur d'allocation mémoire.\n");
        exit(1);
    }

    for (int i = 0; i < nb_cartes; i++) {
        if (pioche->top == 0) {
            printf("Erreur : plus de cartes dans la pioche.\n");
            exit(1);
        }
        joueur->main[i] = pioche->cartes[--pioche->top];
        joueur->main[i].visible = 0;
    }
}

// Afficher une carte
void afficher_carte(Carte c) {
    if (c.visible)
        printf("[ %2d ]", c.valeur);
    else
        printf("[ ?? ]");
}

// Afficher la main du joueur
void afficher_main(Joueur joueur, int nb_cartes) {
    for (int i = 0; i < nb_cartes; i++) {
        printf("%d: ", i);
        afficher_carte(joueur.main[i]);
        printf(" ");
    }
    printf("\n");
}

// Afficher la défausse d'un joueur
void afficher_defausse(Joueur joueur) {
    if (joueur.defausse.top > 0) {
        printf("Défausse de %s : ", joueur.nom);
        for (int i = 0; i < joueur.defausse.top; i++) {
            afficher_carte(joueur.defausse.cartes[i]);
            printf(" ");
        }
        printf("\n");
    }
}
