#ifndef ECRAN_H
#define ECRAN_H

#include "gererParties.h"

typedef struct{
	int hauteur;
	int largeur;
}Ecran;

Ecran* definirEcran(void);
void tailleEcran(Ecran* ecran);
void contourEcran(Ecran* ecran);
void libererEcran(Ecran* ecran);



#endif