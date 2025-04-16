#include <SDL.h>
#include <SDL_image.h>
#include <stdbool.h>
#include <stdio.h>

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720
#define BLOCK_SIZE 80
#define NUMBER_OF_TILES 8
#define MAP_WIDTH 19
#define MAP_HEIGHT 9
#define VIEW_WIDTH 16
#define ANIMATION_SPEED 10

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
} Sprite;

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;
SDL_Texture* tileTexture = NULL;
SDL_Texture* playerTexture = NULL;
Sprite player;
bool running = true;
float camera_x = 0.0f;
float camera_lock_x = 0.0f;
int map[MAP_HEIGHT][MAP_WIDTH];

void generate_map(int map[MAP_HEIGHT][MAP_WIDTH]) {
    for (int row = 0; row < MAP_HEIGHT; row++) {
        for (int col = 0; col < MAP_WIDTH; col++) {
            map[row][col] = (row >= 6) ? 1 : 0;
        }
    }
    map[6][5] = 2; map[6][6] = 3;
    map[7][5] = 2; map[7][6] = 3;
    map[8][5] = 2; map[8][6] = 3;
    map[5][5] = 4; map[5][6] = 5;
    map[4][8] = 6; map[4][9] = 7;
}

bool is_solid_tile(float x, float y) {
    int col = (int)(x / BLOCK_SIZE);
    int row = (int)(y / BLOCK_SIZE);
    return (col >= 0 && col < MAP_WIDTH && row >= 0 && row < MAP_HEIGHT) && (map[row][col] != 0);
}

bool initialize() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) return false;

    window = SDL_CreateWindow("Mario Fusion", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) return false;

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) return false;

    SDL_Surface* tileSurface = SDL_LoadBMP("tiles.bmp");
    if (!tileSurface) return false;
    tileTexture = SDL_CreateTextureFromSurface(renderer, tileSurface);
    SDL_FreeSurface(tileSurface);

    SDL_Surface* marioSurface = IMG_Load("png/mario.png");
    if (!marioSurface) return false;
    SDL_SetColorKey(marioSurface, SDL_TRUE, SDL_MapRGB(marioSurface->format, 0, 197, 10));
    playerTexture = SDL_CreateTextureFromSurface(renderer, marioSurface);
    SDL_FreeSurface(marioSurface);

    player.x = 100;
    player.y = SCREEN_HEIGHT - 240;
    player.velX = player.velY = 0;
    player.texture = playerTexture;
    player.animationTimer = player.idleTimer = 0;
    player.currentFrame = 3;
    player.isJumping = false;
    player.gravity = 0.5f;
    player.jumpForce = -10.0f;
    player.facingRight = true;
    player.isIdleAnimating = false;
    player.lookAlternate = false;
    player.wasMoving = false;

    generate_map(map);
    return true;
}

void handleEvents() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
            running = false;
        if (event.type == SDL_KEYDOWN) {
            if ((event.key.keysym.sym == SDLK_SPACE || event.key.keysym.sym == SDLK_UP) && !player.isJumping) {
                player.velY = player.jumpForce;
                player.isJumping = true;
                player.wasMoving = (player.velX != 0);
            }
        }
    }

    const Uint8* keystate = SDL_GetKeyboardState(NULL);
    player.velX = 0;

    if (keystate[SDL_SCANCODE_LEFT]) {
        player.velX = -3;
        player.facingRight = false;
    }
    if (keystate[SDL_SCANCODE_RIGHT]) {
        player.velX = 3;
        player.facingRight = true;
    }
}

void update() {
    float newX = player.x + player.velX;
    float newY = player.y + player.velY;

    // Horizontale collision
    if (player.velX > 0 && !is_solid_tile(newX + 32, player.y + 32)) player.x = newX;
    else if (player.velX < 0 && !is_solid_tile(newX, player.y + 32)) player.x = newX;

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
        player.currentFrame = (player.velY < 0) ? 8 : 9;
    }
    else if (player.velX != 0) {
        player.wasMoving = true;
        player.idleTimer = 0;
        player.animationTimer++;
        if (player.animationTimer >= ANIMATION_SPEED) {
            player.animationTimer = 0;
            player.currentFrame = (player.currentFrame + 1) % 3;
        }
    }
    else {
        player.idleTimer++;
        if (player.idleTimer > 180) {
            player.animationTimer++;
            if (player.animationTimer >= ANIMATION_SPEED * 3) {
                player.animationTimer = 0;
                if (player.currentFrame == 3) player.currentFrame = 4;
                else if (player.currentFrame == 4) player.currentFrame = 5;
                else if (player.currentFrame == 5) player.currentFrame = 6;
                else if (player.currentFrame == 6) player.currentFrame = 7;
                else player.currentFrame = 4;
            }
        }
        else {
            player.currentFrame = 3;
        }
    }

    if (player.y > SCREEN_HEIGHT) {
        player.x = 100;
        player.y = SCREEN_HEIGHT - 64;
        player.velY = 0;
        player.isJumping = false;
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

void render() {
    SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);
    SDL_RenderClear(renderer);

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
                SDL_Rect src = { tile_index * tile_width, 0, tile_width, tile_height };
                SDL_Rect dst = { col * BLOCK_SIZE - offset_x, row * BLOCK_SIZE, BLOCK_SIZE, BLOCK_SIZE };
                SDL_RenderCopy(renderer, tileTexture, &src, &dst);
            }
        }
    }

    SDL_Rect frames[] = {
        { 3, 43, 17, 24 }, { 22, 43, 17, 24 }, { 42, 43, 16, 24 }, { 3, 246, 16, 24 },
        { 3, 130, 17, 24 }, { 22, 130, 17, 24 }, { 42, 130, 16, 24 }, { 3, 130, 17, 24 },
        { 3, 72, 14, 24 }, { 22, 72, 14, 24 }
    };

    SDL_Rect srcRect = frames[player.currentFrame];
    SDL_Rect dstRect = { (int)(player.x - camera_x), (int)player.y, 32, 64 };

    SDL_RendererFlip flip = player.facingRight ? SDL_FLIP_NONE : SDL_FLIP_HORIZONTAL;
    SDL_RenderCopyEx(renderer, player.texture, &srcRect, &dstRect, 0, NULL, flip);

    SDL_RenderPresent(renderer);
}

void cleanup() {
    SDL_DestroyTexture(tileTexture);
    SDL_DestroyTexture(playerTexture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    if (!initialize()) {
        cleanup();
        return -1;
    }

    Uint32 last_time = SDL_GetTicks();
    while (running) {
        Uint32 current_time = SDL_GetTicks();
        float delta_time = (current_time - last_time) / 1000.0f;
        last_time = current_time;

        handleEvents();
        update();
        render();
        SDL_Delay(16);
    }

    cleanup();
    return 0;
}
