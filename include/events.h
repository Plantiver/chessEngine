#ifndef EVENTS_H
#define EVENTS_H

#include <SDL.h>
#include "game.h"
#include "board.h"

/* Gérer les événements (clics souris, déplacements de pièces) */
void handleEvents(Game* game, SDL_Event* event);

/* Gérer le clic de souris et déplacer une pièce */
int handleMouseClick(Game* game, int mouseX, int mouseY);

#endif
