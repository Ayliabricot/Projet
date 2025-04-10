#ifndef AFFICHEMENU_H
#define AFFICHEMENU_H

#include "ecran.h"
#include "gererParties.h"

void afficherMenu(Ecran* ecran,  int touche,  int* choix, char option[5][40],Partie** tableau, int* nbParties);
void definirChoix(int touche, int* choix);
void lancer_ecran(int* choix, char option[5][40],Partie** tableau, int* nbParties);

int afficher_regles(Ecran* ecran);

int choisirDifficulteContain(Ecran* ecran, Partie* partie);
void affichageDifficulte(Ecran* ecran, int difficulte);
int choisirDifficulte(int toucheDiff, int difficulte);

void cacherCurseur(void);
void afficherCurseur(void);

#endif