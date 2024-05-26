#ifndef JOUEUR_H
  #include <stdlib.h>
  #include "hexagone.h"
  #define JOUEUR_H
  #define NOM 50
  #define PENGUIN 0
  #define SHARK 1
  #define DOLPHIN 2
  #define EAGLE 3
  #define BEAR 4
  #define CROCODILE 5

  typedef struct Animal Animal;
  struct Animal{
      int x;
      int y;
      int valide; // 0 : valide, -1 : invalide 
  };
  
  typedef struct Player Player;
  struct Player{
    int num;
    int nbp;
    char *name;    
    int score;
    int fanimal;//the form of the emojie
    Animal* animals;
  };

  Animal createAnimal();//create an animal
  Player createPlayer(int nbj, Player *tab);//create a player

#endif
