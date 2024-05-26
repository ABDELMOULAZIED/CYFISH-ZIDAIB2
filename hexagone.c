#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hexagone.h"

#define ROW 9
#define COLUMN 9
#define NOM 50

Hexagone *createHexagone(int fish, int x, int y, int z,int a) {
    Hexagone *hexa = malloc(sizeof(Hexagone));
    if (hexa == NULL) {
        fprintf(stderr, "Memory allocation error for hexagon.\n");
        exit(EXIT_FAILURE);
    }
    // Assign the values to the hexagone
    hexa->x = x;
    hexa->y = y;
    hexa->fish = fish;
    hexa->active = a;
    hexa->player = 0;
    hexa->animal = z;
    return hexa;
}

Hexagone **createGrid(int n, int m, int nbj) {
    Hexagone **grid = malloc(n * sizeof(Hexagone *));
    if (grid == NULL) {
        fprintf(stderr, "Memory allocation error for grid.\n");
        exit(EXIT_FAILURE);
    }
    // Create the grid
    for (int i = 0; i < n; i++) {
        grid[i] = malloc(m * sizeof(Hexagone));
        if (grid[i] == NULL) {
            fprintf(stderr, "Memory allocation error for grid.\n");
            for (int k = 0; k < i; k++) {
                free(grid[k]);
            }
            free(grid);
            exit(EXIT_FAILURE);
        }
        // Initialize the grid with hexagones
        int tab[3];
        switch(nbj)
            {
                case 2:
                    tab[0] = (rand() % 77-8) + 8;
                    tab[1] = (rand() % 77-tab[0]) ;
                    tab[2] = 77 - tab[0] - tab[1];
                    break;
                case 3:
                    tab[0] = (rand() % 77-9) + 9;
                    tab[1] = (rand() % 77-tab[0]) ;
                    tab[2] = 77 - tab[0] - tab[1];
                    break;
                case 4:
                    tab[0] = (rand() % 77-8) + 8;
                    tab[1] = (rand() % 77-tab[0]) ;
                    tab[2] = 77 - tab[0] - tab[1];
                    break;
                case 5:
                    tab[0] = (rand() % 77-5) + 5;
                    tab[1] = (rand() % 77-tab[0]) ;
                    tab[2] = 77 - tab[0] - tab[1];
                    break;
                case 6:
                    tab[0] = (rand() % 77-6) + 6;
                    tab[1] = (rand() % 77-tab[0]) ;
                    tab[2] = 77 - tab[0] - tab[1];
                    break; 
            }

        // Assign a random number of fish to each hexagone
        for (int j = 0; j < m; j++) {
            int fish;
            do{
                fish = (rand() % 3) + 1;
            }while(tab[fish-1]==0);
            if(i == 8 && j%2 !=0){
                grid[i][j] = *createHexagone(0, i, j, -1,-1);
            }
            else{
                grid[i][j] = *createHexagone(fish, i, j, -1,0);
            }
            
        }
    }
    return grid;
}

void printInformationGrid(Hexagone **grid, int n, int m) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            printf("number of fish : %d, abscissa : %d, ordinate : %d\n",
                   grid[i][j].fish, grid[i][j].x, grid[i][j].y);
        }
    }
}

