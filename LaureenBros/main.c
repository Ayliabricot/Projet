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
    int idleTimer;       // Timer pour l'animation d'attente
    bool isIdleAnimating; // Si on est en train de faire l'animation d'attente
    bool lookAlternate;
    bool wasMoving;
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
    player.gravity = 0.4f;    // Valeur de gravité (ajustable)
    player.jumpForce = -12.0f; // Valeur négative car en SDL, y augmente vers le bas
    player.facingRight = true;
    player.idleTimer = 0;
    player.isIdleAnimating = false;
    player.lookAlternate = false;
    player.wasMoving = false;
    return true;
}
void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            running = false;
        }

        if (event.type == SDL_KEYDOWN) {
            if ((event.key.keysym.sym == SDLK_SPACE ||
                event.key.keysym.sym == SDLK_UP ||
                event.key.keysym.sym == SDLK_w) &&
                !player.isJumping) {
                player.velY = player.jumpForce;
                player.isJumping = true;
                player.wasMoving = (player.velX != 0); // Enregistre si on bougeait avant de sauter
            }
        }
    }

    const Uint8* keystates = SDL_GetKeyboardState(NULL);
    player.velX = 0;

    if (keystates[SDL_SCANCODE_LEFT] || keystates[SDL_SCANCODE_A]) {
        player.velX = -3;
        player.facingRight = false;
    }
    if (keystates[SDL_SCANCODE_RIGHT] || keystates[SDL_SCANCODE_D]) {
        player.velX = 3;
        player.facingRight = true;
    }
}

void update() {
    // Appliquer la gravité seulement si en train de sauter
    if (player.isJumping) {
        player.velY += player.gravity;
    }

    // Mise à jour position
    player.x += player.velX;
    player.y += player.velY;

    // Collisions avec les bords
    if (player.x < 0) player.x = 0;
    if (player.y < 0) player.y = 0;
    if (player.x > SCREEN_WIDTH / 2 - 32) player.x = SCREEN_WIDTH / 2 - 32;
    if (player.y > SCREEN_HEIGHT - 64) {
        player.y = SCREEN_HEIGHT - 64;
        player.velY = 0;
        player.isJumping = false;
        player.wasMoving = false;
    }

    // Gestion de l'animation
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
}

void render() {
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderClear(renderer);

    // Définition des rectangles source
    SDL_Rect frame0 = { 3, 43, 17, 26 };   // debout
    SDL_Rect frame1 = { 22, 43, 17, 26 };  // Course frame 1
    SDL_Rect frame2 = { 42, 43, 16, 26 };  // Course frame 2
    SDL_Rect frame3 = { 3, 246, 16, 26 };  // Course frame 3
    SDL_Rect frame4 = { 3, 130, 17, 26 };  // Idle frame 1 (face)
    SDL_Rect frame5 = { 22, 130, 17, 26 }; // Idle frame 2 (côté droit)
    SDL_Rect frame6 = { 42, 130, 16, 26 }; // Idle frame 3 (dos)
    SDL_Rect frame8 = { 3, 72, 14, 26 };   // Saut haut
    SDL_Rect frame9 = { 22, 72, 14, 26 };  // Saut bas

    SDL_Rect srcRect;
    switch (player.currentFrame) {
    case 0: srcRect = frame0; break;
    case 1: srcRect = frame1; break;
    case 2: srcRect = frame2; break;
    case 3: srcRect = frame3; break;
    case 4: srcRect = frame4; break;
    case 5: srcRect = frame5; break;
    case 6: srcRect = frame6; break;
    case 8: srcRect = frame8; break;
    case 9: srcRect = frame9; break;
    default: srcRect = frame3; break;
    }

    SDL_Rect dstRect = { (int)player.x, (int)player.y, 32, 64 };

    // Gestion du flip
    SDL_RendererFlip flip = SDL_FLIP_NONE;

    // Pendant le saut, on garde la dernière orientation
    if (player.isJumping) {
        if (!player.facingRight) {
            flip = SDL_FLIP_HORIZONTAL;
        }
    }
    else {
        // Sinon, on suit la direction actuelle
        if ((player.velX < 0) ||
            (player.currentFrame == 7) ||
            (!player.facingRight && (player.currentFrame == 5 || player.currentFrame == 6))) {
            flip = SDL_FLIP_HORIZONTAL;
        }
    }

    // Pour la frame 7 (regarde à gauche), on utilise frame5 mais flipée
    if (player.currentFrame == 7) {
        srcRect = frame5;
    }

    SDL_RenderCopyEx(renderer, playerTexture, &srcRect, &dstRect, 0.0, NULL, flip);
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