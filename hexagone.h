#ifndef HEXAGONE_H
#define HEXAGONE_H

typedef struct {
    int x, y;
    int fish;
    int active;
    int joueur;
    int penguin;
} Hexagone;

Hexagone *createHexagone(int fish, int x, int y, int z);
Hexagone **createGrid(int n, int m, int nbj);
Hexagone *recherche_hexa(Hexagone **grid, int x, int y);
void printInformationGrid(Hexagone **grid, int n, int m);


#endif
