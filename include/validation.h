#ifndef VALIDATION_H
#define VALIDATION_H

struct CastlingRights {
	bool whiteKingMoved;
	bool whiteRookA_Moved;
	bool whiteRookH_Moved;
	bool blackKingMoved;
	bool blackRookA_Moved;
	bool blackRookH_Moved;
};

bool isWhitePiece(int piece);
bool isBlackPiece(int piece);
bool isOwnPiece(int piece, bool whiteToMove);
bool isEnemyPiece(int piece, bool whiteToMove);
bool isInBounds(int rank, int file);
bool isValidPawnMove(int srcRank, int srcFile, int dstRank, int dstFile, bool whiteToMove, int epRank, int epFile);
bool isValidKnightMove(int srcRank, int srcFile, int dstRank, int dstFile);
bool isValidKingMove(int srcRank, int srcFile, int dstRank, int dstFile, bool whiteToMove, const CastlingRights &rights);
bool isValidRookMove(int srcRank, int srcFile, int dstRank, int dstFile);
bool isValidBishopMove(int srcRank, int srcFile, int dstRank, int dstFile);
bool isValidQueenMove(int srcRank, int srcFile, int dstRank, int dstFile);
bool isValidPieceMove(int srcRank, int srcFile, int dstRank, int dstFile, bool whiteToMove, const CastlingRights &rights, int epRank, int epFile);
bool isSquareAttacked(int rank, int file, bool byWhite);
void findKing(bool white, int &kingRank, int &kingFile);
bool doesMoveLeaveKingInCheck(int srcRank, int srcFile, int dstRank, int dstFile, bool whiteToMove, int epRank, int epFile);

#endif
