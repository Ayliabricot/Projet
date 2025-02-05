#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "ecran.h"


int main() {
	Ecran* ecran = definirEcran();
	while (1) {
		
		
		contourEcran(ecran);
		Sleep(500);
		system("cls");
	}

	return 0;
}