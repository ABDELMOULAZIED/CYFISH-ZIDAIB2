#include "joueur.h"
#include "hexagone.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NAME 50
#define PENGUIN 0
#define SHARK 1
#define DOLPHIN 2
#define EAGLE 3
#define BEAR 4
#define CROCODILE 5

Animal createAnimal() {
    Animal p;
    p.x = 0;
    p.y = 0;
    p.valide = 0;
    return p;
}

Player createPlayer(int nbj, Player *tab) {
    int tA[] = {PENGUIN, SHARK, BEAR, EAGLE, CROCODILE, DOLPHIN};
    Player j;
    j.score = 0;
    j.nbp = 0;
    j.name = (char *)malloc(sizeof(char) * NAME);
    if (j.name == NULL) {
        fprintf(stderr, "Memory allocation error for player name.\n");
        exit(EXIT_FAILURE);
    }

    printf("What is your name? ? ");
    if (scanf("%49s", j.name) != 1) {
        fprintf(stderr, "Error reading player name.\n");
        free(j.name);
        exit(EXIT_FAILURE);
    }

    // Calculating the number of penguins for this player
    int animalsCount;
    if (nbj < 5) {
        animalsCount = 6 - nbj;
    } else {
        animalsCount = 1;
    }
    j.animals = (Animal *)malloc(sizeof(Animal) * animalsCount);
    if (j.animals == NULL) {
        fprintf(stderr, "Memory allocation error for penguins.\n");
        free(j.name);
        exit(EXIT_FAILURE);
    }
    // Initializing the animals array
    for (int i = 0; i < animalsCount; i++) {
        j.animals[i] = createAnimal();
        tab[i].fanimal = tA[i % (sizeof(tA) / sizeof(tA[0]))]; 
    }
    j.nbp = animalsCount;
    
    return j;
}

