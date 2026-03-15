#include "validation.h"
#include "board.h"
#include "defs.h"
#include <cstdlib>

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

bool isValidPawnMove(int srcRank, int srcFile, int dstRank, int dstFile, bool whiteToMove) {
    if (!isInBounds(srcRank, srcFile) || !isInBounds(dstRank, dstFile)) {
        return false;
    }

    const int direction = whiteToMove ? 1 : -1;
    const int startRank = whiteToMove ? 1 : 6;
    const int rankDiff = dstRank - srcRank;
    const int fileDiff = dstFile - srcFile;

    //if pawn move just one square forward.
    if (fileDiff == 0 && rankDiff == direction) {
        return board[dstRank][dstFile] == EMPTY;
    }

    //pawn move 2 square from start rank.
    if (fileDiff == 0 && rankDiff == 2 * direction && srcRank == startRank) {
        const int middleRank = srcRank + direction;
        return board[middleRank][dstFile] == EMPTY && board[dstRank][dstFile] == EMPTY;
    }

    //pawn diagonal capture enemy piece.
    if (std::abs(fileDiff) == 1 && rankDiff == direction) {
        return isEnemyPiece(board[dstRank][dstFile], whiteToMove);
    }

    return false;
}
