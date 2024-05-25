#include "joueur.h"
#include "hexagone.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NOM 50
#define PENGUIN 0
#define SHARK 1
#define DOLPHIN 2
#define EAGLE 3
#define BEAR 4
#define CROCODILE 5

Pingouin createPingouin() {
    Pingouin p;
    p.x = 0;
    p.y = 0;
    p.valide = 0;
    return p;
}

Joueur createJoueur(int nbj, Joueur *tab) {
    int tA[] = {PENGUIN, SHARK, BEAR, EAGLE, CROCODILE, DOLPHIN};
    Joueur j;
    j.score = 0;
    j.nbp = 0;
    j.nom = (char *)malloc(sizeof(char) * NOM);
    if (j.nom == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour le nom du joueur.\n");
        exit(EXIT_FAILURE);
    }

    printf("Quel est votre nom ? ");
    if (scanf("%49s", j.nom) != 1) {
        fprintf(stderr, "Erreur de lecture du nom du joueur.\n");
        free(j.nom);
        exit(EXIT_FAILURE);
    }

    // Calcul du nombre de pingouins pour ce joueur
    int pingouinsCount = (nbj < 5) ? (6 - nbj) : 1; // Ajustement de la logique
    j.pingouins = (Pingouin *)malloc(sizeof(Pingouin) * pingouinsCount);
    if (j.pingouins == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les pingouins.\n");
        free(j.nom);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < pingouinsCount; i++) {
        j.pingouins[i] = createPingouin();
        tab[i].fpenguin = tA[i % (sizeof(tA) / sizeof(tA[0]))]; // Assurez-vous de ne pas dépasser les limites du tableau tA
    }
    j.nbp = pingouinsCount;
    
    return j;
}

