#include "utils.h"
#include <stdlib.h>
#include <stdio.h>
#include <signal.h>
#include <ctype.h>
#include <unistd.h>


//Valeur du semaphore 0
struct sembuf semWait = {0,0,SEM_UNDO};

//Incrémente le semaphore pour le bloquer
struct sembuf semDo = {0,1,SEM_UNDO|IPC_NOWAIT};

//Décrémente le semaphore pour le débloquer
struct sembuf semPost = {0,-1,SEM_UNDO|IPC_NOWAIT};

//Valeur du semaphore 0
struct sembuf semWait1 = {1,0,SEM_UNDO};

//Incrémente le semaphore pour le bloquer
struct sembuf semDo1 = {1,1,SEM_UNDO|IPC_NOWAIT};

//Décrémente le semaphore pour le débloquer
struct sembuf semPost1 = {1,-1,SEM_UNDO|IPC_NOWAIT};

//Valeur du semaphore 0
struct sembuf semWait2 = {2,0,SEM_UNDO};

//Incrémente le semaphore pour le bloquer
struct sembuf semDo2 = {2,1,SEM_UNDO|IPC_NOWAIT};

//Décrémente le semaphore pour le débloquer
struct sembuf semPost2 = {2,-1,SEM_UNDO|IPC_NOWAIT};

//Change les heures en secondes
double transfHourInSec = 3600;


int generateRandom(int min_number, int max_number){
	int rand_num = rand()%(max_number + 1 - min_number) + min_number;
	return rand_num;
}

int pitStop(int i) {
	int timeStop = 0; // Temps passé au pit stop
	
	// 15% de chance de s'arrêter au pit stop
	if (generateRandom(0, 99) > 84) {
		cars[i].inStand ++; //Incrémente le nombre d'arrêts au stand de la voiture
		timeStop += (generateRandom(24, 40)/10.0);
	}
	
	// obligation de s'arrêter au stand au moins une fois par course
	if (cars[i].inStand == 0 && cars[i].numCircuit == nbrLapMax){
		cars[i].inStand ++; //Incrémente le nombre d'arrêts au stand de la voiture
		timeStop += (generateRandom(24, 40)/10.0);
	}
	
	return timeStop;
}

void crash(int index)
{	//0 = pas de crash
	if (generateRandom(0, 999) > 998) { // 3% de chance de crash
		cars[index].isOut = 1; //1=crash
	}
}

double getCurrTime()
{
	double curr = 0;
	for(int i=0; i<20; i++)
	{
		if(cars[i].currTime>curr)
		{
			curr = cars[i].currTime;
		}
	}
	return curr;
}

int nbrLaps(int km)
{
	int nbr = 70;			// Nombre de tours par défaut
	int lengthMinRace = 305;	// Taille de course minimale
	if(km == 0)  //Si l'utilisateur ne rentre pas de nombre pour les kilomètres
	{
		return nbr;
	}
	if(lengthMinRace % km == 0)
	{
		nbr = lengthMinRace/km;
	}
	else
	{
		nbr = 1 + (lengthMinRace/km);
	}
	return nbr;
}

int indexOf(int i, int length, int t[])
{
	for(int j=0; j<length; j++)
	{
		if(i==t[j])
		{
			return j;
		}
	}
	//Si le pid n'est pas dans le tableau, on return la taille du tableau pour la recherche d'erreurs
	return length;
}

int isIn(int name, int length, structCar t[])
{
	int k=0;
	for(int j=0; j<length; j++)
	{
		if(name==t[j].name)
		{
			k=1;
			break;
		}
	}
	return k;
}

void generateTimeS1(int i)
{
	semop(id_sem, &semWait, 1);
	semop(id_sem, &semDo, 1);
	double lengthPercent = 0.28;
	double time;
	
	if(!(isRace == 1 && cars[i].numCircuit == 0)){
		cars[i].currCircuit = 0.0;  //remet à 0 le temps pour le tour courant
	}
	
	double averageSpeed = (double)(generateRandom(3450, 3750)/10);
	
	crash(i);
	
	if(cars[i].isOut == 0){
		time = lengthPercent*lengthCircuit /(averageSpeed/transfHourInSec); // performance en secondes pour ce secteur
		
		// Ajout du temps
		cars[i].currCircuit += time;
		cars[i].currTime += time;
		
		// Changement du meilleur temps si le nouveau temps est mieux
		if(cars[i].bestS1 < 1 || time < cars[i].bestS1){
			cars[i].bestS1 = time;
		}
	}
	semop(id_sem, &semPost, 1);
}

void generateTimeS2(int i)
{
	semop(id_sem, &semWait, 1);
	semop(id_sem, &semDo, 1);
	double lengthPercent = 0.33;
	double time;
	
	double averageSpeed = (double)(generateRandom(3000, 3640)/10);
	
	crash(i);
	
	if(cars[i].isOut == 0){
		time = lengthPercent * lengthCircuit / ( averageSpeed / transfHourInSec ); 
		
		cars[i].currCircuit += time;
		cars[i].currTime += time;
		
		if(cars[i].bestS2 < 1 || time < cars[i].bestS2){
			cars[i].bestS2 = time;
		}
	}
	semop(id_sem, &semPost, 1);
}

void generateTimeS3(int i)
{
	semop(id_sem, &semWait, 1);
	semop(id_sem, &semDo, 1);
	double lengthPercent = 0.39;
	double time;
	
	double averageSpeed = (double)(generateRandom(3200, 3550)/10);
	
	crash(i);
	
	if(cars[i].isOut == 0){
		time = lengthPercent * lengthCircuit / ( averageSpeed / transfHourInSec );
		time += (double)pitStop(i);

		cars[i].currCircuit += time;
		cars[i].currTime += time;

		if(cars[i].bestS3 < 1 || time < cars[i].bestS3){
			cars[i].bestS3 = time;
		}
		
		if(cars[i].bestCircuit < 1 || cars[i].currCircuit < cars[i].bestCircuit){
			cars[i].bestCircuit= cars[i].currCircuit;
		}
	}
	semop(id_sem, &semPost, 1);
	sleep(1);
}

char askAction()
{
	char c;
	char s[100];
	do
	{
		puts("What do you want to do?");
		puts("[C]ontinue or [S]top?");
		
		if (fgets(s, 100, stdin) == NULL)
		{
			fprintf(stderr, "erreur lors de la lecture");
			exit(EXIT_FAILURE);
		}
		
		sscanf(s, "%c", &c);
		c = tolower(c);
	} while (c != 'c'
			 && c != 's');
	
	return c;
}
//Imprime à l'écran le résultat actuel de la course
/*void printResult() {

		printf("\n\n\n\n\nPractice %i :\n\n", o);
		printf("\n| N Voiture |     Top  S1    |     Top  S2    |     Top  S3    |    Top  Tour     |    Temps Global    |\n");
		for (int i = 0; i < 20; i++) {
			printf("|     %2d    |   %9f s  |   %9f s  |   %9f s  |    %9f s   |    %4.6f s   |\n", temp[i].name, temp[i].bestS1, temp[i].bestS2, temp[i].bestS3, temp[i].bestCircuit, temp[i].currTime);
		}
		sleep(1);
}*/
void interaction(int i)
{
	char c = askAction();
	if(c=='c')
	{
		semop(id_sem, &semWait1, 1);
		semop(id_sem, &semDo1, 1);
		smv[i]=0;
		semop(id_sem, &semPost1, 1);
	}
	else
	{
		killChildren();
		exit(0);
	}
}

void killChildren()
{
	for(int i=1; i<21; i++)
	{
		//envoie un signal pour kill pidList[i]
		kill(pidList[i], SIGKILL);
	}
}

void wakeChildren()
{
	for(int i=1; i<21; i++)
	{
		//envoie un signal pour kill pidList[i]
		kill(pidList[i], SIGCONT);
	}
}


void sortRace(structCar carsQualif[], int sizeArrayCars)
{
	int i=0;
	structCar tmpCar;
	int j = 0;
	
	for(i=0; i < sizeArrayCars; i++)
		//Rempli l'array
	{
		for(j = i+1; j < sizeArrayCars; j++)
			//Vérifie qu'il n'y a pas de valeur plus petite
		{
			if((carsQualif[j].currTime < carsQualif[i].currTime)&&(carsQualif[j].isOut==0))
			{
				//Si true, swap
				tmpCar = carsQualif[i];
				carsQualif[i] = carsQualif[j];
				carsQualif[j] = tmpCar;
			}
		}
	}
}

void addTimeByPosition()
{
	for (int j = 0; j < 20; j++)
	{
		for(int i = 0; i < 20; i++)
		{
			if (cars[i].name == startPosition[j]){
				cars[i].currTime += j * 0.3;      
				cars[i].currCircuit = j * 0.3; 
			}
		}
	}
}

void setOut(int q)
{
	if(q==2)
	{
		for(int i=0; i<20; i++)
		{
			int j = isIn(cars[i].name, 15, carsQualif2);
			//si la voiture n'est pas dans carsQualif2, on la disqualifie
			if(j==0)
			{
				cars[i].isOut=1;
			}
		}
	}
	else
	{
		for(int i=0; i<20; i++)
		{
			int j = isIn(cars[i].name, 10, carsQualif3);
			//si la voiture n'est pas dans carsQualif3, on la disqualifie
			if(j==0)
			{
				cars[i].isOut=1;
			}
		}
	}
}


