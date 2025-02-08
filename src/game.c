#include "game.h"
#include "board.h"
#include "piece.h"
#include <stdio.h>
#include <stdlib.h>

// Initialiser l'échiquier avec les pièces
void initGame(Board* board) {
    // Initialisation des pièces noires
    board->squares[0][0] = createPiece(ROOK, BLACK_PIECE, 0, 0);
    board->squares[0][1] = createPiece(KNIGHT, BLACK_PIECE, 1, 0);
    board->squares[0][2] = createPiece(BISHOP, BLACK_PIECE, 2, 0);
    board->squares[0][3] = createPiece(QUEEN, BLACK_PIECE, 3, 0);
    board->squares[0][4] = createPiece(KING, BLACK_PIECE, 4, 0);
    board->squares[0][5] = createPiece(BISHOP, BLACK_PIECE, 5, 0);
    board->squares[0][6] = createPiece(KNIGHT, BLACK_PIECE, 6, 0);
    board->squares[0][7] = createPiece(ROOK, BLACK_PIECE, 7, 0);
    for (int i = 0; i < BOARD_SIZE; i++) {
        board->squares[1][i] = createPiece(PAWN, BLACK_PIECE, i, 1);
    }

    // Initialisation des pièces blanches
    for (int i = 0; i < BOARD_SIZE; i++) {
        board->squares[6][i] = createPiece(PAWN, WHITE_PIECE, i, 6);
    }
    board->squares[7][0] = createPiece(ROOK, WHITE_PIECE, 0, 7);
    board->squares[7][1] = createPiece(KNIGHT, WHITE_PIECE, 1, 7);
    board->squares[7][2] = createPiece(BISHOP, WHITE_PIECE, 2, 7);
    board->squares[7][3] = createPiece(QUEEN, WHITE_PIECE, 3, 7);
    board->squares[7][4] = createPiece(KING, WHITE_PIECE, 4, 7);
    board->squares[7][5] = createPiece(BISHOP, WHITE_PIECE, 5, 7);
    board->squares[7][6] = createPiece(KNIGHT, WHITE_PIECE, 6, 7);
    board->squares[7][7] = createPiece(ROOK, WHITE_PIECE, 7, 7);
}

// Vérifier si un mouvement est valide (simplifié ici, à améliorer selon les règles du jeu)
int isValidMove(const Piece* piece, int toX, int toY, const Board* board) {
    if (toX < 0 || toX >= BOARD_SIZE || toY < 0 || toY >= BOARD_SIZE) {
        return 0;  // Hors de l'échiquier
    }

    // Vérification d'une case occupée par une pièce de la même couleur
    Piece* targetPiece = board->squares[toY][toX];
    if (targetPiece != NULL && targetPiece->color == piece->color) {
        return 0;  // La case est occupée par une pièce de la même couleur
    }

    // Pour l'instant, on autorise seulement des déplacements simples pour la démonstration
    // TODO : Implémenter des règles spécifiques pour chaque type de pièce
    return 1;  // Le mouvement est valide (à affiner)
}

// Déplacer une pièce sur l'échiquier
void movePiece(Board* board, int fromX, int fromY, int toX, int toY) {
    // Vérifier que la pièce existe et que le mouvement est valide
    Piece* piece = board->squares[fromY][fromX];
    if (piece == NULL || !isValidMove(piece, toX, toY, board)) {
        printf("Mouvement invalide\n");
        return;
    }

    // Déplacer la pièce
    board->squares[toY][toX] = piece;
    board->squares[fromY][fromX] = NULL;
    piece->x = toX;
    piece->y = toY;
}

// Afficher l'état actuel de l'échiquier dans la console (pour débogage)
void printBoard(const Board* board) {
    for (int y = 0; y < BOARD_SIZE; y++) {
        for (int x = 0; x < BOARD_SIZE; x++) {
            if (board->squares[y][x] == NULL) {
                printf(" . ");
            } else {
                // Affichage du type de la pièce (par exemple "K" pour roi, "Q" pour reine)
                switch (board->squares[y][x]->type) {
                    case PAWN: printf(" P "); break;
                    case KNIGHT: printf(" N "); break;
                    case BISHOP: printf(" B "); break;
                    case ROOK: printf(" R "); break;
                    case QUEEN: printf(" Q "); break;
                    case KING: printf(" K "); break;
                }
            }
        }
        printf("\n");
    }
}
