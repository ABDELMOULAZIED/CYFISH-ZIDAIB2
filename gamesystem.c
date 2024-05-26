#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "gamesystem.h"
#include "hexagone.h"
#include "joueur.h"
#define ROW 9
#define COLUMN 9
#define PENGUIN 0
#define SHARK 1
#define BEAVER 2
#define EAGLE 3
#define BEAR 4
#define CROCODILE 5

void printHexa(int animal) {
    switch (animal) {
        case -1:
            printf("  ");
            break;
        case PENGUIN:
            printf("\U0001F427");
            break;
        case SHARK:
            printf("\U0001F988");
            break;
        case BEAVER:
            printf("\U0001F9AB");
            break;
        case EAGLE:
            printf("\U0001F985");
            break;
        case BEAR:
            printf("\U0001F43B");
            break;
        case CROCODILE:
            printf("\U0001F40A");
            break;
    }
}

void printGrid(Hexagone **grid, int n, int m) {
    for (int j = 0; j < m; j++) { // The first line of [_] is displayed as a function of the number of hexagons in the display.
        if (j % 2 == 0) {
            printf("  ____  ");
        } else {
            printf("    ");
        }
    }
    printf("\n");

    for (int i = 0; i < n; i++) { //display of each hexagon line
        for (int j = 0; j < m; j++) {
            if (j % 2 == 0) {
                printf(" / %d%d \\ ", grid[i][j].x, grid[i][j].y); // floor display [/ ] for even columns
            } else {
                if (i == 0 || grid[i - 1][j].fish < 2) {
                    printf("    ");
                } else if (grid[i - 1][j].fish == 2) {
                    printf(" \U0001F41F ");
                } else if (grid[i - 1][j].fish == 3) {
                    printf("\U0001F41F\U0001F41F");
                }
            }
        }
        printf("\n");

        for (int j = 0; j < m; j++) {
            if (j % 2 == 0) { // space display or fish for even columns
                if (grid[i][j].fish == 0) {
                    printf("/ ");
                    printHexa(grid[i][j].animal);
                    printf("   \\");
                } else if (grid[i][j].fish > 0) {
                    printf("/ ");
                    printHexa(grid[i][j].animal);
                    printf("\U0001F41F \\");
                }
            } else {
                printf("____"); // floor display [____] for odd-numbered columns
            }
        }
        printf("\n");

        for (int j = 0; j < m; j++) {
            if (j % 2 == 0) { // floor display [\ /] or fish for even columns
                if (grid[i][j].fish < 2) {
                    printf("\\      /");
                } else if (grid[i][j].fish == 2) {
                    printf("\\ \U0001F41F   /");
                } else if (grid[i][j].fish == 3) {
                    printf("\\ \U0001F41F\U0001F41F /");
                }
            } else { //coordinate display for odd-numbered columns
                if (i < 8) {
                    printf(" %d%d ", grid[i][j].x, grid[i][j].y);
                } else {
                    printf("    ");
                }
            }
        }
        printf("\n");

        for (int j = 0; j < m; j++) { // floor display [\____/] for even columns
            if (j % 2 == 0) {
                printf(" \\____/ ");
            } else {
                if (i == m - 1 || grid[i][j].fish == 0) {
                    printHexa(grid[i][j].animal);
                    printf("  ");
                } else {
                    printHexa(grid[i][j].animal);
                    printf("\U0001F41F");
                }
            }
        }
        printf("\n");
    }
}
/*void start_auto(Hexagone **grid, Player *tab, int nbj) {
    int compteur = 0;
    int n;
    Hexagone *tfish = malloc(sizeof(Hexagone) * ROW * COLUMN);

    if (tfish == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour tfish.\n");
        exit(EXIT_FAILURE);
    }

    // Ajouter les hexagones avec 1 poisson à tfish
    for (int i = 0; i < ROW; i++) {
        for (int j = 0; j < COLUMN; j++) {
            if (grid[i][j].fish == 1) {
                tfish[compteur].x = grid[i][j].x;
                tfish[compteur].y = grid[i][j].y;
                compteur++;
            }
        }
    }

     //Assurez-vous que compteur n'est pas 0 pour éviter la division par 0 dans rand
    if (compteur == 0) {
        fprintf(stderr, "Aucun hexagone avec 1 poisson trouvé.\n");
        free(tfish);
        return;
    }

    // Placement automatique des animaux des joueurs
    for (int k = 0; k < nbj; k++) {
        for (int l = 0; l < tab[k].nbp; l++) {
            do {
                n = rand() % compteur;
            } while (grid[tfish[n].x][tfish[n].y].player == 0);

            grid[tfish[n].x][tfish[n].y].player = 0;
            tab[k].animals[l].x = tfish[n].x;
            tab[k].animals[l].y = tfish[n].y;
        }
    }

    // Libération de la mémoire allouée
    free(tfish);
} */

void choose_position_start2(Player *j, Hexagone **grid, int nbj, int i) {
    for (int k = 0; k < j->nbp; k++) {
        int x, y;
        do {

            x = (rand()%8)+1;
            y = (rand()%8)+1;

            //Verification of placement conditions
            if (grid[x][y].fish != 1) {
                continue;
            }
            if (grid[x][y].player == -1) {
                continue;
            }
            break; // Coordinates are valid
        } while (1);

        j->animals[k].x = x;
        j->animals[k].y = y;
        grid[x][y].player = -1;
        grid[x][y].animal = i;

        // Debug display to check coordinates
        printf("Animal %d from %s placed in (%d, %d)\n", k, j->name, x, y);
    }
    j->score++;
    printf("\n");
}


// Function to select the animal's starting position
void choose_position_start(Player *j, Hexagone **grid, int nbj, int i) {
    for (int k = 0; k < j->nbp; k++) {
        int x, y;
        do {
            printf("%s, choose a starting position for penguin %d. Enter 2 digits between 0 and %d, one at a time\n", j->name,k, ROW - 1);
            if (scanf("%d", &x) != 1) {
                fprintf(stderr, "Reading error for x.\n");
                exit(EXIT_FAILURE);
            }
            if (scanf("%d", &y) != 1) {
                fprintf(stderr, "Reading error for y.\n");
                exit(EXIT_FAILURE);
            }

            // Checking limits
            if (x < 0 || x >= ROW || y < 0 || y >= COLUMN) {
                printf("Coordinates must be between 0 and %d\n", ROW - 1);
                continue;
            }

            //Verification of placement conditions
            if (grid[x][y].fish != 1) {
                printf("You can't choose a box with more than one fish.\n");
                continue;
            }
            if (grid[x][y].player == -1) {
                printf("You cannot choose a square that is already occupied.\n");
                continue;
            }
            break; // Coordinates are valid
        } while (1);

        j->animals[k].x = x;
        j->animals[k].y = y;
        grid[x][y].player = -1;
        grid[x][y].animal = i;

        // Debug display to check coordinates
        printf("Animal %d from %s placed in (%d, %d)\n", k, j->name, x, y);
    }
    printf("\n");
}

Player* beginning(int nbj, Hexagone **grid) {
    Player* tab = malloc(sizeof(Player) * nbj);
    if (tab == NULL) {
        fprintf(stderr, "Memory allocation error for players.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nbj; i++) {
        printf("player %d : ", i + 1);
        tab[i] = createPlayer(nbj, tab);
    }
    if(system("clear") != 0){
        fprintf(stderr, "Command execution error 'clear'.\n");
        exit(EXIT_FAILURE);
    }
    printGame(tab, nbj, grid);  // Initial grid display
    int version;
    printf("Choose which version you wan't to play :\n 0 : Manual \n 1 : Automatic \n");
    do{
        if(scanf("%d", &version) != 1){
            fprintf(stderr, "Reading error.\n");
            exit(EXIT_FAILURE);  
        }
    }while(version != 0 && version != 1);
    if(version == 0){
        for (int i = 0; i < nbj; i++) {
            choose_position_start(&tab[i], grid, nbj, i);
        }
    }
    if(version == 1){
    for (int i = 0; i < nbj; i++) {
        choose_position_start2(&tab[i], grid, nbj, i);
    }    
    }
    printf("Do you want to play with an handicap\n0 : Yes\n1 : No\n");
    int h;
    do{
        if(scanf("%d", &h) != 1){
            fprintf(stderr, "Reading error.\n");fprintf(stderr, "Reading error for y.\n");
            exit(EXIT_FAILURE);  
        }
    }while(h != 0 && h != 1);
    if(h == 0){
        int nb_h;
        int player_h;
        int n ;
        printf("How many handicap do you want to play with ?\n");
        do{
            if(scanf("%d", &nb_h) != 1){
                fprintf(stderr, "Reading error.\n");fprintf(stderr, "Reading error for y.\n");
                exit(EXIT_FAILURE);  
            }
        }while(nb_h<0 || nb_h>nbj);
        for (int i = 0; i < nb_h; i++){
            printf("Which player want to have more points\n");
            do{
                if(scanf("%d", &player_h) != 1){
                    fprintf(stderr, "Reading error.\n");fprintf(stderr, "Reading error for y.\n");
                    exit(EXIT_FAILURE);  
                }
            }while(player_h<0 || player_h>nbj-1);
            printf("How much point you need\n");
            if(scanf("%d", &n) != 1){
                fprintf(stderr, "Reading error.\n");fprintf(stderr, "Reading error for y.\n");
                exit(EXIT_FAILURE);  
            }
            tab[player_h].score = n;
        }
    }
    return tab;
}

int case_sink(Hexagone hexa) {
    if (hexa.active == -1) { 
        return 0;
    } else {
        return 1;
    }
}

void moove_player(Animal p, int *new_x, int *new_y, Hexagone **grid) {
    int caseNumber;
    int directionMoove;
    const char* tab_deplacement_init[] = TAB_DEPLACEMENT_INIT;

    printf("How many hexagone do you want to advance ?\n");
    if (scanf("%d", &caseNumber) != 1) {
        printf("Input error\n");
        return;
    }

    for (int i = 0; i < 6; i++) {
        printf("type %d for: %s \n", i, tab_deplacement_init[i]);
    }
        
    if (scanf("%d", &directionMoove) != 1) {
        printf("Input error\n");
        return;
    }

    if (directionMoove < 0 || directionMoove >= 6) {
        printf("Direction of travel invalid\n");
        return;
    }
    //these variable will be used to store the new coordinates
    *new_x = p.x;
    *new_y = p.y;
    // Update the new coordinates based on the direction of movement
    for (int i = 0; i < caseNumber; i++) {
        switch (directionMoove) {
            case 0:
                // Move up
                *new_x -= 1;
                break;
            case 1:
                // Move right
                *new_x += 1;
                break;
            case 2:
                // Move down
                if (*new_y % 2 != 0) *new_x += 1;
                *new_y -= 1;
                break;
            case 3:
                // Move left
                if (*new_y % 2 != 0) *new_x += 1;
                *new_y += 1;
                break;
            case 4:
                // Move up-right
                if (*new_y % 2 == 0) *new_x -= 1;
                *new_y -= 1;
                break;
            case 5:
                // Move down-right
                if (*new_y % 2 == 0) *new_x -= 1;
                *new_y += 1;
                break;
            default:
                // Invalid direction
                printf("Error : direction of travel unknown\n");
                return;
        }
        // Check if the new coordinates are within the grid boundaries
        if (*new_x < 0 || *new_x >= ROW || *new_y < 0 || *new_y >= COLUMN || grid[*new_x][*new_y].active == -1 ||grid[*new_x][*new_y].player==-1 || ( grid[*new_x][*new_y].x == 8 &&  grid[*new_x][*new_y].y %2 == 1 )) {
            printf("Unable to move: You cross a sunken or occupied square or off the grid.\n");
            return;
        }
    }
    printf("Nouvelle position : (%d, %d)\n", *new_x, *new_y);
}

int verifMooves(Hexagone **grid, int x1, int y1, int x2, int y2) {
    if (x1 == x2 && y1 == y2) {
        printf("Unable to move: You must move at least one square..\n");
        return 1;
    }
    if (x2 < 0 || x2 >= ROW || y2 < 0 || y2 >= COLUMN) {
        printf("Unable to move: Off grid.\n");
        return 1;
    }
    if (grid[x2][y2].player == -1) {
        printf("Cannot move: This square is already occupied.\n");
        return 1;
    }
    if (grid[x2][y2].fish == 0) {
        printf("Unable to move: This square is sunk.\n");
        return 1;
    }
    if (grid[x2][y2].x == 8 && grid[x2][y2].y % 2 == 1) {
        printf("Unable to move: This square is prohibited.\n");
        return 1;
    }
    printf("Valid travel\n");
    return 0;
}

int* testMooves(Animal p, Hexagone** grid, int directionMoove) {
    //
    int caseNumber = 1;
    int new_x = p.x;
    int new_y = p.y;
    for (int i = 0; i < caseNumber; i++) {
        switch (directionMoove) {
            case 0: new_x -= 1; break;
            case 1: new_x += 1; break;
            case 2: if (new_y % 2 != 0) new_x += 1; new_y -= 1; break;
            case 3: if (new_y % 2 != 0) new_x += 1; new_y += 1; break;
            case 4: if (new_y % 2 == 0) new_x -= 1; new_y -= 1; break;
            case 5: if (new_y % 2 == 0) new_x -= 1; new_y += 1; break;
            default: printf("Error: direction of travel unknown\n"); break;
        }
    }
    static int coords[2]; // static array to return
    coords[0] = new_x;
    coords[1] = new_y;
    return coords;
}

int animal_blocked(Hexagone **grid, Animal p) {
    // Travel in every possible direction
    for (int i = 0; i < 6; i++) {
        // Calculate the new coordinates by adding the offsets
        int new_x = testMooves( p, grid, i)[0];
        int new_y = testMooves(p,grid,i)[1];

        // Check that the new coordinates are within the grid limits
        if (new_x >= 0 && new_x < ROW && new_y >= 0 && new_y < COLUMN) {
            // Check that the box at these coordinates is not cast and not occupied
            if (grid[new_x][new_y].active == 0 && grid[new_x][new_y].player != -1) {
                // If a valid square is found, the animal is not blocked.
                return 0;  // The penguin can move
            }
        }
    }

    // If none of the directions is valid, the animal is blocked.
    return 1;  // The animal can't move
}

int player_blocked(Hexagone **grid, Player j){
    for (int i = 0; i < j.nbp; i++){
        if(animal_blocked(grid, j.animals[i]) == 0){
            return 0;
        }
    }
    return 1;
}

int turn(Player *tab, int nbj, Hexagone **grid, int *new_x, int *new_y) {
    if (tab == NULL || grid == NULL || new_x == NULL || new_y == NULL) {
        fprintf(stderr, "Error: NULL pointer passed to tour function.\n");
        return 0;
    }
    int playerBlockedNumber = 0;

    for (int i = 0; i < nbj; i++) { 
        printf("Beginning of the turn for player %d: %s\n", i, tab[i].name);
        
        if (system("clear") != 0) {
            fprintf(stderr, "Erreur d'exécution de la commande 'clear'.\n");
            exit(EXIT_FAILURE);
        }
        
        printGame(tab, nbj, grid);

        if (player_blocked(grid, tab[i]) == 1) {
            printf("The %s player is blocked and can no longer play.\n", tab[i].name);
            playerBlockedNumber++;
            continue;
        }
        else {
            int k;
            printf("It's %s' turn\n", tab[i].name);
    
            // Display the coordinates of the current player's animal
            for (int j = 0; j < tab[i].nbp; j++) {
                printf("Animal %d: (%d, %d)\n", j, tab[i].animals[j].x, tab[i].animals[j].y);
            }
            // Prompt the player to choose a animal to move and the direction
            do {
                printf("Which animal do you want to move ? (0 à %d)\n", tab[i].nbp - 1);
                if (scanf("%d", &k) != 1) {
                    fprintf(stderr, "Error reading animal number.\n");
                    exit(EXIT_FAILURE);
                }
                if (k < 0 || k >= tab[i].nbp) {
                    printf("Invalid animal number. Please enter a number between 0 and %d.\n", tab[i].nbp - 1);
                }
            } while (k < 0 || k >= tab[i].nbp || tab[i].animals[k].valide == 1);
            //make the animal moove
            do {
                printf("Moving the animal%d\n", k);
                moove_player(tab[i].animals[k], new_x, new_y, grid);
                printf("New animal coordinates: (%d, %d)\n", *new_x, *new_y);
            } while (verifMooves(grid, tab[i].animals[k].x, tab[i].animals[k].y, *new_x, *new_y) != 0);

            // Update the grid and structures with the new coordinates and informations
            printf("You moved your animal well\n");
            grid[tab[i].animals[k].x][tab[i].animals[k].y].active = -1;
            grid[tab[i].animals[k].x][tab[i].animals[k].y].player = 0;
            grid[tab[i].animals[k].x][tab[i].animals[k].y].fish = 0;
            grid[tab[i].animals[k].x][tab[i].animals[k].y].animal = -1;
            tab[i].animals[k].x = *new_x;
            tab[i].animals[k].y = *new_y;
            grid[tab[i].animals[k].x][tab[i].animals[k].y].player = -1;
            grid[tab[i].animals[k].x][tab[i].animals[k].y].animal = i;
            tab[i].score += grid[tab[i].animals[k].x][tab[i].animals[k].y].fish;
            printGame(tab, nbj, grid);
        }
    }


    return playerBlockedNumber;
}

// Game status display function
void printGame(Player *tab, int nbj, Hexagone **grid) {
    for (int i = 0; i < nbj; i++) {
        printf("%s : %d points; ", tab[i].name, tab[i].score);
    }
    printf("\n");
    printGrid(grid, ROW, COLUMN);
}
