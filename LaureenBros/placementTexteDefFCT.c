#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>



void coordonne(int x, int y) {
		COORD coord;
		coord.X = x;  // position X
		coord.Y = y;  // position Y
		SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
	}