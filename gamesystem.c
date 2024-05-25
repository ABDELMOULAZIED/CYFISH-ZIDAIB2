#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "gamesystem.h"
#include "hexagone.h"
#include "joueur.h"
#define ROW 9
#define COLUMN 9

// Fonction pour afficher les emojis dans les hexagones pairs
void printHexa(int penguin) {
    switch (penguin) {
        case PENGUIN:
            printf("/\U0001F427 \U0001F41F \\");
            break;
        case SHARK:
            printf("/\U0001F988 \U0001F41F \\");
            break;
        case DOLPHIN:
            printf("/\U0001F42C \U0001F41F \\");
            break;
        case EAGLE:
            printf("/\U0001F985 \U0001F41F \\");
            break;
        case BEAR:
            printf("/\U0001F43B \U0001F41F \\");
            break;
        case CROCODILE:
            printf("/\U0001F40A \U0001F41F \\");
            break;
    }
}

// Fonction pour afficher les emojis dans les hexagones impairs
void printHexa2(int penguin) {
    switch (penguin) {
        case PENGUIN:
            printf("\U0001F427\U0001F41F");
            break;
        case SHARK:
            printf("\U0001F988\U0001F41F");
            break;
        case DOLPHIN:
            printf("\U0001F42C\U0001F41F");
            break;
        case EAGLE:
            printf("\U0001F985\U0001F41F");
            break;
        case BEAR:
            printf("\U0001F43B\U0001F41F");
            break;
        case CROCODILE:
            printf("\U0001F40A\U0001F41F");
            break;
    }
}

// Fonction pour afficher la grille hexagonale
void printGrid(Hexagone **grid, int n, int m) {
    for (int j = 0; j < m; j++) { // affichage de la première ligne de [_] en fonction du nombre d'hexagones en largeur.
        if (j % 2 == 0) {
            printf("  ____  ");
        } else {
            printf("    ");
        }
    }
    printf("\n");

    for (int i = 0; i < n; i++) { // affichage de chaque ligne d'hexagones
        for (int j = 0; j < m; j++) {
            if (j % 2 == 0) {
                printf(" / %d%d \\ ", grid[i][j].x, grid[i][j].y); // affichage de l'étage [/    \] pour les colonnes paires
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
            if (j % 2 == 0) { // affichage d'espace ou poissons pour les colonnes paires
                if (grid[i][j].fish == 0) {
                    printf("/      \\");
                } else if (grid[i][j].fish > 0) {
                    printf("/   \U0001F41F \\");
                }
            } else {
                printf("____"); // affichage de l'étage [____] pour les colonnes impaires
            }
        }
        printf("\n");

        for (int j = 0; j < m; j++) {
            if (j % 2 == 0) { // affichage de l'étage [\      /] ou poissons pour les colonnes paires
                if (grid[i][j].fish < 2) {
                    printf("\\      /");
                } else if (grid[i][j].fish == 2) {
                    printf("\\ \U0001F41F   /");
                } else if (grid[i][j].fish == 3) {
                    printf("\\ \U0001F41F\U0001F41F /");
                }
            } else { // affichage des coordonnées pour les colonnes impaires
                if (i < 8) {
                    printf(" %d%d ", grid[i][j].x, grid[i][j].y);
                } else {
                    printf("    ");
                }
            }
        }
        printf("\n");

        for (int j = 0; j < m; j++) { // affichage de l'étage [\____/] pour les colonnes paires
            if (j % 2 == 0) {
                printf(" \\____/ ");
            } else {
                if (i == m - 1 || grid[i][j].fish == 0) {
                    printf("    ");
                } else {
                    printf("  \U0001F41F");
                }
            }
        }
        printf("\n");
    }
}

// Fonction pour choisir la position de départ du pingouin
void choose_position_depart(Joueur *j, Hexagone **grid, int nbj) {
    for (int k = 0; k < j->nbp; k++) {
        int x, y;
        do {
            printf("%s, choisissez une position de départ pour pingouin %d. Entrez 2 chiffres entre 0 et %d, un par un\n", j->nom,k, ROW - 1);
            if (scanf("%d", &x) != 1) {
                fprintf(stderr, "Erreur de lecture pour x.\n");
                exit(EXIT_FAILURE);
            }
            if (scanf("%d", &y) != 1) {
                fprintf(stderr, "Erreur de lecture pour y.\n");
                exit(EXIT_FAILURE);
            }

            // Vérification des limites
            if (x < 0 || x >= ROW || y < 0 || y >= COLUMN) {
                printf("Les coordonnées doivent être entre 0 et %d\n", ROW - 1);
                continue;
            }

            // Vérification des conditions de placement
            if (grid[x][y].fish != 1) {
                printf("Vous ne pouvez pas choisir une case avec plus d'un poisson\n");
                continue;
            }
            if (grid[x][y].joueur == -1) {
                printf("Vous ne pouvez pas choisir une case déjà occupée\n");
                continue;
            }
            break; // Les coordonnées sont valides
        } while (1);

        j->pingouins[k].x = x;
        j->pingouins[k].y = y;
        grid[x][y].joueur = -1;

        // Affichage de débogage pour vérifier les coordonnées
        printf("Pingouin %d de %s placé en (%d, %d)\n", k, j->nom, x, y);
    }
}

// Fonction pour initialiser les joueurs et la grille
Joueur* beginning(int nbj, Hexagone **grid) {
    Joueur* tab = malloc(sizeof(Joueur) * nbj);
    if (tab == NULL) {
        fprintf(stderr, "Erreur d'allocation mémoire pour les joueurs.\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < nbj; i++) {
        printf("joueur %d : ", i + 1);
        tab[i] = createJoueur(nbj, tab);
    }
    printGame(tab, nbj, grid);  // Affichage initial de la grille
    for (int i = 0; i < nbj; i++) {
        choose_position_depart(&tab[i], grid, nbj);
    }
    return tab;
}

// Fonction pour vérifier si une case est coulée
int case_coulee(Hexagone **grid, int x, int y) {
    if (grid[x][y].fish == 0) {
        return 0;
    } else {
        return 1;
    }
}

// Fonction pour ajouter le score d'une case
int ajout_score(int x, int y, Hexagone **grid) {
    int score = recherche_hexa(grid, x, y)->fish;
    recherche_hexa(grid, x, y)->fish = 0;
    return score;
}

// Fonction pour déplacer un pingouin
void deplacement_joueur(Pingouin p, int *new_x, int *new_y, Hexagone **grid) {
    int nombre_de_cases;
    int direction_deplacement;
    const char* tab_deplacement_init[] = {"Haut", "Bas", "Bas Gauche", "Bas Droite", "Haut Gauche", "Haut Droite"};

    printf("De combien de cases voulez-vous avancer ?\n");
    if (scanf("%d", &nombre_de_cases) != 1) {
        printf("Erreur de saisie\n");
        return;
    }

    for (int i = 0; i < 6; i++) {
        printf("%d : %s \n", i, tab_deplacement_init[i]);
    }
    if (scanf("%d", &direction_deplacement) != 1) {
        printf("Erreur de saisie\n");
        return;
    }

    if (direction_deplacement < 0 || direction_deplacement >= 6) {
        printf("Direction de déplacement invalide\n");
        return;
    }
    *new_x = p.x;
    *new_y = p.y;

    for (int i = 0; i < nombre_de_cases; i++) {
        switch (direction_deplacement) {
            case 0:
                *new_x -= 1;
                break;
            case 1:
                *new_x += 1;
                break;
            case 2:
                if (*new_y % 2 != 0) *new_x += 1;
                *new_y -= 1;
                break;
            case 3:
                if (*new_y % 2 != 0) *new_x += 1;
                *new_y += 1;
                break;
            case 4:
                if (*new_y % 2 == 0) *new_x -= 1;
                *new_y -= 1;
                break;
            case 5:
                if (*new_y % 2 != 0) *new_x -= 1;
                *new_y += 1;
                break;
            default:
                printf("Erreur : direction de déplacement inconnue\n");
                return;
        }
        if (*new_x < 0 || *new_x >= ROW || *new_y < 0 || *new_y >= COLUMN || grid[*new_x][*new_y].active == 1) {
            printf("Déplacement impossible : Vous traversez une case coulée ou hors de la grille\n");
            return;
        }
    }
    printf("Nouvelle position : (%d, %d)\n", *new_x, *new_y);
}

// Fonction pour vérifier si le déplacement est valide
int verifDeplacement(Hexagone **grid, int x1, int y1, int x2, int y2) {
    if (x1 == x2 && y1 == y2) {
        printf("Déplacement impossible : Vous devez vous déplacer d'au moins une case.\n");
        return 1;
    }
    if (x2 < 0 || x2 >= ROW || y2 < 0 || y2 >= COLUMN) {
        printf("Déplacement impossible : Hors grille.\n");
        return 1;
    }
    if (grid[x2][y2].joueur == -1) {
        printf("Déplacement impossible : Cette case est déjà occupée.\n");
        return 1;
    }
    printf("Déplacement valide\n");
    return 0;
}

int * test_deplacement(Pingouin p, int *new_x, int *new_y, Hexagone **grid, int direction_deplacement) {
    int nombre_de_cases = 1;
    *new_x = p.x;
    *new_y = p.y;
    for (int i = 0; i < nombre_de_cases; i++) {
        switch (direction_deplacement) {
            case 0:
                *new_x -= 1;
                break;
            case 1:
                *new_x += 1;
                break;
            case 2:
                if (*new_y % 2 != 0) *new_x += 1;
                *new_y -= 1;
                break;
            case 3:
                if (*new_y % 2 != 0) *new_x += 1;
                *new_y += 1;
                break;
            case 4:
                if (*new_y % 2 == 0) *new_x -= 1;
                *new_y -= 1;
                break;
            case 5:
                if (*new_y % 2 != 0) *new_x -= 1;
                *new_y += 1;
                break;
            default:
                printf("Erreur : direction de déplacement inconnue\n");
                break;
        }

}
    int *tab[2] = {new_x, new_y};
    return *tab;
}

void pingouin_bloquer(Hexagone **grid,  Pingouin p ){
    int cpt = 0;
    for (int i = 0 ; i < 6 ; i++){
        if (grid[test_deplacement(p , &p.x , &p.y , grid , i)[0]][test_deplacement(p , &p.x , &p.y , grid , i)[1]].active == -1){
            cpt+=1;
        }
    }
    if (cpt == 6){
        p.valide =-1;
    }
    
}

int verif_joueur_bloquer(Hexagone **grid, Joueur j){
    int cpt=0;
    for (int i = 0 ; i< j.nbp ; i++){
        if (j.pingouins[i].valide ==-1){
            cpt +=1;
        }
    }
    if (cpt == j.nbp){
        return -1;
    }
    else{
        return 0;
    }
}

// Fonction pour gérer le tour d'un joueur
void tour(Joueur *tab, int nbj, Hexagone **grid, int *new_x, int *new_y) {
    for (int i = 0; i < nbj; i++) {
        int k;
        printf("C'est au tour de %s\n", tab[i].nom);

        // Afficher les coordonnées des pingouins du joueur actuel
        for (int j = 0; j < tab[i].nbp; j++) {
            printf("Pingouin %d: (%d, %d)\n", j, tab[i].pingouins[j].x, tab[i].pingouins[j].y);
        }

        // Réafficher la grille
        printGame(tab, nbj, grid);

        do {
            printf("Quel pingouin voulez-vous déplacer ? (0 à %d)\n", tab[i].nbp - 1);
            if (scanf("%d", &k) != 1) {
                fprintf(stderr, "Erreur de lecture du numéro du pingouin.\n");
                exit(EXIT_FAILURE);
            }
            if (k < 0 || k >= tab[i].nbp) {
                printf("Numéro de pingouin invalide. Veuillez entrer un numéro entre 0 et %d.\n", tab[i].nbp - 1);
            }
        } while (k < 0 || k >= tab[i].nbp);
        do {
            if(tab[i].pingouins[k].valide == -1){
                printf("Ce pingouin est bloqué, veuillez en choisir un autre\n");
            }
            printf("Quel pingouin voulez-vous déplacer ? (0 à %d)\n", tab[i].nbp - 1);
            if (scanf("%d", &k) != 1) {
                fprintf(stderr, "Erreur de lecture du numéro du pingouin.\n");
                exit(EXIT_FAILURE);
            }
        } while(tab[i].pingouins[k].valide == -1);

        do {
            deplacement_joueur(tab[i].pingouins[k], new_x, new_y, grid);
        } while (verifDeplacement(grid, tab[i].pingouins[k].x, tab[i].pingouins[k].y, *new_x, *new_y) != 0);

        printf("Vous avez bien bougé votre pingouin\n");
        tab[i].score += grid[tab[i].pingouins[k].x][tab[i].pingouins[k].y].fish;
        grid[tab[i].pingouins[k].x][tab[i].pingouins[k].y].active = 1;
        grid[tab[i].pingouins[k].x][tab[i].pingouins[k].y].joueur = 0;
        grid[tab[i].pingouins[k].x][tab[i].pingouins[k].y].fish = 0;
        tab[i].pingouins[k].x = *new_x;
        tab[i].pingouins[k].y = *new_y;
        grid[tab[i].pingouins[k].x][tab[i].pingouins[k].y].joueur = -1;
        printGame(tab, nbj, grid);
    }
}

// Fonction pour afficher l'état du jeu
void printGame(Joueur *tab, int nbj, Hexagone **grid) {
    for (int i = 0; i < nbj; i++) {
        printf("%s : %d points; ", tab[i].nom, tab[i].score);
    }
    printf("\n");
    printGrid(grid, ROW, COLUMN);
}
