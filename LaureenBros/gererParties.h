#ifndef PARTIES_H
#define PARTIES_H

#include "ecran.h"

typedef struct {
	char pseudo[30];
	int objet;
	int score;
	int difficulte;
	int vies;
	int x;
	int y;
}Partie;

Partie** creerTableau(void);
Partie* nouvelle_partie(void);
void demanderPseudo(Ecran* ecran, Partie* partie);

#endif