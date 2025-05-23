#ifndef JEU
#define JEU

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <stdbool.h>
#include <stdio.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define BLOCK_SIZE 50
#define NUMBER_OF_TILES 19
#define MAP_WIDTH 226
#define MAP_HEIGHT 15
#define VIEW_WIDTH 44
#define ANIMATION_SPEED 10
#define SAVE_FILE "save.txt"  // Nouvelle constante pour le fichier de sauvegarde
#define MAX_ENEMIES 20 

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
    bool goomba;
} Sprite;

typedef struct {
    int x;
    int y;
} Personnage;



typedef struct {
    int lives;
    int coins;
    int world;
    char save[50];
    int stage;
    int distance;
} GameState;

typedef struct {
    float x, y;
    float velX;
    bool isActive;
    SDL_Texture* texture;
    bool facingRight;
    int width;
    int height;
    int currentFrame;       // Frame actuelle de l'animation
    int animationTimer;     // Compteur pour changer de frame
    int totalFrames;   // Nombre total de frames dans l'animation
 
} Ennemi;


// Enemy functions
void initializeEnemies(Partie* partie);
void generateEnemy(float x, float y, Partie* partie);
void updateEnemies(Partie* partie);
void renderEnemies();
bool checkPlayerEnemyCollision(int enemyIndex);



extern SDL_Window* window;
extern SDL_Renderer* renderer;
extern SDL_Texture* tileTexture;
extern SDL_Texture* playerTexture;
extern Sprite player;
void initSounds(void);
extern bool running;
extern float camera_x;
extern float camera_lock_x;
extern int map[MAP_HEIGHT][MAP_WIDTH];
extern Partie* currentPartie;

bool is_deadly_tile(float x, float y);

bool is_solid_tile(float x, float y, bool isInvincible);
bool is_ground_near(float x, float y);
bool canEnemyMoveForward(Ennemi* enemy);
bool initialize(Partie* partie);
void handleEvents(Partie* partie);
void update(Partie* partie);
void collectPieces();
void finDuJeu(void);
void renderMario();
void renderMap();
void render(int* choixPerso);
void renderHUD();
void cleanup();
int lancerJeu(int argc, char* argv[], Partie* partie);

// Nouvelles fonctions pour la sauvegarde
void saveGame();
void loadGame();
void saveGameWithPseudo(char* pseudo); // Declare save function
void loadGameWithPseudo(char* pseudo);

void cleanupSounds(void);

#endif