#include <stdio.h>
#include <stdlib.h>
#include <SDL.h>
#include <cstdlib>
#include "map.h"

char** create_map(int rows, int cols) {
    char** map = malloc(rows * sizeof(char*));
    if (!map) {
        perror("malloc failed");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < rows; i++) {
        map[i] = malloc((cols + 1) * sizeof(char));
        if (!map[i]) {
            perror("malloc failed");
            exit(EXIT_FAILURE);
        }

        for (int j = 0; j < cols; j++) {
            map[i][j] = '.';
        }
        map[i][cols] = '\0';
    }

    return map;
}

void display_map() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur d'initialisation de SDL: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    SDL_Window* window = SDL_CreateWindow("Example: 0", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1280, 720, 0);
    if (!window) {
        fprintf(stderr, "Erreur création fenêtre: %s\n", SDL_GetError());
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);
    if (!renderer) {
        fprintf(stderr, "Erreur création renderer: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        exit(EXIT_FAILURE);
    }

    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderClear(renderer);
    SDL_RenderPresent(renderer);

    SDL_Delay(2000);

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}


void free_map(char** map, int rows) {
    for (int i = 0; i < rows; i++) {
        free(map[i]);
    }
    free(map);
}