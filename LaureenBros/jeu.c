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
SDL_Texture* enemyTexture = NULL;
Mix_Chunk* piece = NULL;
Mix_Chunk* saut = NULL;
Mix_Chunk* sonFinJeu = NULL;


Ennemi enemies[MAX_ENEMIES];
Sprite player;
Sprite chateau;
bool running = true;
int enemyCount = 0;
float camera_x = 0.0f;
float camera_lock_x = 0.0f;
float invincibilityTimer = 0.0f;
bool isInvincible = false;

int map[MAP_HEIGHT][MAP_WIDTH] = {
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
    { 0, 0, 6, 6, 6, 0, 0, 6, 6, 0, 0, 6, 0, 0, 15, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 7, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 10, 10, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 6, 6, 6, 0, 0, 6, 6, 6, 0, 0, 0, 6, 6, 0, 15, 6, 0, 6, 0, 0, 6, 6, 0, 0, 6, 0, 0, 0, 0, 12, 13, 0, 0, 0 },
    { 0, 6, 0, 0, 0, 0, 6, 0, 0, 6, 0, 6, 0, 0, 15, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 7, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 10, 0, 0, 10, 0, 0, 10, 0, 0, 10, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 10, 10, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 6, 0, 0, 6, 0, 6, 0, 0, 6, 0, 6, 0, 0, 6, 15, 6, 0, 6, 0, 6, 15, 0, 6, 0, 6, 0, 0, 0, 0, 14, 11, 0, 0, 0 },
    { 0, 6, 0, 6, 6, 0, 6, 0, 0, 6, 0, 6, 0, 0, 15, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 10, 10, 10, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 0, 0, 1, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 10, 10, 0, 0, 0, 15, 0, 10, 0, 0, 10, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 6, 6, 6, 0, 0, 6, 6, 6, 0, 0, 6, 6, 6, 6, 15, 6, 0, 6, 0, 6, 15, 0, 6, 0, 6, 0, 0, 0, 0, 0, 11, 0, 0, 0 },
    { 0, 6, 0, 0, 6, 0, 6, 0, 0, 6, 0, 0, 0, 0, 15, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 1, 1, 1, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 7, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 15, 0, 18, 18, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 18, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 6, 0, 0, 6, 0, 6, 0, 6, 0, 0, 6, 0, 0, 6, 15, 6, 0, 6, 0, 6, 15, 0, 6, 0, 0, 0, 0, 0, 0, 0, 11, 0, 0, 0 },
    { 0, 0, 6, 6, 0, 0, 0, 6, 6, 0, 0, 6, 0, 0, 15, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 6, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 15, 10, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 15, 0, 0, 0, 10, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 15, 0, 0, 0, 0, 0, 0, 0, 10, 10, 15, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 6, 6, 6, 0, 0, 6, 0, 0, 6, 0, 6, 0, 0, 6, 15, 0, 6, 0, 0, 0, 6, 6, 0, 0, 6, 0, 0, 0, 0, 0, 11, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 10, 10, 0, 0, 0, 0, 0, 0, 7, 0, 0, 10, 1, 0, 0, 6, 6, 6, 6, 6, 0, 0, 0, 0, 0, 0, 10, 10, 10, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 0, 0, 0, 15, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 1, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 15, 0, 0, 0, 0, 18, 18, 0, 0, 0, 00, 0, 18, 18, 18, 18, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 15, 0, 0, 10, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 6, 6, 0, 0, 0, 1, 1, 1, 1, 1, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 18, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 0, 0, 0 },
    { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 4, 5, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 0, 15, 0, 0, 0, 0, 0, 0, 0, 18, 18, 0, 0, 0, 0, 0, 0, 0, 15, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 11, 0, 0, 0 },
    { 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 1, 1, 0, 0, 0, 10, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 2, 3, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 0, 2, 3, 0, 0, 0, 1, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 4, 5, 0, 0, 0, 0, 0, 0, 0, 0, 0, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 10, 0, 0, 0, 0, 11, 0, 0, 0 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 8, 8, 1, 2, 3, 1, 1, 1, 8, 8, 8, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 1, 1, 8, 8, 8, 1, 1, 1, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 8, 8, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 8, 8, 1, 8, 8, 1, 8, 8, 1, 8, 8, 1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 1, 8, 8, 8, 8, 8, 8, 1, 1, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 1, 2, 3, 1, 1, 1, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 1, 1, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 1, 9, 9, 1, 9, 9, 1, 9, 9, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 1, 1, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 ,0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 1, 2, 3, 1, 1, 1, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 1, 1, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 1, 9, 9, 1, 9, 9, 1, 9, 9, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 1, 1, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 1, 1, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 1, 2, 3, 1, 1, 1, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 1, 1, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 1, 9, 9, 1, 9, 9, 1, 9, 9, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 1, 1, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 1, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 },
    { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 1, 2, 3, 1, 1, 1, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 2, 3, 1, 1, 9, 9, 9, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 1, 9, 9, 1, 9, 9, 1, 9, 9, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 1, 1, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 9, 1, 1, 1, 2, 3, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 }
};

GameState* gameState = NULL;

void initSounds() {
    piece = Mix_LoadWAV("music/piece.mp3");
    if (!piece) {
        printf("Erreur chargement son piece: %s\n", Mix_GetError());
        return;
    }
    Mix_VolumeChunk(piece, 128);

    saut = Mix_LoadWAV("music/saut.mp3");
    if (!saut) {
        printf("Erreur chargement son saut: %s\n", Mix_GetError());
        return;
    }
    Mix_VolumeChunk(saut, 30);

    sonFinJeu = Mix_LoadWAV("music/sonFinJeu.mp3");
    if (!sonFinJeu) {
        printf("Erreur chargement son fin jeu: %s\n", Mix_GetError());
        return;
    }
    Mix_VolumeChunk(sonFinJeu, 128);
}

bool is_solid_tile(float x, float y, bool isInvincible) {
    int col = (int)(x / BLOCK_SIZE);
    int row = (int)(y / BLOCK_SIZE);
    if (!isInvincible) {
        return (col >= 0 && col < MAP_WIDTH && row >= 0 && row < MAP_HEIGHT) && (map[row][col] != 0) && (map[row][col] != 8) && (map[row][col] != 9) && (map[row][col] != 10) && (map[row][col] != 15) && (map[row][col] != 16);
    }
    else {
        return (col >= 0 && col < MAP_WIDTH && row >= 0 && row < MAP_HEIGHT) && (map[row][col] != 0) && (map[row][col] != 10) && (map[row][col] != 15) && (map[row][col] != 16);
    }
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



    SDL_Surface* enemySurface = IMG_Load("sprite/ennemies.png");
    if (!enemySurface) {
        printf("Erreur surface enemy");
        return false;
    }
    enemyTexture = SDL_CreateTextureFromSurface(renderer, enemySurface);
    SDL_FreeSurface(enemySurface);

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
    player.jumpForce = -11.5f;
    player.facingRight = true;
    player.isIdleAnimating = false;
    player.lookAlternate = false;
    player.wasMoving = false;
 
    initializeEnemies(2);
  

return true;
}

void initializeEnemies(int difficulte) {
    enemyCount = 0;
    for (int i = 0; i < MAX_ENEMIES; i++) {
        enemies[i].isActive = false;
    }

    // Add enemies at specific positions
    generateEnemy(400, 450);  // 
    generateEnemy(1800, 450); // Further in the level
    generateEnemy(1700, 450); // Further in the level
    generateEnemy(2650, 500); // Even further
    generateEnemy(3400, 450);
    generateEnemy(5500, 500);
    generateEnemy(9500, 450);
    generateEnemy(9600, 450);
    generateEnemy(9650, 450);
    if (difficulte == 1|| difficulte == 2) {
        generateEnemy(9980, 450);
        generateEnemy(10090, 450);
    }
    if (difficulte == 2) {
        generateEnemy(10590, 450);
        generateEnemy(11140, 450);
        generateEnemy(12440, 450);
    }
   

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
                gameState->coins += 10; // Increment the score
                printf("Piece collected! Total coins: %d\n", gameState->coins);
            }
            else if (map[row][col] == 16) {
                map[row][col] = 0;
                gameState->coins += 75;
                invincibilityTimer = 5;
                isInvincible = true;
            }
        }
    }
}

void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
            if (victoire == 1) {
                running = false;
            }
            else {
                victoire = 2;
                running = false;
            }
        if (event.type == SDL_KEYDOWN) {
            if ((event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_UP || event.key.keysym.sym == SDLK_z) && !player.isJumping) {
                if (saut) {
                    Mix_PlayChannel(-1, saut, 0);
                }
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
        player.velX = -4;
        player.facingRight = false;
    }
    if (keystate[SDL_SCANCODE_RIGHT] || keystate[SDL_SCANCODE_D]) {
        player.velX = 4;
        player.facingRight = true;
    }
}

// Modification de la fonction update pour corriger le problème de saut en glissant

void update() {
    invincibilityTimer -= 0.01;
    if (invincibilityTimer <= 0) isInvincible = false;

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
                camera_lock_x -= 400;
                camera_x = camera_lock_x;
                player.currentFrame = 12;
            }
            else {
                // Game Over
                running = false;
                victoire = 0;
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
        if (player.velX > 0 && !is_solid_tile(newX + 32, player.y + 32, isInvincible)) {
            player.x = newX;
        }
        else if (player.velX < 0 && !is_solid_tile(newX, player.y + 32, isInvincible)) {
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

    finDuJeu();
    collectPieces();

    float newX = player.x + player.velX;
    float newY = player.y + player.velY;
    gameState->distance = player.x/80;
    // Horizontale collision
    if (player.velX > 0 && !is_solid_tile(newX + 32, player.y + 32, isInvincible)) {
        player.x = newX;
    }
    else if (player.velX < 0 && !is_solid_tile(newX, player.y + 32, isInvincible)) {
        player.x = newX;
    }

    // Vérifie si le joueur est sur le sol avant d'appliquer la gravité
    bool wasOnGround = !player.isJumping;
    bool isOnGround = is_solid_tile(player.x + 16, player.y + 64 + 1, isInvincible);

    // Si le joueur était au sol mais ne l'est plus (glisse d'un bloc), 
    // considérer qu'il est en train de sauter/tomber
    if (wasOnGround && !isOnGround) {
        player.isJumping = true;
    }

    // Gravité
    player.velY += player.gravity;

    if (player.velY > 0) {
        if (is_solid_tile(player.x + 16, newY + 64, isInvincible)) {
            player.y = ((int)((newY + 64) / BLOCK_SIZE)) * BLOCK_SIZE - 64;
            player.velY = 0;
            player.isJumping = false;
        }
        else player.y = newY;
    }
    else if (player.velY < 0) {
        int headCol = (int)((player.x + 16) / BLOCK_SIZE);
        int headRow = (int)(newY / BLOCK_SIZE);
        // Did we hit a question-mark block?
        if (headRow >= 0 && headRow < MAP_HEIGHT &&
            headCol >= 0 && headCol < MAP_WIDTH &&
            map[headRow][headCol] == 7)
        {
            // Mark it used and spawn a star above it:
            map[headRow][headCol] = 17;                // used block
            if (headRow - 1 >= 0)
                map[headRow - 1][headCol] = 16;            // star pops out
            printf("Question mark block hit!\n");
        }

        // Now do the normal head collision response
        if (is_solid_tile(player.x + 16, newY, isInvincible)) {
            player.y = (headRow + 1) * BLOCK_SIZE;
            player.velY = 0;
        }
        else {
            player.y = newY;
        }
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
    updateEnemies();

    // Vérifier les collisions avec les ennemis
    for (int i = 0; i < enemyCount; i++) {
        if (enemies[i].isActive && checkPlayerEnemyCollision(i)) {
            enemies[i].isActive = false; // Désactive l'ennemi si écrasé
        }
    }
    float target_camera_x = player.x + 16 - SCREEN_WIDTH / 2;
    if (target_camera_x > camera_lock_x) camera_lock_x = target_camera_x;

    float max_camera_x = (MAP_WIDTH * BLOCK_SIZE) - SCREEN_WIDTH;
    if (camera_lock_x >= max_camera_x) camera_lock_x = max_camera_x;

    camera_x = camera_lock_x;
    if (player.x < camera_x) player.x = camera_x;
    float max_player_x = (MAP_WIDTH * BLOCK_SIZE) - 32;
    if (player.x > max_player_x) player.x = max_player_x;
}

void updateEnemies() {
    for (int i = 0; i < enemyCount; i++) {
        if (!enemies[i].isActive) continue;

        float newX = enemies[i].x + enemies[i].velX;

        // Vérification des collisions à gauche/droite
        bool leftCollision = false, rightCollision = false;
        int tileCol, tileRow;

        // Collision à gauche
        if (enemies[i].velX < 0) {
            tileCol = (int)(newX / BLOCK_SIZE);
            tileRow = (int)((enemies[i].y + enemies[i].height - 1) / BLOCK_SIZE);
            if (tileCol >= 0 && tileRow >= 0) {
                int tile = map[tileRow][tileCol];
                int tileAbove = (tileRow > 0) ? map[tileRow - 1][tileCol] : 0;
                leftCollision = (tile == 8 && tileAbove == 0) || is_solid_tile(newX, enemies[i].y + enemies[i].height - 1, isInvincible);
            }
        }

        // Collision à droite
        if (enemies[i].velX > 0) {
            tileCol = (int)((newX + enemies[i].width) / BLOCK_SIZE);
            tileRow = (int)((enemies[i].y + enemies[i].height - 1) / BLOCK_SIZE);
            if (tileCol < MAP_WIDTH && tileRow >= 0) {
                int tile = map[tileRow][tileCol];
                int tileAbove = (tileRow > 0) ? map[tileRow - 1][tileCol] : 0;
                rightCollision = (tile == 8 && tileAbove == 0) || is_solid_tile(newX + enemies[i].width, enemies[i].y + enemies[i].height - 1, isInvincible);
            }
        }

        // Vérifier le bord des plateformes
        tileCol = (int)((enemies[i].x + enemies[i].width / 2) / BLOCK_SIZE);
        tileRow = (int)((enemies[i].y + enemies[i].height + 5) / BLOCK_SIZE);
        bool groundCollision = is_solid_tile((enemies[i].x + enemies[i].width / 2), (enemies[i].y + enemies[i].height + 5), isInvincible);

        if (leftCollision || rightCollision || !groundCollision) {
            enemies[i].velX *= -1;
            enemies[i].facingRight = !enemies[i].facingRight;
        }
        else {
            enemies[i].x = newX;
        }

        // Animation
        enemies[i].animationTimer++;
        if (enemies[i].animationTimer >= ANIMATION_SPEED) {
            enemies[i].animationTimer = 0;
            enemies[i].currentFrame = enemies[i].currentFrame == 0 ? 1 : 0;
        }
    }
}

bool checkPlayerEnemyCollision(int enemyIndex) {
    Ennemi* enemy = &enemies[enemyIndex];
    if (!enemy->isActive) return false;

    // Calculate player and enemy hitboxes
    SDL_Rect playerRect = {
        (int)player.x,
        (int)player.y,
        32,  // Player width
        64   // Player height
    };

    SDL_Rect enemyRect = {
        (int)enemy->x,
        (int)enemy->y,
        enemy->width,
        enemy->height
    };

    // Check if player is falling onto enemy
    if (player.velY > 0 &&
        playerRect.x + 10 < enemyRect.x + enemyRect.w &&
        playerRect.x + playerRect.w - 10 > enemyRect.x &&
        playerRect.y + playerRect.h > enemyRect.y &&
        playerRect.y + playerRect.h < enemyRect.y + 20) {

        // Player jumped on enemy
        player.velY = player.jumpForce / 1.5; // Smaller bounce
        return true;
    }

    // Check if player collided with enemy from sides or bottom
    if (playerRect.x + 10 < enemyRect.x + enemyRect.w &&
        playerRect.x + playerRect.w - 10 > enemyRect.x &&
        playerRect.y < enemyRect.y + enemyRect.h &&
        playerRect.y + playerRect.h > enemyRect.y) {

        // Player hit enemy - reset position
        player.x = 100;
        player.y = SCREEN_HEIGHT - 480;
        player.velY = 0;
        player.isJumping = false;
        if (isInvincible == 0) {
            gameState->lives--;
        }
        if (gameState->lives <= 0) {
            running = false; // Arrête le jeu si le joueur n'a plus de vies
        }
    }

    return false;
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

// Version corrigée de renderEnemies() :
void renderEnemies() {
    for (int i = 0; i < enemyCount; i++) {
        if (!enemies[i].isActive) continue;

        if (enemies[i].x + enemies[i].width > camera_x &&
            enemies[i].x < camera_x + SCREEN_WIDTH) {

            SDL_Rect srcRect;
            if (enemies[i].currentFrame == 0) {
                srcRect = (SDL_Rect){ 27, 12, 20, 17 }; // marche goumpa 1
            }
            else if (enemies[i].currentFrame == 1) {
                srcRect = (SDL_Rect){ 54, 12, 19, 17 }; // marche goumpa 2
            }
            else {
                srcRect = (SDL_Rect){ 78, 20, 20, 9 }; // écrasé
            }

            SDL_Rect dstRect = {
                (int)(enemies[i].x - camera_x),
                (int)enemies[i].y,
                enemies[i].width,
                enemies[i].height
            };

            SDL_RendererFlip flip = enemies[i].facingRight==false ? SDL_FLIP_HORIZONTAL : SDL_FLIP_NONE;
            SDL_RenderCopyEx(renderer, enemyTexture, &srcRect, &dstRect, 0, NULL, flip);
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
    if (isInvincible) {
        SDL_SetTextureColorMod(currentTexture, 255, 255, 0); // Change color to yellow
        SDL_SetTextureAlphaMod(currentTexture, 128); // Set transparency
    }
    else {
        SDL_SetTextureColorMod(currentTexture, 255, 255, 255); // Reset color to white
        SDL_SetTextureAlphaMod(currentTexture, 255); // Reset transparency
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



void generateEnemy(float x, float y) {
    if (enemyCount < MAX_ENEMIES) {
        Ennemi* enemy = &enemies[enemyCount];
        enemy->x = x;
        enemy->y = y - enemy->height; // Ajustez selon la hauteur des plateformes
        enemy->velX = -1.5f;
      
        enemy->isActive = true;
        enemy->texture = enemyTexture;
        enemy->facingRight = false;
        enemy->width = 50;
        enemy->height = 50;
        enemy->currentFrame = 0;
        enemy->animationTimer = 0;
        enemyCount++;
    }
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
    renderEnemies();

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
    return victoire;
}

void cleanupSounds(void) {
    if (piece) {
        Mix_FreeChunk(piece);
        piece = NULL;
    }
    if (saut) {
        Mix_FreeChunk(saut);
        saut = NULL;
    }
    if (sonFinJeu) {
        Mix_FreeChunk(sonFinJeu);
        sonFinJeu = NULL;
    }
}