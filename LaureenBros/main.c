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
#include <SDL_image.h>
#include <stdbool.h>


#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define ANIMATION_SPEED 10  // Plus grand = animation plus lente

typedef struct {
    float x, y;//position mario
    float velX, velY; //vitesse mario
    SDL_Texture* texture; // juste l image en sah
    int animationTimer; 
    int currentFrame;
    bool isJumping;      // True si le joueur saute
    float gravity;       // Force de gravité
    float jumpForce;     // Puissance du saut
    bool facingRight; // verifie le sens du perso
} Sprite;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* playerTexture = NULL;
Sprite player;
bool running = true;

bool initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("SDL n'a pas pu s'initialiser (initialize fonction)! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    window = SDL_CreateWindow("Mario Animation", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);// creer une fenetre SDL à certaine dimension
    if (window == NULL) {
        printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED); // en gros ca va permettre de dessiner sans la fenetre sdl
    if (renderer == NULL) {
        printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Chargement de la texture avec transparence
    SDL_Surface* surface = IMG_Load("png/mario.png");// charge l'image
    if (surface == NULL) {
        printf("Erreur pour répurer l'image  (initialize fonction)! SDL_Error: %s\n", SDL_GetError());
        return false;
    }
    SDL_SetColorKey(surface, SDL_TRUE, SDL_MapRGB(surface->format, 0, 197, 10));// ca met le fond en transparent
    playerTexture = SDL_CreateTextureFromSurface(renderer, surface); // en gros ca va prendre de la place dans la ram pour les pixel ensuite ca les converti en texture
    SDL_FreeSurface(surface);// et la ca libere la surface pris dans la ram

    if (playerTexture == NULL) {
        printf("Failed to create texture! SDL_Error: %s\n", SDL_GetError());
        return false;
    }

    // Initialisation du joueur
    player.x = SCREEN_WIDTH / 2;
    player.y = SCREEN_HEIGHT / 2;
    player.velX = 0;
    player.velY = 0;
    player.texture = playerTexture;
    player.animationTimer = 0;
    player.currentFrame = 0;
    player.isJumping = false;
    player.gravity = 0.5f;    // Valeur de gravité (ajustable)
    player.jumpForce = -10.0f; // Valeur négative car en SDL, y augmente vers le bas
    player.facingRight = true;
    return true;
}
void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }

        // Détection du saut
        if (event.type == SDL_KEYDOWN) {
            if ((event.key.keysym.sym == SDLK_SPACE ||
                event.key.keysym.sym == SDLK_UP ||
                event.key.keysym.sym == SDLK_w) &&
                !player.isJumping) {
                player.velY = player.jumpForce;
                player.isJumping = true;
            }
        }
    }

    // Gestion des déplacements gauche/droite
    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    player.velX = 0; // On ne réinitialise que velX

    if (keystates[SDL_SCANCODE_LEFT] || keystates[SDL_SCANCODE_A]) {
        player.velX = -3;
        player.facingRight = false; // Regarde à gauche
    }
    if (keystates[SDL_SCANCODE_RIGHT] || keystates[SDL_SCANCODE_D]) {
        player.velX = 3;
        player.facingRight = true; // Regarde à droite
    }
}



void update() {
    // Mise à jour position
    player.x += player.velX;
    player.y += player.velY;

    // Collisions avec les bords
    if (player.x < 0) player.x = 0;
    if (player.y < 0) player.y = 0;
    if (player.x > SCREEN_WIDTH / 2 - 32) player.x = SCREEN_WIDTH / 2 - 32;
    if (player.y > SCREEN_HEIGHT - 64) player.y = SCREEN_HEIGHT - 64;

    // Animation seulement si le perso bouge
    if (player.velX != 0 || player.velY != 0) {
        // Réinitialiser à la frame 0 si on était sur la frame statique (3)
        if (player.currentFrame == 3) {
            player.currentFrame = 0;
        }

        player.animationTimer++;
        if (player.animationTimer >= ANIMATION_SPEED) {
            player.animationTimer = 0;
            if (player.currentFrame < 2) {
                player.currentFrame++;
            }
            else if (player.currentFrame == 2) {
                player.currentFrame = 0;
            }
        }
    }
    else {
        player.currentFrame = 3;  // Frame statique quand immobile
    }
    // Appliquer la gravité seulement si en train de sauter
    if (player.isJumping) {
        player.velY += player.gravity;
    }

    // Mise à jour position
    player.x += player.velX;
    player.y += player.velY;

    // Gestion du sol (empêche de tomber hors écran)
    if (player.y > SCREEN_HEIGHT - 64) {
        player.y = SCREEN_HEIGHT - 64;
        player.velY = 0;
        player.isJumping = false; // On a atterri
    }

}

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Définition des rectangles source pour chaque frame
    SDL_Rect frame0 = { 3, 43, 17, 26 };   // Première frame cours 
    SDL_Rect frame1 = { 22, 43, 17, 26 };  // Deuxième frame cours
    SDL_Rect frame2 = { 42,43,16,26 };// frame 3 cours
    SDL_Rect frame3 = { 3,246,16,26 };
    // Sélection du rectangle source selon currentFrame
    SDL_Rect srcRect;
    if (player.currentFrame == 0) {
        srcRect = frame0;
    }
    else if (player.currentFrame == 1) {
        srcRect = frame1;
    }
    else if (player.currentFrame == 2) { // currentFrame == 2
        srcRect = frame2;
    }
    else if (player.currentFrame == 3) { // currentFrame == 2
        srcRect = frame3;
    }

    // Rectangle destination (taille affichée à l'écran)
    SDL_Rect dstRect = { (int)player.x, (int)player.y, 32, 64 };

    // Détermination du flip en fonction de la vitesse horizontale
    SDL_RendererFlip flip = SDL_FLIP_NONE;
    if (player.velX < 0) {
        flip = SDL_FLIP_HORIZONTAL; // Inverse si va à gauche
    }
    // Si velX == 0, conserve le dernier flip

    // Rendu avec flip horizontal si nécessaire
    SDL_RenderCopyEx(
        renderer,               // Le renderer
        playerTexture,          // La texture
        &srcRect,              // Rectangle source (frame)
        &dstRect,              // Rectangle destination
        0.0,                   // Angle de rotation (0 = pas de rotation)
        NULL,                   // Centre de rotation (NULL = centre de la texture)
        flip                   // Flip horizontal ou aucun
    );

    SDL_RenderPresent(renderer);
}

void cleanup() {
    SDL_DestroyTexture(playerTexture);
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
        SDL_Delay(16);  // ~60 FPS
    }

    cleanup();
    return 0;
}