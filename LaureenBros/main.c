#include <SDL.h>
#include <stdio.h>

/*#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include "ecran.h"
#include "AffichageMenu.h"
#include <string.h>
#include "placementTexte.h"
#include <time.h>
#include "quitterJeu.h"
*/

#define SCREEN_WIDTH 1280    // -¤ Largeur de la fenêtre en pixel ¤-
#define SCREEN_HEIGHT 720    // -¤ Hauteur de la fenêtre en pixel ¤-

#define NUMBER_OF_TILES 8    // -¤ Sur l'image.bmp ¤-
#define BLOCK_SIZE 80        // -¤ En pixel ¤-

#define MAP_WIDTH 90
#define MAP_HEIGHT 9
#define VIEW_WIDTH 16        // -¤ Nombre de tuiles affichées horizontalement ¤-

#define CAMERA_SPEED 300     // -¤ Vitesse de déplacement de la caméra (pixels/sec) ¤-

void generate_map(int map[MAP_HEIGHT][MAP_WIDTH]) {
    for (int row = 0; row < MAP_HEIGHT; row++) {
        for (int col = 0; col < MAP_WIDTH; col++) {
            if (row >= 6)
                map[row][col] = 1;  // -¤ Sol ¤-
            else
                map[row][col] = 0;  // -¤ Ciel ¤-
        }
    }
}

int main(int argc, char* argv[]) {
	
	/*
	
	//MENU 
	
	Partie** tableau = creerTableau();
	char option[6][40] = { "1. Règles du jeu","2. Choisir difficulté","3. Nouvelle partie","4. Continuer partie","5. Accéder au tableau des scores","6. Quitter le jeu" };

	Ecran* ecran = definirEcran();
	int touche = 0;
	int* choix = malloc(sizeof(int));
	if (choix == NULL) {
		printf("Erreur d'allocation mémoire\n");
		return 1;
	}
	*choix = 0;


	afficherMenu(ecran, touche, choix,option,tableau);

	while (1) {
		if (_kbhit()) {
			touche = _getch();


			system("cls");
			afficherMenu(ecran, touche, choix,option,tableau);
		}


	}
	free(choix);
	choix = NULL;
	return 0;
	*/


    if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)  // -¤ Initialisation de l'affichage et audio en une fois ¤-
    {
        printf("Erreur d'initialisation de SDL : %s\n", SDL_GetError());
        return 1;
    }

    SDL_Window* window = SDL_CreateWindow(
        "LaureenBros",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        SCREEN_WIDTH,          // -¤ Largeur ¤-
        SCREEN_HEIGHT,         // -¤ Hauteur ¤-
        SDL_WINDOW_SHOWN
    );
    if (!window) {
        printf("Erreur de création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        printf("Erreur de création du renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Surface* surface = SDL_LoadBMP("tiles.bmp");
    if (!surface) {
        printf("SDL_LoadBMP Error: %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
    if (!texture) {
        printf("Erreur de création de la texture : %s\n", SDL_GetError());
        SDL_FreeSurface(surface);
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }
    SDL_FreeSurface(surface);

    int tex_width, tex_height;
    SDL_QueryTexture(texture, NULL, NULL, &tex_width, &tex_height);
    int tile_width = tex_width / NUMBER_OF_TILES;  // -¤ Largeur d'une tuile dans la texture ¤-

    float camera_x = 0.0f;   // -¤ Position de la caméra en pixels ¤-
    int map[MAP_HEIGHT][MAP_WIDTH];
    generate_map(map);

    Uint32 last_time = SDL_GetTicks();  // -¤ Pour delta_time ¤-

    SDL_Event event;
    int running = 1;

    while (running) {
        Uint32 current_time = SDL_GetTicks();
        float delta_time = (current_time - last_time) / 1000.0f;
        last_time = current_time;

        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = 0;
            else if (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
                running = 0;
        }

        const Uint8* keystate = SDL_GetKeyboardState(NULL);

        // -¤ Gestion des touches ← → avec caméra fluide en pixels ¤-
        if (keystate[SDL_SCANCODE_RIGHT]) {
            camera_x += CAMERA_SPEED * delta_time;
            float max_camera_x = (MAP_WIDTH - VIEW_WIDTH) * BLOCK_SIZE;
            if (camera_x > max_camera_x)
                camera_x = max_camera_x;
        }
        if (keystate[SDL_SCANCODE_LEFT]) {
            camera_x -= CAMERA_SPEED * delta_time;
            if (camera_x < 0)
                camera_x = 0;
        }

        SDL_SetRenderDrawColor(renderer, 100, 149, 237, 255);  // -¤ Bleu ciel ¤-
        SDL_RenderClear(renderer);

        int first_tile = (int)(camera_x / BLOCK_SIZE);               // -¤ Tuile de départ ¤-
        int offset_x = (int)(camera_x) % BLOCK_SIZE;                 // -¤ Décalage pixel ¤-

        for (int row = 0; row < MAP_HEIGHT; row++) {
            for (int col = 0; col <= VIEW_WIDTH; col++) {
                int tile_col = first_tile + col;

                if (tile_col >= 0 && tile_col < MAP_WIDTH) {
                    int tile_index = map[row][tile_col];

                    SDL_Rect src_rect = {
                        .x = tile_index * tile_width,
                        .y = 0,
                        .w = tile_width,
                        .h = tex_height
                    };

                    SDL_Rect dst_rect = {
                        .x = col * BLOCK_SIZE - offset_x,
                        .y = row * BLOCK_SIZE,
                        .w = BLOCK_SIZE,
                        .h = BLOCK_SIZE
                    };

                    SDL_RenderCopy(renderer, texture, &src_rect, &dst_rect);
                }
            }
        }

        SDL_RenderPresent(renderer);
        SDL_Delay(1000 / 60);  // -¤ Taux de rafraichissement ¤-
    }

    // -¤ Libération des ressources ¤-
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}


//dsqjfdn



//mettre des while(valeur= ...)  ca va dans un menu










