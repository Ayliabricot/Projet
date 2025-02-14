

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "ecran.h"
#include "AffichageMenu.h"
#include <string.h>
#include "placementTexte.h"
#include <time.h>

int main() {

	Ecran* ecran = definirEcran();

	while (1) {

		if (_kbhit()) {
			int touche = _getch();
			afficherMenu(ecran, touche);
		}
		else {
			afficherMenu(ecran, 0);
			Sleep(5000);
			system("cls");
		}


		/*Sleep(5500);*/
		/*system("cls");*/
	}

	return 0;


	/*printf("♥ ♫ ☺ ★ ☃ ⌘ ∆ © • ☼ ∞\n");*/

}