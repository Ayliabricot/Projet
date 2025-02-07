#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "ecran.h"
#include "AffichageMenu.h"
#include <string.h>
#include <time.h>
#include "jeu.h"

void genererPersonnage(Personnage* personnage, Ecran* ecran) {
	Ennemi* nouvel_ennemi = malloc(sizeof(Personnage));
	nouvel_ennemi->x = 1;
	nouvel_ennemi->y = ecran->hauteur % 15;
}

void genererEnnemi(Ennemi* ennemi, Ecran* ecran) {
	Ennemi* nouvel_ennemi = malloc(sizeof(Ennemi));
	nouvel_ennemi->x = 1 + rand() % ecran->largeur;
	nouvel_ennemi->y = ecran->hauteur % 15;
}

void deplacementEnnemi(Ennemi* ennemi) {
	int deplacer = -1 + rand() % 3;
	ennemi->x = ennemi->x + deplacer;
}