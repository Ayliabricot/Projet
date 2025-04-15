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
#include "gererParties.h"
#include <SDL.h>
#include <SDL_ttf.h>



#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600
#define PLAYER_SIZE 32
#define MOB_SIZE 32
#define MOB_COUNT 5

typedef struct {
    float x, y;
    float velX, velY;
    SDL_Texture* texture;
} Entity;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* playerTexture = NULL;
SDL_Texture* mobTexture = NULL;

Entity player;
Entity mobs[MOB_COUNT];
bool running = true;

bool initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Petit Jeu SDL", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Créer des textures simples (carrés colorés)
    playerTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, PLAYER_SIZE, PLAYER_SIZE);
    mobTexture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, MOB_SIZE, MOB_SIZE);

    SDL_SetRenderTarget(renderer, playerTexture);
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderTarget(renderer, mobTexture);
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
    SDL_RenderClear(renderer);

    SDL_SetRenderTarget(renderer, NULL);

    // Initialiser le joueur
    player.x = SCREEN_WIDTH / 2;
    player.y = SCREEN_HEIGHT / 2;
    player.velX = 0;
    player.velY = 0;
    player.texture = playerTexture;

    // Initialiser les ennemis
    srand(time(NULL));
    for (int i = 0; i < MOB_COUNT; i++) {
        mobs[i].x = rand() % (SCREEN_WIDTH - MOB_SIZE);
        mobs[i].y = rand() % (SCREEN_HEIGHT - MOB_SIZE);
        mobs[i].velX = (rand() % 3) - 1; // -1, 0 ou 1
        mobs[i].velY = (rand() % 3) - 1;
        mobs[i].texture = mobTexture;
    }

    return true;
}

void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }
    }

    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    player.velX = 0;
    player.velY = 0;

    if (keystates[SDL_SCANCODE_LEFT] || keystates[SDL_SCANCODE_Q]) {
        player.velX = -3;
    }
    if (keystates[SDL_SCANCODE_RIGHT] || keystates[SDL_SCANCODE_D]) {
        player.velX = 3;
    }
    if (keystates[SDL_SCANCODE_UP] || keystates[SDL_SCANCODE_Z]) {
        player.velY = -3;
    }
    if (keystates[SDL_SCANCODE_DOWN] || keystates[SDL_SCANCODE_S]) {
        player.velY = 3;
    }
}

void update() {
    // Mettre à jour le joueur
    player.x += player.velX;
    player.y += player.velY;

    // Garder le joueur dans l'écran
    if (player.x < 0) player.x = 0;
    if (player.y < 0) player.y = 0;
    if (player.x > SCREEN_WIDTH - PLAYER_SIZE) player.x = SCREEN_WIDTH - PLAYER_SIZE;
    if (player.y > SCREEN_HEIGHT - PLAYER_SIZE) player.y = SCREEN_HEIGHT - PLAYER_SIZE;

    // Mettre à jour les ennemis
    for (int i = 0; i < MOB_COUNT; i++) {
        mobs[i].x += mobs[i].velX;
        mobs[i].y += mobs[i].velY;

        // Rebond des ennemis
        if (mobs[i].x < 0 || mobs[i].x > SCREEN_WIDTH - MOB_SIZE) {
            mobs[i].velX *= -1;
        }
        if (mobs[i].y < 0 || mobs[i].y > SCREEN_HEIGHT - MOB_SIZE) {
            mobs[i].velY *= -1;
        }
    }
}

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Dessiner le joueur
    SDL_Rect playerRect = { (int)player.x, (int)player.y, PLAYER_SIZE, PLAYER_SIZE };
    SDL_RenderCopy(renderer, player.texture, NULL, &playerRect);

    // Dessiner les ennemis
    for (int i = 0; i < MOB_COUNT; i++) {
        SDL_Rect mobRect = { (int)mobs[i].x, (int)mobs[i].y, MOB_SIZE, MOB_SIZE };
        SDL_RenderCopy(renderer, mobs[i].texture, NULL, &mobRect);
    }

    SDL_RenderPresent(renderer);
}

void cleanup() {
    SDL_DestroyTexture(playerTexture);
    SDL_DestroyTexture(mobTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* args[]) {
    if (!initialize()) {
        cleanup();
        return -1;
    }

    while (running) {
        handleEvents();
        update();
        render();
        SDL_Delay(16); // Environ 60 FPS
    }

    cleanup();
    return 0;
}