#ifndef ECRAN_H
#define ECRAN_H

typedef struct{
	int hauteur;
	int largeur;
}Ecran;

Ecran* definirEcran(void);
void tailleEcran(Ecran* ecran);
void libererEcran(Ecran* ecran);
void contourEcran(Ecran* ecran);


#endif