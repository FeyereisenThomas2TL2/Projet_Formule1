#include "utils.h"
//#include "course.h"


void sortCarsByCurrTime(structCar carsRace[])
{
	int i=0;
	structCar tmpCar;
	int j = 0;
	
	for(i=0; i < 20; i++)
		//Rempli l'array => BubbleSort
	{
		for(j = i+1; j < 20; j++)
			//Vérifie si il n'y a pas un nombre plus petit dans la case suivante?
		{
			if(carsRace[j].numCircuit == carsRace[i].numCircuit && carsRace[j].currTime < carsRace[i].currTime)
			{
				//Swap si true
				tmpCar = carsRace[i];
				carsRace[i] = carsRace[j];
				carsRace[j] = tmpCar;
			}
			else if(carsRace[j].numCircuit > carsRace[i].numCircuit)
			{
				//Swap si true
				tmpCar = carsRace[i];
				carsRace[i] = carsRace[j];
				carsRace[j] = tmpCar;
				
			}
		}
	}
}

void race(int index)
{
	id_sem = semop(id_sem, &semWait, 1);
	id_sem = semop(id_sem, &semDo, 1);
	id_sem = semop(id_sem, &semPost, 1);
	
	while(cars[index].isOut == 0 && cars[index].numCircuit < nbrLapMax)
	{
		generateTimeS1(index);
		if(cars[index].bestS1<smv[7])
		{
			id_sem = semop(id_sem, &semWait1, 1);
			id_sem = semop(id_sem, &semDo1, 1);
			smv[7] = cars[index].bestS1;
			id_sem = semop(id_sem, &semPost1, 1);
		}
		generateTimeS2(index);
		if(cars[index].bestS2<smv[8])
		{
			id_sem = semop(id_sem, &semWait1, 1);
			id_sem = semop(id_sem, &semDo1, 1);
			smv[8] = cars[index].bestS2;
			id_sem = semop(id_sem, &semPost1, 1);
		}
		generateTimeS3(index);
		if(cars[index].bestS3<smv[9])
		{
			id_sem = semop(id_sem, &semWait1, 1);
			id_sem = semop(id_sem, &semDo1, 1);
			smv[9] = cars[index].bestS3;
			id_sem = semop(id_sem, &semPost1, 1);
		}
		if(cars[index].bestCircuit<smv[10])
		{
			id_sem = semop(id_sem, &semWait1, 1);
			id_sem = semop(id_sem, &semDo1, 1);
			smv[10] = cars[index].bestCircuit;
			id_sem = semop(id_sem, &semPost1, 1);
		}
		id_sem = semop(id_sem, &semWait, 1);
		id_sem = semop(id_sem, &semDo, 1);
		id_sem = semop(id_sem, &semPost, 1);
		
		if(cars[index].isOut == 0)
		{
			cars[index].numCircuit++; //Incrémente le nombre de circuit déjŕ performé
		}
	}
	
	id_sem = semop(id_sem, &semWait1, 1);
	id_sem = semop(id_sem, &semDo1, 1);
	smv[6]++;
	id_sem = semop(id_sem, &semPost1, 1);
	
}

void generateRecapFileRace()
{
	//Ecrit le fichier 
	FILE *file = NULL;
	
	file = fopen("RecapFileRace.txt", "a");
	structCar temp = cars[0];
	temp.currTime=10000;
	if(file != NULL){
		fprintf(file,"\n| N Voiture |     Best S1    |     Best S2    |     Best S3    |    Best Tour     |    Global time   |\n");
		for(int i = 0; i < 20; i++){
			if((temp.currTime>cars[i].currTime)&&(cars[i].currTime != 0)){temp=cars[i];}
			fprintf(file,"|     %2d    |   %9f s  |   %9f s  |   %9f s  |    %9f s   |    %9f s   |\n", cars[i].name,cars[i].bestS1,cars[i].bestS2,cars[i].bestS3,cars[i].bestCircuit,cars[i].currTime);
		}
		fprintf(file,"\n The winner is the car number %2d with a time of %9f s\n",temp.name, temp.currTime);
		fclose(file);
	}
	else{
		printf("Ouverture du fichier recap impossible");
	}
	//Aprčs avoir sauvegardé les valeurs dans un fichier, on remet ŕ 0 pour lancer un nouveau pratice
	for(int i=0; i<20; i++)
	{
		reset(i);
	}
}
