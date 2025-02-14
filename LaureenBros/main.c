

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "ecran.h"
#include "AffichageMenu.h"
#include <string.h>
#include "placementTexte.h"
#include <time.h>
#include "menu.h"


int main() {
	char opti[4] = "oui";
	while (1) {
		Ecran* ecran = definirEcran();
		quitterJeuContain(ecran, opti);


		
	}
	printf("ca passe");
	return 0;
}

















