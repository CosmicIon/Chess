#ifndef DEFS_H
#define DEFS_H

enum Piece {
    EMPTY = 0,
    W_PAWN, W_KNIGHT, W_BISHOP, W_ROOK, W_QUEEN, W_KING,   // 1–6
    B_PAWN, B_KNIGHT, B_BISHOP, B_ROOK, B_QUEEN, B_KING     // 7–12
};

const int WHITE = 0;
const int BLACK = 1;

#endif
