CFLAGS = -Wall -std=c99 -g

	objects = beale.o listadelista.o arqchaves.o codifica.o decodifica.o

CC = gcc

all: beale

beale : beale.o listadelista.o arqchaves.o codifica.o decodifica.o
	$(CC) -o beale beale.o listadelista.o arqchaves.o codifica.o decodifica.o

beale.o: beale.c listadelista.h arqchaves.h codifica.h decodifica.h
	$(CC) -c beale.c

listadelista.o: listadelista.c listadelista.h
	$(CC) -c listadelista.c

arqchaves.o: arqchaves.c arqchaves.h
	$(CC) -c arqchaves.c

codifica.o: codifica.c codifica.h
	$(CC) -c codifica.c

decodifica.o: decodifica.c decodifica.h
	$(CC) -c decodifica.c	

clean:
	rm -rf $(objects)

purge:
	rm -rf $(objects) beale