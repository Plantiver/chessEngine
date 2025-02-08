#include <SDL.h>
#include <stdio.h>
#include "renderer.h"
#include "board.h"

// Fonction d'initialisation de SDL
int initSDL(SDL_Window** window, SDL_Renderer** renderer) {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        printf("Erreur d'initialisation SDL : %s\n", SDL_GetError());
        return -1;
    }

    // Créer une fenêtre SDL
    *window = SDL_CreateWindow("Jeu d'Échecs", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 800, 800, SDL_WINDOW_SHOWN);
    if (*window == NULL) {
        printf("Erreur de création de la fenêtre : %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    // Créer un renderer pour afficher la fenêtre
    *renderer = SDL_CreateRenderer(*window, -1, SDL_RENDERER_ACCELERATED);
    if (*renderer == NULL) {
        printf("Erreur de création du renderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(*window);
        SDL_Quit();
        return -1;
    }

    return 0; // Initialisation réussie
}

// Fonction pour charger une texture
SDL_Texture* loadTexture(const char* path, SDL_Renderer* renderer) {
    SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, SDL_LoadBMP(path));
    if (texture == NULL) {
        printf("Erreur de chargement de la texture : %s\n", SDL_GetError());
    }
    return texture;
}

// Fonction pour afficher l'échiquier et ses pièces
void renderGame(SDL_Renderer* renderer, const Board* board) {
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255); // Couleur de fond (blanc)
    SDL_RenderClear(renderer); // Effacer la fenêtre avec la couleur de fond

    // Dessiner l'échiquier (simplifié en dessinant des cases de couleur alternée)
    int squareSize = 100; // Taille d'une case de l'échiquier
    for (int row = 0; row < BOARD_SIZE; row++) {
        for (int col = 0; col < BOARD_SIZE; col++) {
            SDL_Rect square = { col * squareSize, row * squareSize, squareSize, squareSize };
            if ((row + col) % 2 == 0) {
                SDL_SetRenderDrawColor(renderer, 240, 217, 181, 255); // Case claire
            } else {
                SDL_SetRenderDrawColor(renderer, 121, 85, 59, 255); // Case foncée
            }
            SDL_RenderFillRect(renderer, &square); // Dessiner la case

            // Rendu des pièces (à faire plus tard en utilisant les textures)
            // Cette section sera complétée en ajoutant les pièces sur l'échiquier.
        }
    }

    SDL_RenderPresent(renderer); // Actualiser l'affichage
}

// Fonction de nettoyage des ressources SDL
void cleanUp(SDL_Window* window, SDL_Renderer* renderer, SDL_Texture* texture) {
    if (texture != NULL) {
        SDL_DestroyTexture(texture);
    }
    if (renderer != NULL) {
        SDL_DestroyRenderer(renderer);
    }
    if (window != NULL) {
        SDL_DestroyWindow(window);
    }
    SDL_Quit(); // Fermer SDL
}
