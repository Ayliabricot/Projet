#ifndef MENU_H
#define MENU_H

#include "ecran.h"

int quitterJeu(Ecran* ecran, int touche, char opti[4]);
int quitterJeuContain(Ecran* ecran, char opti[4]);
int confirmerChoix(char opti[4]);

int choisir(Ecran* ecran, int touche, char opti[4], int resultat);
int jeuFiniContain(Ecran* ecran, char opti[4], int resultat);

#endif