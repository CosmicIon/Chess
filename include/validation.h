#ifndef VALIDATION_H
#define VALIDATION_H

bool isWhitePiece(int piece);
bool isBlackPiece(int piece);
bool isOwnPiece(int piece, bool whiteToMove);
bool isEnemyPiece(int piece, bool whiteToMove);
bool isInBounds(int rank, int file);
bool isValidPawnMove(int srcRank, int srcFile, int dstRank, int dstFile, bool whiteToMove);
bool isValidKnightMove(int srcRank, int srcFile, int dstRank, int dstFile);
bool isValidKingMove(int srcRank, int srcFile, int dstRank, int dstFile);
bool isValidRookMove(int srcRank, int srcFile, int dstRank, int dstFile);
bool isValidBishopMove(int srcRank, int srcFile, int dstRank, int dstFile);
bool isValidQueenMove(int srcRank, int srcFile, int dstRank, int dstFile);
bool isValidPieceMove(int srcRank, int srcFile, int dstRank, int dstFile, bool whiteToMove);
bool isSquareAttacked(int rank, int file, bool byWhite);
void findKing(bool white, int &kingRank, int &kingFile);
bool doesMoveLeaveKingInCheck(int srcRank, int srcFile, int dstRank, int dstFile, bool whiteToMove);

#endif
