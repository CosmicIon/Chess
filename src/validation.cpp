#include "validation.h"
#include "defs.h"

bool isWhitePiece(int piece) {
    return piece >= W_PAWN && piece <= W_KING;
}

bool isBlackPiece(int piece) {
    return piece >= B_PAWN && piece <= B_KING;
}

bool isOwnPiece(int piece, bool whiteToMove) {
    return whiteToMove ? isWhitePiece(piece) : isBlackPiece(piece);
}

bool isEnemyPiece(int piece, bool whiteToMove) {
    return whiteToMove ? isBlackPiece(piece) : isWhitePiece(piece);
}

bool isInBounds(int rank, int file) {
    return rank >= 0 && rank <= 7 && file >= 0 && file <= 7;
}
