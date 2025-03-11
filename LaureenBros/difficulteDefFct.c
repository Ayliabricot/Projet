#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "quitterJeu.h"
#include "ecran.h"
#include "placementTexte.h"


void affichageDifficulte(Ecran* ecran) {
	contourEcran(ecran);
	SetConsoleOutputCP(1252);
	SetConsoleCP(1252);

	afficherTexte(ecran->largeur / 2 - 32 / 2, ecran->hauteur /3, "Choississez votre difficulté :");
	afficherTexte(ecran->largeur / 3, ecran->hauteur / 2, " /)/)");
	afficherTexte(ecran->largeur / 3, ecran->hauteur / 2+1, "( -.-)");
	afficherTexte(ecran->largeur / 3, ecran->hauteur / 2+2, " o_(µ)(µ)");
	SetConsoleOutputCP(GetOEMCP());
	SetConsoleCP(GetOEMCP());
}