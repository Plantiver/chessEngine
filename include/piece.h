#ifndef PIECE_H
#define PIECE_H

// Déclaration anticipée de la structure Board
struct Board;

typedef enum { PAWN, KNIGHT, BISHOP, ROOK, QUEEN, KING } PieceType;
typedef enum { WHITE_PIECE, BLACK_PIECE } PieceColor;

typedef struct {
    PieceType type;
    PieceColor color;
    int x, y; // Position sur l'échiquier
} Piece;

/* Initialiser une pièce */
Piece* createPiece(PieceType type, PieceColor color, int x, int y);

/* Vérifier les mouvements valides d'une pièce */
int isValidMove(const Piece* piece, int toX, int toY, const struct Board* board); // Utilisation de la déclaration anticipée

/* Libérer la mémoire d'une pièce */
void freePiece(Piece* piece);

#endif
