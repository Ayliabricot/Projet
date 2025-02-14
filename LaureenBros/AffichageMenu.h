#ifndef AFFICHEMENU_H
#define AFFICHEMENU_H

#include "ecran.h"

void contourEcran(Ecran* ecran);
void afficherMenu(Ecran* ecran,  int touche,  int* choix);
void definirChoix(int touche, int* choix);


#endif