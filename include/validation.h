#ifndef VALIDATION_H
#define VALIDATION_H

bool isWhitePiece(int piece);
bool isBlackPiece(int piece);
bool isOwnPiece(int piece, bool whiteToMove);
bool isEnemyPiece(int piece, bool whiteToMove);
bool isInBounds(int rank, int file);
bool isValidPawnMove(int srcRank, int srcFile, int dstRank, int dstFile, bool whiteToMove);

#endif
