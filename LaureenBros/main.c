

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
#include "menu."


int main() {
	while (1) {

       system("cls");
		Ecran* ecran = definirEcran();
		affichageDifficulte(ecran);
		
		Sleep(6000);
	}
}






//mettre des while(valeur= ...)  ca va dans un menu










