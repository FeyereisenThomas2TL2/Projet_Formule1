#ifndef utils_h
#define utils_h
//#include "voiture.h"
#include <sys/types.h>
#include <sys/time.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <signal.h>

typedef struct structCar {//déclaration de la structure d'une voiture
	int name;           
	double bestCircuit; 
	double bestS1;      
	double bestS2;      
	double bestS3;      
	int numCircuit;     
	double currTime;    
	double currCircuit; 
	int inStand;
	int isOut;
}structCar;

//déclaration des variables utiles
int nbrLapMax;
int lengthCircuit;
structCar *cars;
int *smv;//Tableau des variables globales partagées par tous les processus
int *pidList;
int id_sem;
structCar *carsQualif2;
structCar *carsQualif3;
int startPosition[20];//Ajouter le numéro des voitures
int isRace;//Booleen dans le but de savoir si on est en course ou pas

//Structures des sémaphores utilisées
extern struct sembuf semWait;
extern struct sembuf semDo;
extern struct sembuf semPost;
extern struct sembuf semWait1;
extern struct sembuf semDo1;
extern struct sembuf semPost1;
extern struct sembuf semWait2;
extern struct sembuf semDo2;
extern struct sembuf semPost2;

//déclaration des fonctions utiles
int generateRandom(int min_number, int max_number);
int pitStop(int i);
void crash(int index);
double getCurrTime();//temps maximum des voitures
int nbrLaps(int km);
int indexOf(int i, int length, int t[]);//faire correspondre pId et numVoiture
int isIn(int name, int length, structCar t[]);//vérification si la voiture est dans le tableau
void generateTimeS1(int i);
void generateTimeS2(int i);
void generateTimeS3(int i);
char askAction();//demande si continue ou stop
void interaction(int i);//demande à l'utilisateur s'il faut arreter le processus
void killChildren();
void wakeChildren();
void sortRace(structCar carsQualif[], int sizeArrayCars);//trier les voitures sur base de leur temps actuel
void addTimeByPosition();//ajout de temps en fonction de la position
void setOut(int q);//modifier les variables des voitures à 1

void practice(int index, int p);
void generateRecapFilePractice();
void sortCarsByCurrTime(structCar carsRace[]);
void race(int index);
void generateRecapFileRace();


void sortCars(structCar carsQualif[], int sizeArrayCars);//trie les voitures pour la qualification
void buildStartPosition(structCar carsQualif[], int q);//on place les voitures sur la ligne de départ
void qualif(int index, int q);
void generateRecapFileQualif();//feuille de résultats des qualifs

void init(int i, int name);//initialisation
void reset(int i);//reinitialise le score des voitures

#endif // utilitaire_h 
