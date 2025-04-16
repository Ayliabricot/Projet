#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <stdbool.h>

// --- CONSTANTES ---
#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define BLOCK_SIZE 80

#define NUMBER_OF_TILES 8
#define MAP_WIDTH 90
#define MAP_HEIGHT 9
#define VIEW_WIDTH 16

#define ANIMATION_SPEED 10
#define CAMERA_SPEED 300.0f

// --- STRUCTURES ---
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
} Sprite;

// --- VARIABLES GLOBALES ---
SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* playerTexture = NULL;
SDL_Texture* tileTexture = NULL;

Sprite player;
bool running = true;
int map[MAP_HEIGHT][MAP_WIDTH];
float cameraX = 0.0f;

// --- INITIALISATION ---
bool initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;
    window = SDL_CreateWindow("Mario Map Fusion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) return false;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) return false;

    // Chargement tiles
    SDL_Surface* tileSurface = SDL_LoadBMP("tiles.bmp");
    if (!tileSurface) return false;
    tileTexture = SDL_CreateTextureFromSurface(renderer, tileSurface);
    SDL_FreeSurface(tileSurface);

    // Chargement sprite
    SDL_Surface* marioSurface = IMG_Load("png/mario.png");
    if (!marioSurface) return false;
    SDL_SetColorKey(marioSurface, SDL_TRUE, SDL_MapRGB(marioSurface->format, 0, 197, 10));
    playerTexture = SDL_CreateTextureFromSurface(renderer, marioSurface);
    SDL_FreeSurface(marioSurface);

    // Init player
    player.x = 100;
    player.y = 300;
    player.velX = player.velY = 0;
    player.texture = playerTexture;
    player.animationTimer = 0;
    player.currentFrame = 0;
    player.isJumping = false;
    player.gravity = 0.5f;
    player.jumpForce = -10.0f;
    player.facingRight = true;

    return true;
}

// --- MAP ---
void generate_map(int map[MAP_HEIGHT][MAP_WIDTH]) {
    for (int row = 0; row < MAP_HEIGHT; row++) {
        for (int col = 0; col < MAP_WIDTH; col++) {
            if (row >= 6) map[row][col] = 1; // Sol
            else map[row][col] = 0;
        }
    }
}

// --- EVENEMENTS ---
void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            running = false;
        else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
            running = false;

        if (event.type == SDL_KEYDOWN) {
            if ((event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_UP) && !player.isJumping) {
                player.velY = player.jumpForce;
                player.isJumping = true;
            }
        }
    }

    const Uint8* keys = SDL_GetKeyboardState(NULL);
    player.velX = 0;
    if (keys[SDL_SCANCODE_LEFT]) {
        player.velX = -3;
        player.facingRight = false;
    }
    if (keys[SDL_SCANCODE_RIGHT]) {
        player.velX = 3;
        player.facingRight = true;
    }
}

// --- UPDATE ---
void update(float deltaTime) {
    // Gravité
    if (player.isJumping)
        player.velY += player.gravity;

    player.x += player.velX;
    player.y += player.velY;

    // Collision sol (ligne Y + 64 pixels)
    int tileX = (int)(player.x + 16) / BLOCK_SIZE;
    int tileY = (int)(player.y + 63) / BLOCK_SIZE;
    if (tileY < MAP_HEIGHT && tileX < MAP_WIDTH && map[tileY][tileX] == 1) {
        player.y = tileY * BLOCK_SIZE - 64;
        player.velY = 0;
        player.isJumping = false;
    }

    // Animation
    if (player.velX != 0 || player.velY != 0) {
        player.animationTimer++;
        if (player.animationTimer >= ANIMATION_SPEED) {
            player.animationTimer = 0;
            player.currentFrame = (player.currentFrame + 1) % 3;
        }
    }
    else {
        player.currentFrame = 3; // Frame statique
    }

    // Caméra suit le joueur (centrée)
    cameraX = player.x - SCREEN_WIDTH / 2 + 16;
    if (cameraX < 0) cameraX = 0;
    float maxCameraX = (MAP_WIDTH - VIEW_WIDTH) * BLOCK_SIZE;
    if (cameraX > maxCameraX) cameraX = maxCameraX;
}

// --- RENDER ---
void render() {
    SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
    SDL_RenderClear(renderer);

    int texW, texH;
    SDL_QueryTexture(tileTexture, NULL, NULL, &texW, &texH);
    int tileW = texW / NUMBER_OF_TILES;

    int firstTile = (int)(cameraX / BLOCK_SIZE);
    int offsetX = (int)(cameraX) % BLOCK_SIZE;

    for (int row = 0; row < MAP_HEIGHT; row++) {
        for (int col = 0; col <= VIEW_WIDTH; col++) {
            int mapCol = firstTile + col;
            if (mapCol < MAP_WIDTH) {
                int tileIndex = map[row][mapCol];
                SDL_Rect src = { tileIndex * tileW, 0, tileW, texH };
                SDL_Rect dst = { col * BLOCK_SIZE - offsetX, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE };
                SDL_RenderCopy(renderer, tileTexture, &src, &dst);
            }
        }
    }

    // Mario sprite
    SDL_Rect frames[] = {
        {3, 43, 17, 26}, {22, 43, 17, 26}, {42, 43, 16, 26}, {62, 43, 17, 26}
    };
    SDL_Rect src = frames[player.currentFrame];
    SDL_Rect dst = { (int)(player.x - cameraX), (int)player.y, 32, 64 };

    SDL_RendererFlip flip = player.facingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    SDL_RenderCopyEx(renderer, player.texture, &src, &dst, 0, NULL, flip);

    SDL_RenderPresent(renderer);
}

// --- CLEANUP ---
void cleanup() {
    SDL_DestroyTexture(playerTexture);
    SDL_DestroyTexture(tileTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// --- MAIN ---
int main(int argc, char* argv[]) {
    if (!initialize()) return -1;
    generate_map(map);

    Uint32 lastTime = SDL_GetTicks();

    while (running) {
        Uint32 current = SDL_GetTicks();
        float delta = (current - lastTime) / 1000.0f;
        lastTime = current;

        handleEvents();
        update(delta);
        render();
        SDL_Delay(16); // ~60 FPS
    }

    cleanup();
    return 0;
}
