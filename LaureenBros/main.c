#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "ecran.h"
#include "AffichageMenu.h"
#include <string.h>

int main() {
	
	Ecran* ecran = definirEcran();
	while (1) {


		contourEcran(ecran);
		afficherMenu(ecran);
		
		Sleep(1500);
		system("cls");
	}

	return 0;


	/*printf("♥ ♫ ☺ ★ ☃ ⌘ ∆ © • ☼ ∞\n");*/

}