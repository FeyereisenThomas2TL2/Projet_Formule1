CC=gcc -Wall -Werror -std=gnu99

all: main.o utils.o voiture.o essais.o qualifs.o course.o
	$(CC) -o main main.o utils.o voiture.o essais.o qualifs.o course.o

main.o: main.c
	$(CC) -c main.c

essais.o: essais.c
	$(CC) -c essais.c

qualifs.o: qualifs.c
	$(CC) -c qualifs.c
course.o: course.c
	$(CC) -c course.c

utilitaire.o: utilitaire.c
	$(CC) -c utilitaire.c

voiture.o: voiture.c
	$(CC) -c voiture.c

clean:
	rm -f *.o manageTime voiture utils main *.gch rapport.out rapport.aux rapport.log rapport.toc *.txt main
