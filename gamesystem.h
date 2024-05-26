#ifndef GAMESYSTEM_H
  #include "hexagone.h"
  #include "joueur.h"
  #define GAMESYSTEM_H
  #define TAB_DEPLACEMENT_INIT { "Up", "down", "down left", "down right", "up left", "up right" }

  void printHexa(int animal); // print the emoji of the animal
  void printGrid(Hexagone **grid, int n, int m); // print the hexa grid
  Player *beginning(int nbj, Hexagone **grid); // create the table of players
  int case_sink(Hexagone hexa); //check if a hexagone has sunk
  int verifMooves(Hexagone **grid, int x1, int y1, int x2, int y2);//check if a moove is valid.
  int* testMooves(Animal p, Hexagone** grid, int direction_deplacement);
  void start_auto(Hexagone **grid,Player *tab,int nbj);
  void printGame(Player *tab, int nbj, Hexagone **grid);// print the grid and players informations
  void moove_player(Animal p, int *new_x, int *new_y, Hexagone **grid); // ask the player to move his animal
  int turn(Player *tab, int nbj, Hexagone **grid, int *new_x, int *new_y);// the turn of the player
  void choose_position_start(Player *j, Hexagone **grid, int nbj, int i);// ask the player to choose the position of his animal
  void choose_position_start2(Player *j, Hexagone **grid, int nbj, int i);
  int animal_blocked(Hexagone **grid,  Animal p );// check if a pingouin is blocked
  int player_blocked(Hexagone **grid, Player j);// check if a player is blocked
#endif
