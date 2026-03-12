#include "board.h"
#include "defs.h"
#include <iostream>
using namespace std;

int board[8][8];

void initBoard() {
    //make the board empty first.
    for (int r = 0; r < 8; r++) {
        for (int f = 0; f < 8; f++) {
            board[r][f] = EMPTY;
        } 
    }
    
    //setup the white pieces in rank 1.
    board[0][0] = W_ROOK;
    board[0][1] = W_KNIGHT;
    board[0][2] = W_BISHOP;
    board[0][3] = W_QUEEN;
    board[0][4] = W_KING;
    board[0][5] = W_BISHOP;
    board[0][6] = W_KNIGHT;
    board[0][7] = W_ROOK;

    //setup white pawns in rank 2.
    for (int f = 0; f < 8; f++) {
        board[1][f] = W_PAWN;
    } 

    //setup black pawns in rank 7.
    for (int f = 0; f < 8; f++) board[6][f] = B_PAWN;

    //setup the black pieces in rank 8.
    board[7][0] = B_ROOK;
    board[7][1] = B_KNIGHT;
    board[7][2] = B_BISHOP;
    board[7][3] = B_QUEEN;
    board[7][4] = B_KING;
    board[7][5] = B_BISHOP;
    board[7][6] = B_KNIGHT;
    board[7][7] = B_ROOK;
}

static char pieceToChar(int piece) {
    switch (piece) {
        case EMPTY:     return '-';
        case W_PAWN:    return 'P';
        case W_KNIGHT:  return 'N';
        case W_BISHOP:  return 'B';
        case W_ROOK:    return 'R';
        case W_QUEEN:   return 'Q';
        case W_KING:    return 'K';
        case B_PAWN:    return 'p';
        case B_KNIGHT:  return 'n';
        case B_BISHOP:  return 'b';
        case B_ROOK:    return 'r';
        case B_QUEEN:   return 'q';
        case B_KING:    return 'k';
        default:        return '?';
    }
}

void printBoard() {
    cout << "   _________________" << endl;
    for (int r = 7; r > -1; r--) {
        cout << (r + 1) << " | ";
        for (int f = 0; f < 8; f++) {
            cout << pieceToChar(board[r][f]) << " ";
        }
        cout << "|";
        cout << endl;
    }
    cout << "  |_________________|" << endl;
    cout << "    a b c d e f g h" << endl;
}
