#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "hexagone.h"
#include "joueur.h"
#include "gamesystem.h"

#define ROW 9
#define COLUMN 9

int main() {
    srand(time(NULL));

    if (system("clear") != 0) {
        fprintf(stderr, "Error executing 'clear' command.\n");
        exit(EXIT_FAILURE);
    }

    int nbj;
    int new_x = 0, new_y = 0;

    printf("How many people will take part in the game? ");
    if (scanf("%d", &nbj) != 1 || nbj <= 0) {
        fprintf(stderr, "Misreading the number of players.\n");
        exit(EXIT_FAILURE);
    }

    Hexagone **grid = createGrid(ROW, COLUMN, nbj);
    if (grid == NULL) {
        fprintf(stderr, "Memory allocation error for grid.\n");
        exit(EXIT_FAILURE);
    }
    
    Player *tab = beginning(nbj, grid);
    if (tab == NULL) {
        fprintf(stderr, "Memory allocation error for players.\n");
        for (int i = 0; i < ROW; i++) {
            free(grid[i]);
        }
        free(grid);
        exit(EXIT_FAILURE);
    }

    if (system("clear") != 0) {
        fprintf(stderr, "Error executing the 'clear' command..\n");
        for (int i = 0; i < ROW; i++) {
            free(grid[i]);
        }
        free(grid);
        for (int i = 0; i < nbj; i++) {
            free(tab[i].name);
            free(tab[i].animals);
        }
        free(tab);
        exit(EXIT_FAILURE);
    }
    printf("Tour launch\n");
    
    
    do{
        // Game turn for each player
        turn(tab, nbj, grid, &new_x, &new_y);
        printf("%d", turn(tab, nbj, grid, &new_x, &new_y));
    }while(turn(tab, nbj, grid, &new_x, &new_y) != nbj);
        

    printf("All players are blocked. End of the game.\n");
    
    Player winner = tab[0];
    for(int i = 1; i < nbj; i++){
        if(winner.score < tab[i].score){
            winner = tab[i];
        }
    }
    int restart = -1;
    printf("the winner is %s with a score of %d\n", winner.name, winner.score);
    printf("Type 0 : Restart \n Type 1: Leave\n");
    do{
        if (scanf("%d", &restart) != 1 || nbj <= 0) {
            fprintf(stderr, "Erreur de lecture.\n");
            exit(EXIT_FAILURE);
        }
    }while(restart != 0 && restart != 1);
    if(restart == 0){
        main();
    }
    
    // Freeing allocated memory
    for (int i = 0; i < ROW; i++) {
        free(grid[i]);
    }
    free(grid);
    for (int i = 0; i < nbj; i++) {
        free(tab[i].name);
        free(tab[i].animals);
    }
    free(tab);

    return 0;
}
