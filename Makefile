CC=gcc
CFLAGS=-std=c99


all: Quoridor Affichage


Affichage : affichage.o
	$(CC) $(CFLAGS) affichage.o -lncurses -o Affichage

Quoridor : serveur.o fct_annexes.o is_blockable.o main.o random.o
	$(CC) $(CFLAGS) serveur.o fct_annexes.o is_blockable.o main.o random.o -o Quoridor

affichage.o : 
	$(CC) $(CFLAGS) -c ./src/affichage/affichage.c -lncurses

serveur.o : 
	$(CC) $(CFLAGS) -c ./src/serveur.c

fct_annexes.o : 
	$(CC) $(CFLAGS) -c ./src/fct_annexes.c

is_blockable.o : 
	$(CC) $(CFLAGS) -c ./src/is_blockable.c

main.o : 
	$(CC) $(CFLAGS) -c ./src/main.c

random.o : 
	$(CC) $(CFLAGS) -c ./src/random.c


clean : 
	rm -f *.o *.aux *.log

mrproper : 
	rm -f *.o *.aux *.log Quoridor Affichage
