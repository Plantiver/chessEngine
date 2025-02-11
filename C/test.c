#include <stdio.h>
#include <stdlib.h>

#define ull unsigned long long
#define bool short
#define true 1
#define false 0

typedef struct {
    ull p;
    ull k;
    ull q;
    ull n;
    ull b;
    ull r;
    ull black;
    bool kCastling;
    bool qCastling;

    ull P;
    ull K;
    ull Q;
    ull N;
    ull B;
    ull R;
    ull white;
    bool KCastling;
    bool QCastling;

    bool whiteSturn;
    ull enPassant;
    short fiftyMoveCounter;
} position;

typedef struct {
    position* first;
    int length;
} MoveSet;




/* 

    Les deux fonctions suivantes viennent de chat-gpt, parce que l'interprétation d'une fen, j'avais la flemmmmmmmmmeeeeeeeeeeeeeee
    (c'est certainement pour ça qu'elle sont aussi bien documenté)

*/

// Fonction pour placer une pièce dans le bitboard correspondant
void set_piece(ull *bitboard, int square) {
    *bitboard |= (1ULL << square);
}

// Convertir une position FEN en structure position
position decode_fen(const char *fen) {
    position pos = {0}; // Initialisation de la structure à zéro
    int square = 0; // Début en haut à gauche (case A8)
    
    // Parsing de la position des pièces
    while (*fen && *fen != ' ') {
        if (*fen >= '1' && *fen <= '8') {
            square += (*fen - '0');
        } else if (*fen == '/') {
            // Ne rien faire
        } else {
            switch (*fen) {
                case 'p': set_piece(&pos.p, square); pos.black |= (1ULL << square); break;
                case 'k': set_piece(&pos.k, square); pos.black |= (1ULL << square); break;
                case 'q': set_piece(&pos.q, square); pos.black |= (1ULL << square); break;
                case 'n': set_piece(&pos.n, square); pos.black |= (1ULL << square); break;
                case 'b': set_piece(&pos.b, square); pos.black |= (1ULL << square); break;
                case 'r': set_piece(&pos.r, square); pos.black |= (1ULL << square); break;
                case 'P': set_piece(&pos.P, square); pos.white |= (1ULL << square); break;
                case 'K': set_piece(&pos.K, square); pos.white |= (1ULL << square); break;
                case 'Q': set_piece(&pos.Q, square); pos.white |= (1ULL << square); break;
                case 'N': set_piece(&pos.N, square); pos.white |= (1ULL << square); break;
                case 'B': set_piece(&pos.B, square); pos.white |= (1ULL << square); break;
                case 'R': set_piece(&pos.R, square); pos.white |= (1ULL << square); break;
            }
            square++;
        }
        fen++;
    }
    
    // Tour du joueur
    fen++;
    pos.whiteSturn = (*fen == 'w');
    fen += 2;
    
    // Roque
    while (*fen && *fen != ' ') {
        switch (*fen) {
            case 'K': pos.KCastling = true; break;
            case 'Q': pos.QCastling = true; break;
            case 'k': pos.kCastling = true; break;
            case 'q': pos.qCastling = true; break;
        }
        fen++;
    }
    
    // Case en passant
    fen++;
    if (*fen != '-') {
        int file = fen[0] - 'a';
        int rank = fen[1] - '1';
        pos.enPassant = 1ULL << (rank * 8 + file);
        fen += 2;
    } else {
        pos.enPassant = 0;
        fen++;
    }
    
    // Compteur de coups pour la règle des 50 coups
    pos.fiftyMoveCounter = atoi(fen);
    
    return pos;
}

position invertWB(position pos) {
    position result;

    result.P = pos.p;
    result.p = pos.P;
    result.K = pos.k;
    result.k = pos.K;
    result.Q = pos.q;
    result.q = pos.Q;
    result.N = pos.n;
    result.n = pos.N;
    result.B = pos.b;
    result.b = pos.B;
    result.R = pos.r;
    result.r = pos.R;
    result.white = pos.black;
    result.black = pos.white;
    result.KCastling = pos.kCastling;
    result.kCastling = pos.KCastling;
    result.QCastling = pos.qCastling;
    result.qCastling = pos.QCastling;

    result.enPassant = pos.enPassant;
    result.fiftyMoveCounter = pos.fiftyMoveCounter;
    result.whiteSturn = !pos.whiteSturn;

    return result;
}

MoveSet generateMove(position pos) {
    MoveSet result;
    result.length = 0;

    position moves[200];

    // Pawn
    for (int i=8; i<56; i++) {
        if ((1ull<<i)&pos.P) {
            printf("%d\n", i);
        }
    }

    result.first = moves;
    return result;
}


int main(int argc, char *argv[]) {

    printf("Hi\n");

    char* fen = "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1";

    position test = decode_fen(fen);
    
    generateMove(test);

    return 0;
}




// gcc C/*.c -o myEngine.exe
