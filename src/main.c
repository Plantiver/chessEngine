#include <SDL.h>
#include "game.h"
#include "renderer.h"
#include "events.h"
#include "board.h"
#include "piece.h"

int main() {
    SDL_Window* window = NULL;
    SDL_Renderer* renderer = NULL;
    Board board;
    SDL_Event e;
    int selectedX = -1, selectedY = -1;
    int turn = WHITE_PIECE; // Le jeu commence avec les blancs

    // Initialiser SDL et l'échiquier
    if (initSDL(&window, &renderer) < 0) {
        return -1;
    }

    initGame(&board);

    // Boucle principale du jeu
    int quit = 0;
    while (!quit) {
        quit = handleEvents(&e, &board, &selectedX, &selectedY, &turn);

        // Affichage de l'état du jeu
        renderGame(renderer, &board);

        // Attendre un peu pour rendre l'affichage fluide
        SDL_Delay(100);
    }

    // Nettoyer et fermer
    cleanUp(window, renderer, NULL);
    return 0;
}
