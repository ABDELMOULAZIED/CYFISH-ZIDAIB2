#ifndef GAMESYSTEM_H
#include "hexagone.h"
#include "joueur.h"
#define GAMESYSTEM_H
#define TAB_DEPLACEMENT_INIT                                                   \
  { "Haut", "Bas", "Bas Gauche", "Bas Droite", "Haut Gauche", "Haut Droite" }
void printHexa(int penguin);
void printHexa2(int penguin);
void printGrid(Hexagone **grid, int n, int m);
Joueur *beginning(int nbj, Hexagone **grid);
void printGame(Joueur *tab, int nbj, Hexagone **grid);
void deplacement_joueur(Pingouin p, int *new_x, int *new_y, Hexagone **grid);
void tour(Joueur *tab, int nbj, Hexagone **grid, int *new_x, int *new_y);
void choose_position_depart(Joueur *j, Hexagone **grid, int nbj);
void printGame(Joueur *tab, int nbj, Hexagone **grid);
void pingouin_bloquer(Hexagone **grid,  Pingouin p );
int verif_joueur_bloquer(Hexagone **grid, Joueur j);
#endif