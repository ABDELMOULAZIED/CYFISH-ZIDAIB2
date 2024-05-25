all: exec

joueur.o: joueur.c joueur.h hexagone.h
	gcc -c joueur.c -o joueur.o

hexagone.o: hexagone.c hexagone.h 
	gcc -c hexagone.c -o hexagone.o

gamesystem.o: gamesystem.c gamesystem.h hexagone.h joueur.h
	gcc -c gamesystem.c -o gamesystem.o 

main.o: main.c hexagone.h joueur.h gamesystem.h
	gcc -c main.c -o main.o

exec: main.o hexagone.o joueur.o gamesystem.o
	gcc main.o hexagone.o joueur.o gamesystem.o -o exec
