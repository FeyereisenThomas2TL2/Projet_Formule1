#ifndef _VOITURE_H
#define _VOITURE_H

typedef struct structCar {
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

void init(int i, int name);
void reset(int i);

#endif
