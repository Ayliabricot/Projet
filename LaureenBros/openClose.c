#include <SDL.h>
#include <SDL_ttf.h>

void fermerConsoleC() {
    
    system("cls");  
    exit(0);        
}


void ouvrirConsoleSDL() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur SDL: %s\n", SDL_GetError());
        exit(-1);
    }

    SDL_Window* window = SDL_CreateWindow("Mon jeu SDL",
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        1280, 720, SDL_WINDOW_SHOWN);
    if (!window) {
        printf("Erreur création fenêtre SDL: %s\n", SDL_GetError());
        SDL_Quit();
        exit(-1);
    }


    SDL_Event event;
    int quit = 0;
    while (!quit) {
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = 1;
            }
        }
       
    }

    SDL_DestroyWindow(window);
    SDL_Quit();
}