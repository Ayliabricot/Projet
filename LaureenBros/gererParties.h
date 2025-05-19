#ifndef PARTIES_H
#define PARTIES_H

#include "ecran.h"

#define MAX_PLAYERS 14
#define MAX_NAME_LEN 50

typedef struct {
	char name[MAX_NAME_LEN];
	double score;
} Player;


typedef struct {
	char pseudo[30];
	int objet;
	int score;
	int difficulte;
	int vies;
	int x;
	int y;
} Partie;

Partie** creerTableau(void);
Partie* nouvelle_partie(void);
void demanderPseudo(Ecran* ecran, Partie* partie);
int affichageScore(Ecran *ecran);
int compareScores(const void* a, const void* b);
#endif