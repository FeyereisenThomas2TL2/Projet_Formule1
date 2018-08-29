#ifndef qualification_h
#define qualification_h

#include "voiture.h"

/*
 * trie la table
 * @pre : carsQualif not null, sizeArrayCars==20 || sizeArrayCars==15 || sizeArrayCars==10
 * @post : modifie carsQualif
 */
void sortCars(structCar carsQualif[], int sizeArrayCars);

/*
 * Création de la grille de départ
 * @pre : carsQualif not null, q==1 || q==2 || q==3
 * @post : modifie la variable startPosition
 */
void buildStartPosition(structCar carsQualif[], int q);

/*
 * Lance les qualifications sur une voiture
 * @pre : car referenced by the index is not null, q==1 || q==2 || q==3
 * @post : modifie les valeurs dans la structure de car
 */
void qualif(int index, int q);

/*
 * crée un file qui contient les qualifications
 * @post : crée un file qui contient les informations nécessaires
 */
void generateRecapFileQualif();

#endif /* practice_h */

