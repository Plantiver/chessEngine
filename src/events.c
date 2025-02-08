#include "events.h"
#include "game.h"
#include "board.h"
#include "piece.h"
#include <SDL.h>
#include <stdio.h>

// Fonction pour gérer les événements SDL
int handleEvents(SDL_Event* e, Board* board, int* selectedX, int* selectedY, int* turn) {
    // Parcourir tous les événements SDL
    while (SDL_PollEvent(e) != 0) {
        if (e->type == SDL_QUIT) {
            return 1;  // Quitter l'application si l'utilisateur ferme la fenêtre
        }

        // Gérer les événements de souris
        if (e->type == SDL_MOUSEBUTTONDOWN) {
            // Récupérer la position de la souris
            int mouseX = e->button.x;
            int mouseY = e->button.y;

            // Convertir la position de la souris en coordonnées sur l'échiquier
            int squareSize = 100;  // Taille d'une case de l'échiquier (à adapter si besoin)
            int x = mouseX / squareSize;
            int y = mouseY / squareSize;

            if (*selectedX == -1 && *selectedY == -1) {
                // Sélectionner une pièce si aucune n'est sélectionnée
                Piece* piece = board->squares[y][x];
                if (piece != NULL && piece->color == *turn) {
                    *selectedX = x;
                    *selectedY = y;
                }
            } else {
                // Déplacer la pièce si une pièce est sélectionnée
                Piece* selectedPiece = board->squares[*selectedY][*selectedX];
                if (isValidMove(selectedPiece, x, y, board)) {
                    movePiece(board, *selectedX, *selectedY, x, y);

                    // Passer au tour suivant
                    *turn = (*turn == WHITE_PIECE) ? BLACK_PIECE : WHITE_PIECE;
                }

                // Réinitialiser la sélection
                *selectedX = -1;
                *selectedY = -1;
            }
        }
    }

    return 0;  // Continuer le jeu si aucun événement de fermeture
}
