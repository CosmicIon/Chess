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
        return board[middleRank][srcFile] == EMPTY && board[dstRank][dstFile] == EMPTY;
    }

    //pawn diagonal capture enemy piece.
    if (std::abs(fileDiff) == 1 && rankDiff == direction) {
        return isEnemyPiece(board[dstRank][dstFile], whiteToMove);
    }

    return false;
}

bool isValidKnightMove(int srcRank, int srcFile, int dstRank, int dstFile) {
    if (!isInBounds(srcRank, srcFile) || !isInBounds(dstRank, dstFile)) {
        return false;
    }
    const int rankDiff = dstRank - srcRank;
    const int fileDiff = dstFile - srcFile;
    
    //L-shape movement of knight.
    if((std::abs(fileDiff) == 1 && std::abs(rankDiff) == 2) || (std::abs(fileDiff) == 2 && std::abs(rankDiff) == 1)) {
        return true;
    }
    return false;
}

bool isValidKingMove(int srcRank, int srcFile, int dstRank, int dstFile) {
    if (!isInBounds(srcRank, srcFile) || !isInBounds(dstRank, dstFile)) {
        return false;
    }

    //if king not move at all, its invalid move.
    //No need to do it here because this error is already handled. but did it anyway.
    if(srcFile == dstFile && srcRank == dstRank) {
        return false;
    }
    const int rankDiff = std::abs(dstRank - srcRank);
    const int fileDiff = std::abs(dstFile - srcFile);
    
    //king only move 1 step anywhere.
    if(rankDiff < 2 && fileDiff < 2) {
        return true;
    }
    return false;
}

bool isValidRookMove(int srcRank, int srcFile, int dstRank, int dstFile) {
    if (!isInBounds(srcRank, srcFile) || !isInBounds(dstRank, dstFile)) {
        return false;
    }

    //horizontal move: same rank, file changes.
    if (srcRank == dstRank) {
        const int step = (dstFile > srcFile) ? 1 : -1;
        for (int f = srcFile + step; f != dstFile; f += step) {
            if (board[srcRank][f] != EMPTY) {
                return false;
            }
        }
        return true;
    }

    //vertical move: same file, rank changes.
    if (srcFile == dstFile) {
        const int step = (dstRank > srcRank) ? 1 : -1;
        for (int r = srcRank + step; r != dstRank; r += step) {
            if (board[r][srcFile] != EMPTY) {
                return false;
            }
        }
        return true;
    }

    return false;
}