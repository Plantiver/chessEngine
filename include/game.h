#ifndef GAME_H
#define GAME_H

#include "board.h"

typedef enum { WHITE, BLACK } Player;

typedef struct {
    Board board;
    Player currentPlayer;
    int gameOver;
} Game;

/* Initialiser un jeu */
void initGame(Game* game);

/* Passer au joueur suivant */
void switchPlayer(Game* game);

/* Vérifier si le jeu est terminé (échec ou échec et mat) */
int isGameOver(const Game* game);

/* Terminer le jeu */
void endGame(Game* game);

#endif
