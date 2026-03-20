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

static bool isValidCastlingMove(int srcRank, int srcFile, int dstRank, int dstFile, bool whiteToMove, const CastlingRights &rights) {
    if (whiteToMove) {
        if (srcRank != 0 || srcFile != 4 || dstRank != 0) {
            return false;
        }

        // White kingside: e1 -> g1
        if (dstFile == 6) {
            if (rights.whiteKingMoved || rights.whiteRookH_Moved) {
                return false;
            }
            if (board[0][7] != W_ROOK || board[0][5] != EMPTY || board[0][6] != EMPTY) {
                return false;
            }
            if (isSquareAttacked(0, 4, false) || isSquareAttacked(0, 5, false) || isSquareAttacked(0, 6, false)) {
                return false;
            }
            return true;
        }

        // White queenside: e1 -> c1
        if (dstFile == 2) {
            if (rights.whiteKingMoved || rights.whiteRookA_Moved) {
                return false;
            }
            if (board[0][0] != W_ROOK || board[0][1] != EMPTY || board[0][2] != EMPTY || board[0][3] != EMPTY) {
                return false;
            }
            if (isSquareAttacked(0, 4, false) || isSquareAttacked(0, 3, false) || isSquareAttacked(0, 2, false)) {
                return false;
            }
            return true;
        }
    } else {
        if (srcRank != 7 || srcFile != 4 || dstRank != 7) {
            return false;
        }

        // Black kingside: e8 -> g8
        if (dstFile == 6) {
            if (rights.blackKingMoved || rights.blackRookH_Moved) {
                return false;
            }
            if (board[7][7] != B_ROOK || board[7][5] != EMPTY || board[7][6] != EMPTY) {
                return false;
            }
            if (isSquareAttacked(7, 4, true) || isSquareAttacked(7, 5, true) || isSquareAttacked(7, 6, true)) {
                return false;
            }
            return true;
        }

        // Black queenside: e8 -> c8
        if (dstFile == 2) {
            if (rights.blackKingMoved || rights.blackRookA_Moved) {
                return false;
            }
            if (board[7][0] != B_ROOK || board[7][1] != EMPTY || board[7][2] != EMPTY || board[7][3] != EMPTY) {
                return false;
            }
            if (isSquareAttacked(7, 4, true) || isSquareAttacked(7, 3, true) || isSquareAttacked(7, 2, true)) {
                return false;
            }
            return true;
        }
    }

    return false;
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

bool isValidKingMove(int srcRank, int srcFile, int dstRank, int dstFile, bool whiteToMove, const CastlingRights &rights) {
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

    // Castling move (king moves two squares horizontally).
    if (rankDiff == 0 && fileDiff == 2) {
        return isValidCastlingMove(srcRank, srcFile, dstRank, dstFile, whiteToMove, rights);
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

bool isValidBishopMove(int srcRank, int srcFile, int dstRank, int dstFile) {
    if (!isInBounds(srcRank, srcFile) || !isInBounds(dstRank, dstFile)) {
        return false;
    }

    const int rankDiff = std::abs(dstRank - srcRank);
    const int fileDiff = std::abs(dstFile - srcFile);

    //bishop must move in diagonal.
    if (rankDiff != fileDiff || rankDiff == 0 || fileDiff == 0) {
        return false;
    }

    const int rankStep = (dstRank > srcRank) ? 1 : -1;
    const int fileStep = (dstFile > srcFile) ? 1 : -1;

    int r = srcRank + rankStep;
    int f = srcFile + fileStep;

    //check if all the square between is empty or not.
    while (r != dstRank && f != dstFile) {
        if (board[r][f] != EMPTY) {
            return false;
        }
        r += rankStep;
        f += fileStep;
    }

    return true;
}

bool isValidQueenMove(int srcRank, int srcFile, int dstRank, int dstFile) {
    return(isValidBishopMove(srcRank, srcFile, dstRank, dstFile) || isValidRookMove(srcRank, srcFile, dstRank, dstFile)); //haha simple
}

bool isValidPieceMove(int srcRank, int srcFile, int dstRank, int dstFile, bool whiteToMove, const CastlingRights &rights) {
    if (!isInBounds(srcRank, srcFile) || !isInBounds(dstRank, dstFile)) {
        return false;
    }

    const int piece = board[srcRank][srcFile];
    switch (piece) {
        case W_PAWN:
        case B_PAWN:
            return isValidPawnMove(srcRank, srcFile, dstRank, dstFile, whiteToMove);
        case W_KNIGHT:
        case B_KNIGHT:
            return isValidKnightMove(srcRank, srcFile, dstRank, dstFile);
        case W_BISHOP:
        case B_BISHOP:
            return isValidBishopMove(srcRank, srcFile, dstRank, dstFile);
        case W_ROOK:
        case B_ROOK:
            return isValidRookMove(srcRank, srcFile, dstRank, dstFile);
        case W_QUEEN:
        case B_QUEEN:
            return isValidQueenMove(srcRank, srcFile, dstRank, dstFile);
        case W_KING:
        case B_KING:
            return isValidKingMove(srcRank, srcFile, dstRank, dstFile, whiteToMove, rights);
        default:
            return false;
    }
}

bool isSquareAttacked(int rank, int file, bool byWhite) {
    if (!isInBounds(rank, file)) {
        return false;
    }

    const int attackerKnight = byWhite ? W_KNIGHT : B_KNIGHT;
    const int attackerBishop = byWhite ? W_BISHOP : B_BISHOP;
    const int attackerRook = byWhite ? W_ROOK : B_ROOK;
    const int attackerQueen = byWhite ? W_QUEEN : B_QUEEN;
    const int attackerKing = byWhite ? W_KING : B_KING;
    const int attackerPawn = byWhite ? W_PAWN : B_PAWN;

    const int knightOffsets[8][2] = {
        {-2, -1}, {-2, 1}, {-1, -2}, {-1, 2},
        {1, -2}, {1, 2}, {2, -1}, {2, 1}
    };
    for (int i = 0; i < 8; i++) {
        const int r = rank + knightOffsets[i][0];
        const int f = file + knightOffsets[i][1];
        if (isInBounds(r, f) && board[r][f] == attackerKnight) {
            return true;
        }
    }

    const int straightDirs[4][2] = {{1, 0}, {-1, 0}, {0, 1}, {0, -1}};
    for (int d = 0; d < 4; ++d) {
        int r = rank + straightDirs[d][0];
        int f = file + straightDirs[d][1];
        while (isInBounds(r, f)) {
            const int piece = board[r][f];
            if (piece == EMPTY) {
                r += straightDirs[d][0];
                f += straightDirs[d][1];
                continue;
            }

            if (piece == attackerRook || piece == attackerQueen) {
                return true;
            }
            break;
        }
    }

    const int diagonalDirs[4][2] = {{1, 1}, {1, -1}, {-1, 1}, {-1, -1}};
    for (int d = 0; d < 4; ++d) {
        int r = rank + diagonalDirs[d][0];
        int f = file + diagonalDirs[d][1];
        while (isInBounds(r, f)) {
            const int piece = board[r][f];
            if (piece == EMPTY) {
                r += diagonalDirs[d][0];
                f += diagonalDirs[d][1];
                continue;
            }

            if (piece == attackerBishop || piece == attackerQueen) {
                return true;
            }
            break;
        }
    }

    if (byWhite) {
        if (isInBounds(rank - 1, file - 1) && board[rank - 1][file - 1] == attackerPawn) {
            return true;
        }
        if (isInBounds(rank - 1, file + 1) && board[rank - 1][file + 1] == attackerPawn) {
            return true;
        }
    } else {
        if (isInBounds(rank + 1, file - 1) && board[rank + 1][file - 1] == attackerPawn) {
            return true;
        }
        if (isInBounds(rank + 1, file + 1) && board[rank + 1][file + 1] == attackerPawn) {
            return true;
        }
    }

    const int kingOffsets[8][2] = {
        {-1, -1}, {-1, 0}, {-1, 1},
        {0, -1},           {0, 1},
        {1, -1},  {1, 0},  {1, 1}
    };
    for (int i = 0; i < 8; ++i) {
        const int r = rank + kingOffsets[i][0];
        const int f = file + kingOffsets[i][1];
        if (isInBounds(r, f) && board[r][f] == attackerKing) {
            return true;
        }
    }

    return false;
}

void findKing(bool whiteToMove, int &kingRank, int &kingFile) {
    const int targetKing = whiteToMove ? W_KING : B_KING;
    
    //find positon of king.
    for (int r = 0; r < 8; r++) {
        for (int f = 0; f < 8; f++) {
            if (board[r][f] == targetKing) {
                kingRank = r;
                kingFile = f;
                return;
            }
        }
    }
    //if not found.
    kingRank = -1;
    kingFile = -1;
}

bool doesMoveLeaveKingInCheck(int srcRank, int srcFile, int dstRank, int dstFile, bool whiteToMove) {
    const int srcPiece = board[srcRank][srcFile];
    const int dstPiece = board[dstRank][dstFile];

    board[dstRank][dstFile] = srcPiece;
    board[srcRank][srcFile] = EMPTY;

    int kingRank = -1;
    int kingFile = -1;
    findKing(whiteToMove, kingRank, kingFile);

    bool inCheck = true;
    if (kingRank != -1 && kingFile != -1) {
        inCheck = isSquareAttacked(kingRank, kingFile, !whiteToMove);
    }

    board[srcRank][srcFile] = srcPiece;
    board[dstRank][dstFile] = dstPiece;

    return inCheck;
}