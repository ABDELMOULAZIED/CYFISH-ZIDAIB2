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

  typedef struct Pingouin Pingouin;
  struct Pingouin{
      int x;
      int y;
      int valide; // 0 : valide, -1 : invalide 
  };
  
  typedef struct Joueur Joueur;
  struct Joueur{
    int num;
    int nbp;
    char *nom;    
    int score;
    int fpenguin;//changfement d'emoji en fonction desjoueurs
    Pingouin* pingouins;
  };

  Pingouin createPingouin();
  Joueur createJoueur(int nbj, Joueur *tab);

#endif