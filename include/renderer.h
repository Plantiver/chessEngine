#ifndef RENDERER_H
#define RENDERER_H

#include <SDL.h>
#include "board.h"

/* Initialiser SDL et la fenêtre */
int initSDL(SDL_Window** window, SDL_Renderer** renderer);

/* Afficher l'échiquier avec les pièces */
void renderGame(SDL_Renderer* renderer, const Board* board);

/* Charger une texture pour une image */
SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer);

/* Libérer les ressources SDL */
void cleanUp(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture);

#endif
