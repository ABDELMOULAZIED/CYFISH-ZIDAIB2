#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hexagone.h"
#include "joueur.h"
#include "gamesystem.h"

#define PENGUIN 0
#define SHARK 1
#define DOLPHIN 2
#define EAGLE 3
#define BEAR 4
#define CROCODILE 5
#define ROW 9
#define COLUMN 9

int main() {
    srand(time(NULL));

    int nbj;
    int new_x = 0, new_y = 0; // Initialisation des coordonnées

    printf("Combien de personnes vont participer au jeu ? ");
    if (scanf("%d", &nbj) != 1 || nbj <= 0) {
        fprintf(stderr, "Erreur de lecture du nombre de joueurs.\n");
        exit(EXIT_FAILURE);
    }

    Hexagone *tabDisable = malloc(sizeof(Hexagone) * 8);
    if (tabDisable == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour tabDisable.\n");
        exit(EXIT_FAILURE);
    }

    Hexagone **grid = createGrid(ROW, COLUMN, nbj);
    if (grid == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour la grille.\n");
        free(tabDisable);
        exit(EXIT_FAILURE);
    }

    Joueur *tab = beginning(nbj, grid);
    if (tab == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les joueurs.\n");
        for (int i = 0; i < ROW; i++) {
            free(grid[i]);
        }
        free(grid);
        free(tabDisable);
        exit(EXIT_FAILURE);
    }

    printf("Lancement du tour\n");
    int cpt;
    while(cpt!=nbj){
        cpt = 0;
    for (int i = 0 ; i<nbj ; i++){
        if(verif_joueur_bloquer(grid, tab[i])==-1){
            cpt +=1;
        }
    }
        tour(tab, nbj, grid, &new_x, &new_y);
    }
    

    // Libération de la mémoire allouée
    for (int i = 0; i < ROW; i++) {
        free(grid[i]);
    }
    free(grid);
    free(tabDisable);
    for (int i = 0; i < nbj; i++) {
        free(tab[i].nom);
        free(tab[i].pingouins);
    }
    free(tab);

    return 0;
}
