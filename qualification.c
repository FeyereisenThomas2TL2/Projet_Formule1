#include "voiture.h"
#include "utilitaire.h"
#include "qualification.h"
#include <stdio.h>
#include <stdlib.h>

double timeQualif1 = 1080;
double timeQualif2 = 900;
double timeQualif3 = 720;

void sortCars(structCar carsQualif[], int sizeArrayCars)
{
	int i=0;
	structCar tmpCar;
	int j = 0;
	
	for(i=0; i < sizeArrayCars; i++)
	{
		for(j = i+1; j < sizeArrayCars; j++)
		{
			if(carsQualif[j].bestCircuit < carsQualif[i].bestCircuit)
			{
				tmpCar = carsQualif[i];
				carsQualif[i] = carsQualif[j];
				carsQualif[j] = tmpCar;
			}
		}
	}
}

void buildStartPosition(structCar carsQualif[], int q)
{
	int loop = 0;
	int startArray = 0;
	int loop2 = 0;
	int startArray2 = 0;
	
	if (q == 1) {
		loop = 20;
		startArray = 15;
		
		loop2 = 15;
		startArray2 = 0;
	}
	if (q == 2) {
		loop = 15;
		startArray = 10;
		
		loop2 = 10;
		startArray2 = 0;
	}
	if (q == 3) {
		loop = 10;
		startArray = 0;
	}
	
	for(int i=startArray; i < loop; i++)
	{
		startPosition[i] = carsQualif[i].name;
	}
	
	for(int i=startArray2; i < loop2; i++)
	{
		if (q == 1) {
			carsQualif2[i] = carsQualif[i];
		}
		else if (q == 2)
		{
			carsQualif3[i] = carsQualif[i];
		}
	}
}


void qualif(int index, int q)
{
	id_sem = semop(id_sem, &semWait, 1);
	id_sem = semop(id_sem, &semDo, 1);
	double time = getCurrTime();
	id_sem = semop(id_sem, &semPost, 1);
	double timeQualif = 0.0;
	
	if(q==1)
	{
		timeQualif = timeQualif1;
	}
	if(q==2)
	{
		timeQualif = timeQualif2;
	}
	if(q==3)
	{
		timeQualif = timeQualif3;
	}
	
	while(time<timeQualif && cars[index].isOut == 0)
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
		time = getCurrTime();
		id_sem = semop(id_sem, &semPost, 1);
	}
	if(q==1)
	{
		id_sem = semop(id_sem, &semWait1, 1);
		id_sem = semop(id_sem, &semDo1, 1);
		smv[3]++;
		id_sem = semop(id_sem, &semPost1, 1);
	}
	if(q==2)
	{
		id_sem = semop(id_sem, &semWait1, 1);
		id_sem = semop(id_sem, &semDo1, 1);
		smv[4]++;
		id_sem = semop(id_sem, &semPost1, 1);
	}
	if(q==3)
	{
		id_sem = semop(id_sem, &semWait1, 1);
		id_sem = semop(id_sem, &semDo1, 1);
		smv[5]++;
		id_sem = semop(id_sem, &semPost1, 1);
	}
	
}

void generateRecapFileQualif()
{
	FILE *fichier = NULL;
	
	fichier = fopen("RecapFileQualif.txt", "a");
	structCar temp = cars[0];
	temp.bestCircuit=10000;
	if(fichier != NULL){
		fprintf(fichier,"\n| N Voiture |     Best S1    |     Best S2    |     Best S3    |    Best Tour     |\n");
		for(int i = 0; i < 20; i++){
			if((temp.bestCircuit>cars[i].bestCircuit)&&(cars[i].bestCircuit != 0)){temp=cars[i];}
			fprintf(fichier,"|     %2d    |   %9f s  |   %9f s  |   %9f s  |    %9f s   |\n", cars[i].name,cars[i].bestS1,cars[i].bestS2,cars[i].bestS3,cars[i].bestCircuit);
		}
		fprintf(fichier,"\n The winner is the car number %2d with a time of %9f s\n",temp.name, temp.bestCircuit);
		fclose(fichier);
	}
	else{
		printf("Ouverture du fichier recap impossible");
	}
	
	
	for(int i=0; i<20; i++)
	{
		reset(i);
	}
}
