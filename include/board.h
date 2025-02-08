#ifndef BOARD_H
#define BOARD_H

#include "piece.h"

#define BOARD_SIZE 8

typedef struct {
    Piece* squares[BOARD_SIZE][BOARD_SIZE]; // Tableau pour les cases de l'échiquier
} Board;

/* Initialiser l'échiquier */
void initBoard(Board* board);

/* Afficher l'échiquier */
void renderBoard(const Board* board);

/* Mettre à jour la position d'une pièce sur l'échiquier */
void movePiece(Board* board, int fromX, int fromY, int toX, int toY);

#endif
