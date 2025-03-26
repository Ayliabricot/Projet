#ifndef AFFICHEMENU_H
#define AFFICHEMENU_H

#include "ecran.h"


void afficherMenu(Ecran* ecran,  int touche,  int* choix, char option[6][40]);
void definirChoix(int touche, int* choix);
void lancer_ecran(int* choix, char option[6][40]);
int afficher_regles(Ecran* ecran);

#endif