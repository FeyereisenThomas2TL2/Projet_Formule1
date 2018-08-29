//#include "voiture.h"
#include "utilitaire.h"

//Initialisation dees voitures
void init(int i, int name)
{
	cars[i].name = name;
	cars[i].bestCircuit=0;		//meilleur temps
	cars[i].bestS1=0;		//meilleur sur secteur 1
	cars[i].bestS2=0;		//meilleur sur secteur 2
	cars[i].bestS3=0;		//meilleur sur secteur 3
	cars[i].numCircuit=0;
	cars[i].currTime=0;
	cars[i].currCircuit=0;
	cars[i].inStand=0;		//22 à 27 secondes
	cars[i].isOut=0;
	
	if(i<10)
	{
		carsQualif2[i].name=0;
		carsQualif2[i].bestCircuit=0;
		carsQualif2[i].bestS1=0;
		carsQualif2[i].bestS2=0;
		carsQualif2[i].bestS3=0;
		carsQualif2[i].numCircuit=0;
		carsQualif2[i].currTime=0;
		carsQualif2[i].currCircuit=0;
		carsQualif2[i].inStand=0;
		carsQualif2[i].isOut=0;
		carsQualif3[i].name=0;
		carsQualif3[i].bestCircuit=0;
		carsQualif3[i].bestS1=0;
		carsQualif3[i].bestS2=0;
		carsQualif3[i].bestS3=0;
		carsQualif3[i].numCircuit=0;
		carsQualif3[i].currTime=0;
		carsQualif3[i].currCircuit=0;
		carsQualif3[i].inStand=0;
		carsQualif3[i].isOut=0;
	}
	if(i>=10 && i< 15)
	{
		carsQualif2[i].name=0;
		carsQualif2[i].bestCircuit=0;
		carsQualif2[i].bestS1=0;
		carsQualif2[i].bestS2=0;
		carsQualif2[i].bestS3=0;
		carsQualif2[i].numCircuit=0;
		carsQualif2[i].currTime=0;
		carsQualif2[i].currCircuit=0;
		carsQualif2[i].inStand=0;
		carsQualif2[i].isOut=0;
	}
}

//reset les scores indexe i
void reset(int i)
{
	cars[i].bestCircuit=0;
	cars[i].bestS1=0;
	cars[i].bestS2=0;
	cars[i].bestS3=0;
	cars[i].numCircuit=0;
	cars[i].currTime=0;
	cars[i].currCircuit=0;
	cars[i].inStand=0;
	cars[i].isOut=0;
}
