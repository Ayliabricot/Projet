#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "ecran.h"
#include "AffichageMenu.h"
#include <string.h>
#include <time.h>
#include <direct.h>
#include "jeu.h"




SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* tileTexture = NULL;
SDL_Texture* playerTexture = NULL;
SDL_Texture* hudTexture = NULL;
SDL_Texture* itemsTexture = NULL;
TTF_Font* font = NULL;
SDL_Texture* textTexture = NULL;
SDL_Texture* deathTexture = NULL;


Sprite player;
Sprite chateau;
bool running = true;
float camera_x = 0.0f;
float camera_lock_x = 0.0f;
int map[MAP_HEIGHT][MAP_WIDTH] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 6, 7, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 1, 0, 0, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 4, 5, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 2, 3, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 8, 8, 1, 2, 3, 1, 1, 1, 8, 8, 8, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 1, 1, 8, 8, 8, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 8, 8, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 8, 8, 1, 8, 8, 1, 8, 8, 1, 8, 8, 1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 1, 2, 3, 1, 1, 1, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 1, 1, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 1, 9, 9, 1, 9, 9, 1, 9, 9, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 1, 2, 3, 1, 1, 1, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 1, 1, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 1, 9, 9, 1, 9, 9, 1, 9, 9, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 1, 2, 3, 1, 1, 1, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 1, 1, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 1, 9, 9, 1, 9, 9, 1, 9, 9, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 1, 2, 3, 1, 1, 1, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 1, 1, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 1, 9, 9, 1, 9, 9, 1, 9, 9, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

GameState* gameState = NULL;

bool is_solid_tile(float x, float y) {
    int col = (int)(x / BLOCK_SIZE);
    int row = (int)(y / BLOCK_SIZE);
    return (col >= 0 && col < MAP_WIDTH && row >= 0 && row < MAP_HEIGHT) &&
        (map[row][col] != 0) && (map[row][col] != 8) && (map[row][col] != 9);
}

bool is_deadly_tile(float x, float y) {
    int col = (int)(x / BLOCK_SIZE);
    int row = (int)(y / BLOCK_SIZE);
    return (col >= 0 && col < MAP_WIDTH && row >= 0 && row < MAP_HEIGHT) &&
        (map[row][col] == 8 || map[row][col] == 9);
}

bool initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;

    window = SDL_CreateWindow("Mario Fusion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) printf("Erreur window");

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) printf("Erreur render");

    SDL_Surface* tileSurface = IMG_Load("png/textures.png");
    if (!tileSurface) return printf("Erreur surface tile");
    tileTexture = SDL_CreateTextureFromSurface(renderer, tileSurface);
    SDL_FreeSurface(tileSurface);

    SDL_Surface* marioSurface = IMG_Load("png/mario.png");
    if (!marioSurface) return printf("Erreur surface mario");
    SDL_SetColorKey(marioSurface, SDL_TRUE, SDL_MapRGB(marioSurface->format, 0, 197, 10));
    playerTexture = SDL_CreateTextureFromSurface(renderer, marioSurface);
    SDL_FreeSurface(marioSurface);



    SDL_Surface* hudSurface = IMG_Load("sprite/hud.png");
    if (!hudSurface) return printf("Erreur surface HUD");
    hudTexture = SDL_CreateTextureFromSurface(renderer, hudSurface);
    SDL_FreeSurface(hudSurface);

    SDL_Surface* itemsSurface = IMG_Load("sprite/health.png");
    if (!itemsSurface) return printf("Erreur surface items");
    itemsTexture = SDL_CreateTextureFromSurface(renderer, itemsSurface);
    SDL_FreeSurface(itemsSurface);  

    TTF_Init();
    font = TTF_OpenFont("Fonts/8514oem.fon", 24);

    SDL_Surface* deathSurface = IMG_Load("png/mario_anim.png");
    if (!deathSurface) {
        printf("Erreur surface mario death: %s\n", IMG_GetError());
        return false;
    }
    SDL_SetColorKey(deathSurface, SDL_TRUE, SDL_MapRGB(deathSurface->format, 39, 122, 209));
    deathTexture = SDL_CreateTextureFromSurface(renderer, deathSurface);
    SDL_FreeSurface(deathSurface);

    // Initialisation des nouveaux états
    player.isDying = false;
    player.isRespawning = false;
    player.respawnTimer = 0.0f;
    player.swingOffset = 0.0f;
    player.parachuteYOffset = 0.0f;
    player.deathTimer = 0.0f;
   
    player.x = 100;
    player.y = SCREEN_HEIGHT - 480;
    gameState = malloc(sizeof(GameState));
    if (!gameState) return false;

    gameState->lives = 3;
    gameState->coins = 0;
    gameState->world = 1;
    gameState->stage = 1;
    gameState->distance = 0;
    strcpy_s(gameState->save, 50, currentPartie->pseudo);

    // Charger la sauvegarde si elle existe
    if (chargerPartieUNIQUE) loadGame();
    // Initialisation des autres propriétés
    player.velX = player.velY = 0;
    player.texture = playerTexture;
    player.animationTimer = player.idleTimer = 5;
    player.currentFrame = 3;
    player.isJumping = false;
    player.gravity = 0.5f;
    player.jumpForce = -12.0f;
    player.facingRight = true;
    player.isIdleAnimating = false;
    player.lookAlternate = false;
    player.wasMoving = false;

    
    return true;
}

void collectPieces() {
    if (!player.isDying && !player.isRespawning) {
        // Calculate player's center position
        float playerCenterX = player.x + 16;
        float playerCenterY = player.y + 32;

        // Convert position to map coordinates
        int col = (int)(playerCenterX / BLOCK_SIZE);
        int row = (int)(playerCenterY / BLOCK_SIZE);

        // Check if the player is on a valid map tile
        if (col >= 0 && col < MAP_WIDTH && row >= 0 && row < MAP_HEIGHT) {
            // Check if the tile is a piece (ID 10)
            if (map[row][col] == 10) {
                // Collect the piece
                map[row][col] = 0; // Remove the piece from the map
                gameState->coins++; // Increment the score
                printf("Piece collected! Total coins: %d\n", gameState->coins);
            }
        }
    }
}

void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
            running = false;
        if (event.type == SDL_KEYDOWN) {
            if ((event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_z) && !player.isJumping) {
                player.velY = player.jumpForce;
                player.isJumping = true;
                player.wasMoving = (player.velX != 0);
            }
            // Save with F5 using currentPartie's pseudo
            else if (event.key.keysym.sym == SDLK_F5 && currentPartie != NULL) {
                saveGameWithPseudo(currentPartie->pseudo);
            }
            // Load with F9 using currentPartie's pseudo
            else if (event.key.keysym.sym == SDLK_F9 && currentPartie != NULL) {
                loadGameWithPseudo(currentPartie->pseudo);
            }
        }
    }

    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    player.velX = 0;

    if (keystate[SDL_SCANCODE_LEFT] || keystate[SDL_SCANCODE_A]) {
        player.velX = -3;
        player.facingRight = false;
    }
    if (keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D]) {
        player.velX = 3;
        player.facingRight = true;
    }
}

// Modification de la fonction update pour corriger le problème de saut en glissant

void update() {

    if (!player.isDying && !player.isRespawning &&
        (is_deadly_tile(player.x + 16, player.y + 32) ||
            is_deadly_tile(player.x + 32, player.y + 32))) {
        player.isDying = true;
        player.deathTimer = 0.0f;
        return;
    }

    if (player.isDying) {
        player.deathTimer += 0.05f;

        // Death animation sequence
        if (player.deathTimer < 1.0f) {
            player.currentFrame = 10; // First death frame
        }
        else if (player.deathTimer < 2.0f) {
            player.currentFrame = 11; // Second death frame
            player.y += 5.0f; // Make Mario fall
        }
        else {
            // After death animation completes
            gameState->lives--;
            if (gameState->lives > 0) {
                player.isDying = false;
                player.isRespawning = true;
                player.respawnTimer = 0.0f;
                // Respawn 5 blocs avant la position actuelle
                player.x -= 400;
                player.y = SCREEN_HEIGHT-800;
                camera_lock_x = 0.0f;
                camera_x = camera_lock_x;
                player.currentFrame = 12;
            }
            else {
                // Game Over
                running = false;
            }
        }
        return; // Skip other updates while dying
    }

    if (player.isRespawning) {
        player.respawnTimer += 0.05f;

        // Parachute animation
        player.swingOffset = sin(player.respawnTimer * 2.0f) * 20.0f;
        player.parachuteYOffset = sin(player.respawnTimer * 5.0f) * 2.0f;

        // Déplacement horizontal pendant le respawn
        float newX = player.x + player.velX;
        if (player.velX > 0 && !is_solid_tile(newX + 32, player.y + 32)) {
            player.x = newX;
        }
        else if (player.velX < 0 && !is_solid_tile(newX, player.y + 32)) {
            player.x = newX;
        }

        // Descente verticale
        player.y += 2.0f;

        // Fin du respawn
        if (player.y >= SCREEN_HEIGHT - 430) {
            player.isRespawning = false;
            player.currentFrame = 3;
            player.swingOffset = 0.0f;
            player.parachuteYOffset = 0.0f;
        }

        return; // on skippe le reste du update (physique classique)
    }

    collectPieces();

    float newX = player.x + player.velX;
    float newY = player.y + player.velY;
    gameState->distance = player.x/80;
    // Horizontale collision
    if (player.velX > 0 && !is_solid_tile(newX + 32, player.y + 32)) {
        player.x = newX;
    }
    else if (player.velX < 0 && !is_solid_tile(newX, player.y + 32)) {
        player.x = newX;
    }

    // Vérifie si le joueur est sur le sol avant d'appliquer la gravité
    bool wasOnGround = !player.isJumping;
    bool isOnGround = is_solid_tile(player.x + 16, player.y + 64 + 1);

    // Si le joueur était au sol mais ne l'est plus (glisse d'un bloc), 
    // considérer qu'il est en train de sauter/tomber
    if (wasOnGround && !isOnGround) {
        player.isJumping = true;
    }

    // Gravité
    player.velY += player.gravity;

    // Verticale collision
    if (player.velY > 0) {
        if (is_solid_tile(player.x + 16, newY + 64)) {
            player.y = ((int)((newY + 64) / BLOCK_SIZE)) * BLOCK_SIZE - 64;
            player.velY = 0;
            player.isJumping = false;
        }
        else player.y = newY;
    }
    else if (player.velY < 0) {
        if (is_solid_tile(player.x + 16, newY)) {
            player.y = ((int)(newY / BLOCK_SIZE) + 1) * BLOCK_SIZE;
            player.velY = 0;
        }
        else player.y = newY;
    }

    // Animation
    if (player.isJumping) {
        // Animation de saut uniquement
        player.idleTimer = 0;
        player.isIdleAnimating = false;

        // Détermine la frame de saut en fonction de la vitesse Y et de l'orientation
        if (player.velY < 0) { // Monter
            player.currentFrame = 8; // Frame de saut vers le haut
        }
        else { // Descendre
            player.currentFrame = 9; // Frame de saut vers le bas
        }
    }
    else if (player.velX != 0) {
        // Animation de course seulement si au sol
        player.wasMoving = true;
        player.idleTimer = 0;
        player.isIdleAnimating = false;

        player.animationTimer++;
        if (player.animationTimer >= ANIMATION_SPEED) {
            player.animationTimer = 0;
            player.currentFrame = (player.currentFrame + 1) % 3; // Cycle entre 0, 1, 2
        }
    }
    else {
        // Le joueur est immobile
        player.idleTimer++;

        // Après 3 secondes (180 frames)
        if (player.idleTimer > 180) {
            player.isIdleAnimating = true;

            player.animationTimer++;
            if (player.animationTimer >= ANIMATION_SPEED * 3) {
                player.animationTimer = 0;

                if (player.currentFrame == 3) player.currentFrame = 4;
                else if (player.currentFrame == 4) player.currentFrame = 5;
                else if (player.currentFrame == 5) player.currentFrame = 6;
                else if (player.currentFrame == 6) {
                    player.currentFrame = 7;
                    player.lookAlternate = true;
                }
                else if (player.currentFrame == 7) {
                    player.currentFrame = 4;
                    player.lookAlternate = false;
                }
            }
        }
        else {
            player.currentFrame = 3; // Frame statique normale
        }
    }
    

    float target_camera_x = player.x + 16 - SCREEN_WIDTH / 2;
    if (target_camera_x > camera_lock_x) camera_lock_x = target_camera_x;

    float max_camera_x = (MAP_WIDTH * BLOCK_SIZE) - SCREEN_WIDTH;
    if (camera_lock_x > max_camera_x) camera_lock_x = max_camera_x;

    camera_x = camera_lock_x;
    if (player.x < camera_x) player.x = camera_x;
    float max_player_x = (MAP_WIDTH * BLOCK_SIZE) - 32;
    if (player.x > max_player_x) player.x = max_player_x;
}



void renderMap() {
    int tile_width, tile_height;
    SDL_QueryTexture(tileTexture, NULL, NULL, &tile_width, &tile_height);
    tile_width /= NUMBER_OF_TILES;

    int first_tile = (int)(camera_x / BLOCK_SIZE);
    int offset_x = (int)(camera_x) % BLOCK_SIZE;

    for (int row = 0; row < MAP_HEIGHT; row++) {
        for (int col = 0; col <= VIEW_WIDTH; col++) {
            int tile_col = first_tile + col;
            if (tile_col >= 0 && tile_col < MAP_WIDTH) {
                int tile_index = map[row][tile_col];
                if (tile_index == 2 || tile_index == 3) {
                    if (row>=10) {
                        SDL_Rect src = { 1 * tile_width, 0, tile_width, tile_height };
                        SDL_Rect dst = { col * BLOCK_SIZE - offset_x, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE };
                        SDL_RenderCopy(renderer, tileTexture, &src, &dst);
                    }
                    SDL_Rect src = { tile_index * tile_width, 0, tile_width, tile_height };
                    SDL_Rect dst = { col * BLOCK_SIZE - offset_x, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE };
                    SDL_RenderCopy(renderer, tileTexture, &src, &dst);
                }
                else {
                    SDL_Rect src = { tile_index * tile_width, 0, tile_width, tile_height };
                    SDL_Rect dst = { col * BLOCK_SIZE - offset_x, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE };
                    SDL_RenderCopy(renderer, tileTexture, &src, &dst);
                }
            }
        }
    }
}


void renderMario() {
    // Définition des rectangles source


   
    SDL_Texture* currentTexture = player.texture; // Utilise la texture courante du joueur

    // Pour les animations de mort/respawn, utiliser deathTexture
    if (player.isDying || player.isRespawning) {
        currentTexture = deathTexture;
    }
    if (player.currentFrame >= 10 && player.currentFrame <= 12) {
        currentTexture = deathTexture;
    }
    SDL_Rect frame0 = { 3, 45, 17, 22 };   // debout
    SDL_Rect frame1 = { 22, 45, 17, 22 };  // Course frame 1
    SDL_Rect frame2 = { 41, 45, 17, 22 };  // Course frame 2
    SDL_Rect frame3 = { 3, 248, 17, 22 };  // Course frame 3
    SDL_Rect frame4 = { 3, 132, 17, 22 };  // Idle frame 1 (face)
    SDL_Rect frame5 = { 22, 132, 17, 22 }; // Idle frame 2 (côté droit)
    SDL_Rect frame6 = { 41, 132, 17, 22 }; // Idle frame 3 (dos)
    SDL_Rect frame8 = { 3, 74, 17, 22 };   // Saut haut
    SDL_Rect frame9 = { 22, 74, 17, 22 };  // Saut bas
    SDL_Rect frame10 = { 27, 255, 13, 24 };// mort frame 1
    SDL_Rect frame11 = { 180, 35, 23, 13 };// mort frame 2
    SDL_Rect frame12 = { 133, 614, 24, 32 };// respawn

    SDL_Rect srcRect;
    SDL_Rect dstRect = {
    (int)(player.x - camera_x + (player.isRespawning ? player.swingOffset : 0)),
    (int)(player.y + (player.isRespawning ? player.parachuteYOffset : 0)),
    32,
    64
    };

    switch (player.currentFrame) {
    case 0: srcRect = frame0; break;
    case 1: srcRect = frame1; break;
    case 2: srcRect = frame2; break;
    case 3: srcRect = frame3; break;
    case 4: srcRect = frame4; break;
    case 5: srcRect = frame5; break;
    case 6: srcRect = frame6; break;
    case 7: srcRect = frame5; break;
    case 8: srcRect = frame8; break;
    case 9: srcRect = frame9; break;
    case 10: srcRect = frame10; break;
    case 11: srcRect = frame11; break;
    case 12:srcRect = frame12;break;
    default: srcRect = frame3; break;
    }

    if (player.currentFrame == 11) {
        dstRect.h = 26; // Flattened Mario is shorter
    }
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    // Flip logic
    if (player.isJumping) {
        if (!player.facingRight) flip = SDL_FLIP_HORIZONTAL;
    }
    else if (player.isIdleAnimating) {
        if (player.currentFrame == 5 && !player.facingRight)
            flip = SDL_FLIP_HORIZONTAL;
        else if (player.currentFrame == 7 && player.facingRight)
            flip = SDL_FLIP_HORIZONTAL;
    }
    else if (player.velX < 0) {
        flip = SDL_FLIP_HORIZONTAL;
    }

    // Don't render Mario during death animation (frame 11 is the flattened sprite)
    if (player.currentFrame != 11 || player.isDying) {
        SDL_RenderCopyEx(renderer, currentTexture, &srcRect, &dstRect, 0, NULL, flip);
    }

    // Render parachute during respawn
    if (player.isRespawning) {
        SDL_Rect dstWithSwing = dstRect;
        dstWithSwing.x += (int)player.swingOffset;
        SDL_RenderCopyEx(renderer, currentTexture, &srcRect, &dstRect, 0, NULL, flip);
    }
}


void renderHUD() {
    if (!gameState || !renderer || !hudTexture || !itemsTexture) return;

    // 1. Afficher le fond du HUD
    SDL_Rect hudBgRect = { 0, 0, SCREEN_WIDTH, 50 };
    SDL_Rect hudBgSrc = { 2, 176, 234, 18 };
    SDL_RenderCopy(renderer, hudTexture, &hudBgSrc, &hudBgRect);

    // 2. Afficher les vies (cœurs)
    int MAX_LIVES = 3; // Nombre max de vies affichables
    for (int i = 0; i < MAX_LIVES; i++) {
      
        if (i == 0) {
            SDL_Rect lifeRect = { SCREEN_WIDTH * 0.825  , 10, 25, 25 };
            if (i < gameState->lives) {
                // Vie pleine
                SDL_Rect lifeSrc = { 34, 13, 12, 16 };
                SDL_RenderCopy(renderer, itemsTexture, &lifeSrc, &lifeRect);
            }
            else {
                // Vie vide
                SDL_Rect lifeSrc = { 48, 13, 12, 16 };
                SDL_RenderCopy(renderer, itemsTexture, &lifeSrc, &lifeRect);
            }
        }
        else if (i == 1) {
            SDL_Rect lifeRect = { SCREEN_WIDTH * 0.828 + 83, 10, 25, 25 };
            if (i < gameState->lives) {
                // Vie pleine
                SDL_Rect lifeSrc = { 34, 13, 12, 16 };
                SDL_RenderCopy(renderer, itemsTexture, &lifeSrc, &lifeRect);
            }
            else {
                // Vie vide
                SDL_Rect lifeSrc = { 48, 13, 12, 16 };
                SDL_RenderCopy(renderer, itemsTexture, &lifeSrc, &lifeRect);
            }
        }
        else if (i == 2) {
            SDL_Rect lifeRect = { SCREEN_WIDTH * 0.828 + 173, 10, 25, 25 };
            if (i < gameState->lives) {
                // Vie pleine
                SDL_Rect lifeSrc = { 34, 13, 12, 16 };
                SDL_RenderCopy(renderer, itemsTexture, &lifeSrc, &lifeRect);
            }
            else {
                // Vie vide
                SDL_Rect lifeSrc = { 48, 13, 12, 16 };
                SDL_RenderCopy(renderer, itemsTexture, &lifeSrc, &lifeRect);

            }
        }
        // Choisir entre vie pleine ou vide
   
    }
 

    // 4. Afficher le nombre de pièces (avec SDL_ttf)
    char coinText[10];
    snprintf(coinText, sizeof(coinText), "%d", gameState->coins);

    SDL_Color white = { 255, 255, 255, 255 };
    SDL_Surface* textSurface = TTF_RenderText_Solid(font, coinText, white);
    SDL_Texture* textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    SDL_Rect textRect = { SCREEN_WIDTH * 0.467, 13.5, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);



    // 6. Afficher le numéro du monde
    char worldText[10];
    snprintf(worldText, sizeof(worldText), "%d-%d", gameState->world, gameState->stage);

    textSurface = TTF_RenderText_Solid(font, worldText, white);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    textRect = (SDL_Rect){ SCREEN_WIDTH*0.168, 13.5, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

    // 7. Afficher le nom de sauvegarde
    char saveName[50];
    snprintf(saveName, sizeof(saveName), "%s", gameState->save);

    textSurface = TTF_RenderText_Solid(font, saveName, white);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    textRect = (SDL_Rect){SCREEN_WIDTH*0.54, 13.5, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);


    char distance[10];
    snprintf(distance, sizeof(distance), "%dm", gameState->distance);

    textSurface = TTF_RenderText_Solid(font, distance, white);
    textTexture = SDL_CreateTextureFromSurface(renderer, textSurface);
    textRect = (SDL_Rect){ SCREEN_WIDTH * 0.341, 13.5, textSurface->w, textSurface->h };
    SDL_RenderCopy(renderer, textTexture, NULL, &textRect);
    SDL_FreeSurface(textSurface);
    SDL_DestroyTexture(textTexture);

}

void saveGameWithPseudo(char* pseudo) {
    char saveFilePath[255];
    snprintf(saveFilePath, sizeof(saveFilePath), "saves/save_%s.txt", pseudo);

    FILE* file = fopen(saveFilePath, "w");
    if (!file) {
        printf("Erreur lors de l'ouverture du fichier de sauvegarde\n");
        return;
    }

    // Save the player's position, camera lock, and coins collected
    fprintf(file, "%.2f %.2f %.2f %d\n", player.x, player.y, camera_lock_x, gameState->coins); // Added coins
    fclose(file);

    printf("Jeu sauvegard� pour %s - Position: (%.2f, %.2f), Camera lock: %.2f, Coins: %d\n",
        pseudo, player.x, player.y, camera_lock_x, gameState->coins);
}

void loadGameWithPseudo(char* pseudo) {
    char saveFilePath[255];
    snprintf(saveFilePath, sizeof(saveFilePath), "saves/save_%s.txt", pseudo);

    FILE* file = fopen(saveFilePath, "r");
    if (!file) {
        printf("Aucune sauvegarde trouv�e pour %s, utilisation des valeurs par d�faut\n", pseudo);
        return;
    }

    float x, y, camLock;
    int coins; // Variable to store the number of coins
    if (fscanf_s(file, "%f %f %f %d", &x, &y, &camLock, &coins) == 4) { // Read 4 values instead of 3
        player.x = x;
        player.y = y;
        camera_lock_x = camLock;
        camera_x = camera_lock_x;
        gameState->coins = coins; // Update the game state with loaded coins
        printf("Jeu charg� pour %s - Position: (%.2f, %.2f), Camera lock: %.2f, Coins: %d\n",
            pseudo, player.x, player.y, camera_lock_x, gameState->coins);
    }
    else {
        printf("Erreur lors de la lecture de la sauvegarde pour %s\n", pseudo);
    }

    fclose(file);
}

// Update the existing save and load functions to use the new ones
void saveGame() {
    if (currentPartie != NULL) {
        saveGameWithPseudo(currentPartie->pseudo);
    }
    else {
        printf("Aucune partie en cours pour sauvegarder\n");
    }
}

void loadGame() {
    if (currentPartie != NULL) {
        loadGameWithPseudo(currentPartie->pseudo);
    }
    else {
        printf("Aucune partie en cours pour charger\n");
    }
}

void render(int* choixPerso) {
    SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
    SDL_RenderClear(renderer);

    renderMap();
    renderMario();
    renderHUD(); 

    SDL_RenderPresent(renderer);
}


void cleanup() {
    SDL_DestroyTexture(tileTexture);
    SDL_DestroyTexture(playerTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_DestroyTexture(hudTexture);
    SDL_DestroyTexture(itemsTexture);
    TTF_CloseFont(font);
    TTF_Quit();
    free(gameState);
    SDL_Quit();
}

int lancerJeu(int argc, char* argv[]) {
    if (!initialize()) {
        printf("Échec de l'initialisation. Appuyez sur une touche pour continuer...\n");
        getchar(); // Attendre que l'utilisateur voie le message
        cleanup();
        return -1;
    }

    Uint32 last_time = SDL_GetTicks();
    running = true; // Reset the running flag
    Partie* currentPartie = NULL;

    while (running) {
        Uint32 current_time = SDL_GetTicks();
        float delta_time = (current_time - last_time) / 1000.0f;
        last_time = current_time;

        handleEvents();
        update();
        render(0);
        SDL_Delay(16); //60fps
    }

    cleanup();
	system("cls");
    return 0;
}