#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "ecran.h"
#include "AffichageMenu.h"
#include <string.h>
#include "placementTexte.h"
#include <time.h>
#include "quitterJeu.h"

Partie** creerTableau(void) {
	Partie** tableau = malloc(sizeof(Partie*));

	*tableau = NULL;

	return tableau;
}

void adapterMemoire(Partie** tableau,int nbParties) {
	tableau = realloc(tableau, nbParties * sizeof(Partie*));
	tableau[nbParties - 1] = NULL;
}

Partie* nouvelle_partie(void) {
	Partie* partie = malloc(sizeof(Partie));

	partie->difficulte = 0;
	partie->objet = 0;
	strcpy_s(partie->pseudo, 50, "Vide");
	partie->score = 0;
	partie->vies = 3;
	partie->x = 0;
	partie->y = 0;

	return partie;
}

