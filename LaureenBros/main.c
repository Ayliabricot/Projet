

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
#include 


int main() {

	Ecran* ecran = definirEcran();
	int touche = 0;
	int* choix = malloc(sizeof(int));
	if (choix == NULL) {
		printf("Erreur d'allocation memoire\n");
		return 1;
	}
	*choix = 2;


	afficherMenu(ecran, touche, choix);

	while (1) {
		if (_kbhit()) {
			touche = _getch();


			system("cls");
			afficherMenu(ecran, touche, choix);
		}


	}
	free(choix);
	choix = NULL;
	return 0;

}






//mettre des while(valeur= ...)  ca va dans un menu










