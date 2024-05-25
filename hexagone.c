#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hexagone.h"

#define ROW 9
#define COLUMN 9
#define NOM 50

// Cette fonction permet de créer un élément de la structure hexagone.
Hexagone *createHexagone(int fish, int x, int y, int z) {
    Hexagone *hexa = malloc(sizeof(Hexagone));
    if (hexa == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour l'hexagone.\n");
        exit(EXIT_FAILURE);
    }
    hexa->x = x;
    hexa->y = y;
    hexa->fish = fish;
    hexa->active = 0;
    hexa->joueur = 0;
    hexa->penguin = z;
    return hexa;
}

// Cette fonction permet de créer un tableau d'éléments de la structure hexagone.
Hexagone **createGrid(int n, int m, int nbj) {
    Hexagone **grid = malloc(n * sizeof(Hexagone *));
    if (grid == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour la grille.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < n; i++) {
        grid[i] = malloc(m * sizeof(Hexagone));
        if (grid[i] == NULL) {
            fprintf(stderr, "Erreur d'allocation mémoire pour la grille.\n");
            for (int k = 0; k < i; k++) {
                free(grid[k]);
            }
            free(grid);
            exit(EXIT_FAILURE);
        }
        int tab[3];
        switch(nbj)
            {
                case 2:
                    tab[0] = (rand() % 77) + 8;
                
            }
        for (int j = 0; j < m; j++) {
            int fish = (rand() % 3) + 1;
            grid[i][j] = *createHexagone(fish, i, j, 0);
        }
    }
    return grid;
}

Hexagone *recherche_hexa(Hexagone **grid, int x, int y) {
    if (x < 0 || x >= ROW || y < 0 || y >= COLUMN) {
        return NULL;
    }
    return &grid[x][y];
}

// Cette fonction va afficher les infos contenues dans la grille d'hexagones.
void printInformationGrid(Hexagone **grid, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("nombre de poissons : %d, abscisse : %d, ordonnée : %d\n",
                   grid[i][j].fish, grid[i][j].x, grid[i][j].y);
        }
    }
}

// Cette procédure va permettre d'afficher la grille hexagonale avec les poissons dedans en fonction des infos de chaque hexagone.
