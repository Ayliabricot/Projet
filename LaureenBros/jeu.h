#ifndef JEU
#define JEU

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <stdbool.h>
#include <stdio.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define BLOCK_SIZE 50
#define NUMBER_OF_TILES 11
#define MAP_WIDTH 226
#define MAP_HEIGHT 15
#define VIEW_WIDTH 44
#define ANIMATION_SPEED 10
#define SAVE_FILE "save.txt"  // Nouvelle constante pour le fichier de sauvegarde

typedef struct {
    float x, y;
    float velX, velY;
    SDL_Texture* texture;
    int animationTimer;
    int currentFrame;
    bool isJumping;
    float gravity;
    float jumpForce;
    bool facingRight;
    int idleTimer;
    bool isIdleAnimating;
    bool lookAlternate;
    bool wasMoving;
    bool isDying;         // True pendant l'animation de mort
    bool isRespawning;    // True pendant l'animation de réapparition
    float respawnTimer;   // Timer pour l'animation de réapparition
    float swingOffset;    // Décalage oscillation parachute
    float parachuteYOffset;
    float deathTimer;
} Sprite;

typedef struct {
    int x;
    int y;
} Personnage;

typedef struct {
    int x;
    int y;
} Ennemi;

typedef struct {
    int lives;
    int coins;
    int world;
    char save[50];
    int stage;
    int distance;
} GameState;




extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* tileTexture;
extern SDL_Texture* playerTexture;
extern Sprite player;
extern bool running;
extern float camera_x;
extern float camera_lock_x;
extern int map[MAP_HEIGHT][MAP_WIDTH];

bool is_solid_tile(float x, float y);
bool initialize();
void handleEvents();
void update();
void renderMario();
void renderMap();
void render(int* choixPerso);
void cleanup();
int lancerJeu(int argc, char* argv[]);

// Nouvelles fonctions pour la sauvegarde
void saveGame();
void loadGame();

#endif