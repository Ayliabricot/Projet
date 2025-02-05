#ifndef ECRAN_H
#define ECRAN_H

typedef struct{
	int hauteur;
	int largeur;
}Ecran;

Ecran* definir(void);
void tailleEcran();
void libererEcran();

#endif