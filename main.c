//#include "voiture.h"
#include "utils.h"
//#include "essais.h"
//#include "qualifs.h"
//#include "course.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include <time.h>
#include <sys/time.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <errno.h>
#include <signal.h>


int myGlobalStaticContinueVariable;

void handleSignal(int sig) {
	myGlobalStaticContinueVariable = 1;
}

void worker(int nprocesses)
{
	int pid;
	isRace = 0;
	if(getpid()==pidList[0] && nprocesses==0) //=> processus parent après tous les fork()
	{
		
		//Début de practice 1
		//le parent sleep() jusqu'à ce que tous les enfants aient finis
		structCar temp[20];
		while(smv[0]!=20)
		{
			id_sem = semop(id_sem, &semWait, 1);
			id_sem = semop(id_sem, &semDo, 1);
			for(int i =0; i<20; i++)
			{
				temp[i]=cars[i];
			}
			id_sem = semop(id_sem, &semPost, 1);
			sortCars(temp, 20);
			printf("\n\n\n\n\nPractice 1 :\n\n");
			printf("\n| N Voiture |     Best S1    |     Best S2    |     Best S3    |    Best Tour     |    Global time   |\n");
			for(int i = 0; i < 20; i++){
				printf("|     %2d    |   %9f s  |   %9f s  |   %9f s  |    %9f s   |    %9f s   |\n", temp[i].name,temp[i].bestS1,temp[i].bestS2,temp[i].bestS3,temp[i].bestCircuit,temp[i].currTime);
			}
			sleep(1);
		}
		
		//Les voitures ont terminé le practice donc on génère le fichier récap
		semop(id_sem, &semWait, 1);
		semop(id_sem, &semDo, 1);
		generateRecapFilePractice();
		semop(id_sem, &semPost, 1);
		
		//Demande si l'utilisateur veut continuer : si oui smv[0]=0 sinon kill les enfants
		//et quitte le programme
		interaction(0);
		
		//Début de practice 2
		wakeChildren();
		//le parent sleep() jusqu'à ce que tous les enfants aient finis
		while(smv[1]!=20)
		{
			id_sem = semop(id_sem, &semWait, 1);
			id_sem = semop(id_sem, &semDo, 1);
			for(int i =0; i<20; i++)
			{
				temp[i]=cars[i];
			}
			id_sem = semop(id_sem, &semPost, 1);
			sortCars(temp, 20);
			printf("\n\n\n\n\nPractice 2 :\n\n");
			printf("\n| N Voiture |     Best S1    |     Best S2    |     Best S3    |    Best Tour     |    Global time   |\n");
			for(int i = 0; i < 20; i++){
				printf("|     %2d    |   %9f s  |   %9f s  |   %9f s  |    %9f s   |    %9f s   |\n", temp[i].name,temp[i].bestS1,temp[i].bestS2,temp[i].bestS3,temp[i].bestCircuit,temp[i].currTime);
			}
			sleep(1);
		}
		
		//Les voitures ont terminé le practice donc on génère le fichier récap
		semop(id_sem, &semWait, 1);
		semop(id_sem, &semDo, 1);
		generateRecapFilePractice();
		semop(id_sem, &semPost, 1);
		
		//Demande si l'utilisateur veut continuer : si oui smv[1]=0 sinon kill les enfants
		//et quitte le programme
		interaction(1);
		
		
		//début de practice 3
		wakeChildren();
		//le parent sleep() jusqu'à ce que tous les enfants aient finis
		while(smv[2]!=20)
		{
			id_sem = semop(id_sem, &semWait, 1);
			id_sem = semop(id_sem, &semDo, 1);
			for(int i =0; i<20; i++)
			{
				temp[i]=cars[i];
			}
			id_sem = semop(id_sem, &semPost, 1);
			sortCars(temp, 20);
			printf("\n\n\n\n\nPractice 3 :\n\n");
			printf("\n| N Voiture |     Best S1    |     Best S2    |     Best S3    |    Best Tour     |    Global time   |\n");
			for(int i = 0; i < 20; i++){
				printf("|     %2d    |   %9f s  |   %9f s  |   %9f s  |    %9f s   |    %9f s   |\n", temp[i].name,temp[i].bestS1,temp[i].bestS2,temp[i].bestS3,temp[i].bestCircuit,temp[i].currTime);
			}
			sleep(1);
		}
		
		//Les voitures ont terminé le practice donc on génère le fichier récap
		semop(id_sem, &semWait, 1);
		semop(id_sem, &semDo, 1);
		generateRecapFilePractice();
		semop(id_sem, &semPost, 1);
		
		//Demande si l'utilisateur veut continuer : si oui smv[2]=0 sinon kill les enfants
		//et quitte le programme
		interaction(2);
		
		//début de practice qualif 1
		wakeChildren();
		//le parent sleep() jusqu'à ce que tous les enfants aient finis
		while(smv[3]!=20)
		{
			id_sem = semop(id_sem, &semWait, 1);
			id_sem = semop(id_sem, &semDo, 1);
			for(int i =0; i<20; i++)
			{
				temp[i]=cars[i];
			}
			id_sem = semop(id_sem, &semPost, 1);
			sortCars(temp, 20);
			printf("\n\n\n\n\nQualification 1 :\n\n");
			printf("\n| N Voiture |     Best S1    |     Best S2    |     Best S3    |    Best Tour     |    Global time   |\n");
			for(int i = 0; i < 20; i++){
				printf("|     %2d    |   %9f s  |   %9f s  |   %9f s  |    %9f s   |    %9f s   |\n", temp[i].name,temp[i].bestS1,temp[i].bestS2,temp[i].bestS3,temp[i].bestCircuit,temp[i].currTime);
			}
			sleep(1);
		}
		//Création d'une variable temporaire qui trie les voitures
		id_sem = semop(id_sem, &semWait, 1);
		id_sem = semop(id_sem, &semDo, 1);
		for(int i =0; i<20; i++)
		{
			temp[i]=cars[i];
		}
		id_sem = semop(id_sem, &semPost, 1);
		
		sortCars(temp, 20);
		buildStartPosition(temp, 1);
		
		//On crée le récap file pour la qualif
		semop(id_sem, &semWait, 1);
		semop(id_sem, &semDo, 1);
		generateRecapFileQualif();
		semop(id_sem, &semPost, 1);
		
		//On élimine les voitures pas assez rapides
		id_sem = semop(id_sem, &semWait, 1);
		id_sem = semop(id_sem, &semDo, 1);
		setOut(2);
		id_sem = semop(id_sem, &semPost, 1);
		
		//On demande à l'utilisateur si il veut continuer, si oui smv[3]=0 sinon on kill les enfants et exit
	
		interaction(3);
		
		//Début de qualif 2
		wakeChildren();
		//Le processus parent dort jusqu'à la fin de l'exécution des enfants
		while(smv[4]!=20)
		{
			id_sem = semop(id_sem, &semWait, 1);
			id_sem = semop(id_sem, &semDo, 1);
			for(int i =0; i<15; i++)
			{
				temp[i]=cars[i];
			}
			id_sem = semop(id_sem, &semPost, 1);
			sortCars(temp, 20);
			printf("\n\n\n\n\nQualification 2 :\n\n");
			printf("\n| N Voiture |     Best S1    |     Best S2    |     Best S3    |    Best Tour     |    Global time   |\n");
			for(int i = 0; i < 20; i++){
				printf("|     %2d    |   %9f s  |   %9f s  |   %9f s  |    %9f s   |    %9f s   |\n", temp[i].name,temp[i].bestS1,temp[i].bestS2,temp[i].bestS3,temp[i].bestCircuit,temp[i].currTime);
			}
			sleep(1);
		}
		//Construction de la liste de départ
		sortCars(carsQualif2, 15);
		buildStartPosition(carsQualif2, 2);
		
		//Les voitures ont terminé la qualif, on crée le fichier récap
		semop(id_sem, &semWait, 1);
		semop(id_sem, &semDo, 1);
		generateRecapFileQualif();
		semop(id_sem, &semPost, 1);
		
		//On élimine les voitures les plus lentes
		id_sem = semop(id_sem, &semWait, 1);
		id_sem = semop(id_sem, &semDo, 1);
		setOut(3);
		id_sem = semop(id_sem, &semPost, 1);
		
		//On demande à l'utilisateur si il veut continuer, si oui smv[4]=0 sinon on kill les enfants et exit
		interaction(4);
		//Début de qualif 3
		wakeChildren();
		//Le processus parent dort jusqu'à la fin de l'exécution des enfants
		while(smv[5]!=20)
		{
			id_sem = semop(id_sem, &semWait, 1);
			id_sem = semop(id_sem, &semDo, 1);
			for(int i =0; i<20; i++)
			{
				temp[i]=cars[i];
			}
			id_sem = semop(id_sem, &semPost, 1);
			sortCars(temp, 20);
			printf("\n\n\n\n\nQualification 3 :\n\n");
			printf("\n| N Voiture |     Best S1    |     Best S2    |     Best S3    |    Best Tour     |    Global time   |\n");
			for(int i = 0; i < 20; i++){
				printf("|     %2d    |   %9f s  |   %9f s  |   %9f s  |    %9f s   |    %9f s   |\n", cars[i].name,cars[i].bestS1,cars[i].bestS2,cars[i].bestS3,cars[i].bestCircuit,cars[i].currTime);
			}
			sleep(1);
		}
		//Construction de la liste de départ
		sortCars(carsQualif3, 10);
		buildStartPosition(carsQualif3, 3);
		
		//Génération du récap file
		semop(id_sem, &semWait, 1);
		semop(id_sem, &semDo, 1);
		generateRecapFileQualif();
		semop(id_sem, &semPost, 1);
		
		//On demande à l'utilisateur si il veut continuer, si oui smv[5]=0 sinon on kill les enfants et exit
		interaction(5);
		//Début de la course!
		wakeChildren();
		//on ajoute du temps aux voitures en fonction de leur position de départ
		addTimeByPosition();
		isRace = 1;
		//Le processus parent dort jusqu'à la fin de l'exécution des enfants
		while(smv[6]!=20)
		{
			id_sem = semop(id_sem, &semWait, 1);
			id_sem = semop(id_sem, &semDo, 1);
			for(int i =0; i<20; i++)
			{
				temp[i]=cars[i];
			}
			id_sem = semop(id_sem, &semPost, 1);
			sortCarsByCurrTime(temp);
			printf("\n\n\n\n\n RACE\n\n");
			printf("\n| N Voiture |     Best S1    |     Best S2    |     Best S3    |    Best Tour     |    Global time   |\n");
			for(int i = 0; i < 20; i++){
				printf("|     %2d    |   %9f s  |   %9f s  |   %9f s  |    %9f s   |    %9f s   |\n", temp[i].name,temp[i].bestS1,temp[i].bestS2,temp[i].bestS3,temp[i].bestCircuit,temp[i].currTime);
			}
			sleep(1);
		}
		
		//Génération du récap file
		semop(id_sem, &semWait, 1);
		semop(id_sem, &semDo, 1);
		generateRecapFileRace();
		semop(id_sem, &semPost, 1);
		
		printf("\n\nThe race is over, we hope you've enjoyed yourselves !\n");
		
	}
	
	
	if(nprocesses > 0) //Tous les fork() ne sont pas terminés
	{
		if ((pid = fork()) < 0)
		{
			perror("fork\n");
			exit(EXIT_FAILURE);
		}
		else if (pid == 0)//Début du processus enfant
		{
			signal(SIGCONT, handleSignal);
			//Sleep une seconde pour permettre au parent de finir de forker
			sleep(1);
			
			//Début de practice 1
			int index;
			
			//On détermine quelle voiture appartient à quel processus
			semop(id_sem, &semWait2, 1);
			semop(id_sem, &semDo2, 1);
			index = indexOf(getpid(), 21, pidList);//index-1 = index de la voiture
			semop(id_sem, &semPost2, 1);
			
			//Seed pour le générateur aléatoire
			srand(time(NULL)+getpid());
			
			if(index==21 || index==0)
			{
				//Erreur
				perror("pid not in pidList\n");
				exit(EXIT_FAILURE);
			}
			practice(index-1, 1);
			//Attends que les autres aient terminés et que le parent imprime le fichier récap
			while(smv[0]!=0)
			{
				sleep(1);
			}
			
			//Début de practice 2
			practice(index-1, 2);
			//Attends que les autres aient terminés et que le parent imprime le fichier récap
			while(smv[1]!=0)
			{
				sleep(1);
			}
			
			//début de practice 3
			practice(index-1, 3);
			//Attends que les autres aient terminés et que le parent imprime le fichier récap
			while(smv[2]!=0)
			{
				sleep(1);
			}
			
			//Début de qualif 1
			qualif(index-1, 1);
			//Attends que les autres aient terminés et que le parent imprime le fichier récap
			while(smv[3]!=0)
			{
				sleep(1);
			}
			
			//Début de qualif 2
			qualif(index-1, 2);
			//Attends que les autres aient terminés et que le parent imprime le fichier récap
			while(smv[4]!=0)
			{
				sleep(1);
			}
			
			//Début de qualif 3
			qualif(index-1, 3);
			//Attends que les autres aient terminés et que le parent imprime le fichier récap
			while(smv[5]!=0)
			{
				sleep(1);
			}
			
			//Début de la course!
			race(index-1);
			
			//Exit quand tout est terminé
			exit(0);
			
		}
		else if(pid > 0)//=> Processus parent
		{
			//Sauvegarde le pid de l'enfant puis lance Worker avec pid -1
			semop(id_sem, &semWait2, 1);
			semop(id_sem, &semDo2, 1);
			pidList[21-nprocesses]=pid;
			semop(id_sem, &semPost2, 1);
			worker(nprocesses - 1);
			
		}
	}
}

int main(int argc, char *argv[])
{
	int key = 123;//Clé shared memory
	int key1 = 789;//Clé second shared memory
	int key2 = 999;//Clé third shared memory
	int key3 = 888;//Clé fourth shared memory
	int key4 = 777;//Clé fifth shared memory
	int keyS = 456;//Clé semaphore
	
	//Création du sémaphore
	if ((id_sem = semget(keyS, 3, IPC_CREAT|0666)) == -1) {
		perror("semget: semget failed");
		exit(1);
	}
	
	//Variable temporaires
	structCar temp[20];
	structCar temp3[15];
	structCar temp4[10];
	int temp1[7];
	int temp2[21];
	
	//Création de la shared memory
	int id_shm = shmget(key, sizeof(temp), IPC_CREAT|0666); //autorisation 0666??
	int id_shm1 = shmget(key1, sizeof(temp1), IPC_CREAT|0666);
	int id_shm2 = shmget(key2, sizeof(temp2), IPC_CREAT|0666);
	int id_shm3 = shmget(key3, sizeof(temp3), IPC_CREAT|0666);
	int id_shm4 = shmget(key4, sizeof(temp4), IPC_CREAT|0666);
	if(id_shm==-1 || id_shm1==-1 || id_shm2==-1 || id_shm3==-1 || id_shm4==-1)
	{
		printf("error");
		exit(EXIT_FAILURE);
	}
	
	//Interactions avec l'utilisateur
	int km;
	char s[100];
	puts("Welcome to this weekend Formula One GP!");
	do
	{
		puts("Enter here the length of a lap in kilometers");
		puts("This number must be between 1 and 7");
		
		if (fgets(s, 100, stdin) == NULL)
		{
			fprintf(stderr, "erreur lors de la lecture");
			exit(EXIT_FAILURE);
		}
		
		sscanf(s, "%d", &km);
	} while (km<1||km>7);
	lengthCircuit = km;
	nbrLapMax = nbrLaps(lengthCircuit);
	
	cars = shmat(id_shm, NULL, SHM_W);
	smv = shmat(id_shm1, NULL, SHM_W);
	pidList = shmat(id_shm2, NULL, SHM_W);
	carsQualif2 = shmat(id_shm3, NULL, SHM_W);
	carsQualif3 = shmat(id_shm4, NULL, SHM_W);
	
	//Initialisation des voitures
	int c[20] = {44,77,3,33,5,7,11,31,19,18,14,2,10,55,8,20,27,30,9,94};
	for(int i=0; i<20; i++)
	{
		//Bloquage des sémaphores
		semop(id_sem, &semWait, 1);
		semop(id_sem, &semDo, 1);
		init(i,c[i]);
		semop(id_sem, & semPost, 1);
		startPosition[i]=0;
		//Débloquage des sémphores
	}
	
	//Initialisation des variables "gobales"
	semop(id_sem, &semWait1, 1);
	semop(id_sem, &semDo1, 1);
	smv[0]=0; //p1
	smv[1]=0; //p2
	smv[2]=0; //p3
	smv[3]=0; //q1
	smv[4]=0; //q2
	smv[5]=0; //q3
	smv[6]=0; //r
	smv[7]=0; //topS1
	smv[8]=0; //topS2
	smv[9]=0; //topS3
	smv[10]=0; //topTour
	semop(id_sem, &semPost1, 1);
	
	//initialisation des valeurs de pidList (valeurs = -1 pour permettre la détection d'erreurs)
	semop(id_sem, &semWait2, 1);
	semop(id_sem, &semDo2, 1);
	pidList[0]=getpid();
	pidList[1]=-1;
	pidList[2]=-1;
	pidList[3]=-1;
	pidList[4]=-1;
	pidList[5]=-1;
	pidList[6]=-1;
	pidList[7]=-1;
	pidList[8]=-1;
	pidList[9]=-1;
	pidList[10]=-1;
	pidList[11]=-1;
	pidList[12]=-1;
	pidList[13]=-1;
	pidList[14]=-1;
	pidList[15]=-1;
	pidList[16]=-1;
	pidList[17]=-1;
	pidList[18]=-1;
	pidList[19]=-1;
	pidList[20]=-1;
	semop(id_sem, &semPost2, 1);
	
	worker(20);
	
	
	//Ici on détache la mémoire partagée et on supprimer les sémaphores
	if((shmdt(cars))==-1)
	{
		perror("shmdt foireux a");
	}
	
	if((shmdt(smv))==-1)
	{
		perror("shmdt foireux 2");
	}
	if((shmdt(pidList))==-1)
	{
		perror("shmdt foireux 3");
	}
	if((shmdt(carsQualif2))==-1)
	{
		perror("shmdt foireux a");
	}
	if((shmdt(carsQualif3))==-1)
	{
		perror("shmdt foireux a");
	}
	if((shmctl(id_shm, IPC_RMID, 0))==-1)
	{
		printf("errno %d\n", errno);
		perror("shmctl(IPC_RMID) failed\n");
	}
	if((shmctl(id_shm1, IPC_RMID, 0))==-1)
	{
		printf("errno %d\n", errno);
		perror("shmctl(IPC_RMID) 1 failed\n");
	}
	if((shmctl(id_shm2, IPC_RMID, 0))==-1)
	{
		printf("errno %d\n", errno);
		perror("shmctl(IPC_RMID) 2 failed\n");
	}
	if((shmctl(id_shm3, IPC_RMID, 0))==-1)
	{
		printf("errno %d\n", errno);
		perror("shmctl(IPC_RMID) 3 failed\n");
	}
	if((shmctl(id_shm4, IPC_RMID, 0))==-1)
	{
		printf("errno %d\n", errno);
		perror("shmctl(IPC_RMID) 4 failed\n");
	}
	if((semctl(id_sem, 0, IPC_RMID))==-1)
	{
//		printf("errno %d\n", errno);
//		perror("semctl(IPC_RMID) failed\n");
	}
	// THE END
	
}
