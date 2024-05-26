#ifndef HEXAGONE_H
#define HEXAGONE_H

typedef struct {
    int x, y;
    int fish;
    int active;
    int player;
    int animal;
} Hexagone;

Hexagone *createHexagone(int fish, int x, int y, int z, int a);//this function creates an element of the structure hexagone.
Hexagone **createGrid(int n, int m, int nbj);//this function creates an array of elements of the structure hexagone.
void printInformationGrid(Hexagone **grid, int n, int m);//this function allows you to print the information of the hexagone.


#endif
