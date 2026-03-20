#include "board.h"
#include "defs.h"
#include "input.h"
#include "validation.h"
#include <cstdlib>
#include <iostream>
#include <string>

int main() {
    initBoard();
    bool whiteToMove = true;
    CastlingRights castlingRights = {
        false, false, false,
        false, false, false
    };

    while (true) {
        //system("cls"); //to clear the terminal screen.
        printBoard();

        std::cout << (whiteToMove ? "White" : "Black") << " to move: ";
        std::string input;
        std::cin >> input;

        if (input == "quit" || input == "exit") {
            break;
        }

        Move move;
        if (!parseMove(input, move)) {
            continue; //if input is invalid, skips the loop.
        }

        if (!isInBounds(move.srcRank, move.srcFile) || !isInBounds(move.dstRank, move.dstFile)) {
            std::cout << "Move is out of bounds. Press Enter to continue." << std::endl;
            std::cin.get(); std::cin.get(); //this will consume the Enter we press. that way user get a chance to read the error message.
            continue;
        }

        //check whether user moving valid piece or not.
        if (!isOwnPiece(board[move.srcRank][move.srcFile], whiteToMove)) {
            std::cout << "That's not your piece! Press Enter to continue." << std::endl;
            std::cin.get(); std::cin.get();
            continue;
        }
        if (isOwnPiece(board[move.dstRank][move.dstFile], whiteToMove)) {
            std::cout << "You can't capture your own piece! Press Enter to continue." << std::endl;
            std::cin.get(); std::cin.get();
            continue;
        }

        const int movingPiece = board[move.srcRank][move.srcFile];
        const int capturedPiece = board[move.dstRank][move.dstFile];
        if (!isValidPieceMove(move.srcRank, move.srcFile, move.dstRank, move.dstFile, whiteToMove, castlingRights)) {
            std::cout << "Illegal move! Press Enter to continue." << std::endl;
            std::cin.get(); std::cin.get();
            continue;
        }

        if (doesMoveLeaveKingInCheck(move.srcRank, move.srcFile, move.dstRank, move.dstFile, whiteToMove)) {
            std::cout << "Illegal move: your king would be in check! Press Enter to continue." << std::endl;
            std::cin.get(); std::cin.get();
            continue;
        }

        // Track rook captures on original squares so castling rights are revoked.
        if (capturedPiece == W_ROOK) {
            if (move.dstRank == 0 && move.dstFile == 0) {
                castlingRights.whiteRookA_Moved = true;
            }
            if (move.dstRank == 0 && move.dstFile == 7) {
                castlingRights.whiteRookH_Moved = true;
            }
        }
        if (capturedPiece == B_ROOK) {
            if (move.dstRank == 7 && move.dstFile == 0) {
                castlingRights.blackRookA_Moved = true;
            }
            if (move.dstRank == 7 && move.dstFile == 7) {
                castlingRights.blackRookH_Moved = true;
            }
        }

        const bool isCastlingMove =
            (movingPiece == W_KING || movingPiece == B_KING) &&
            move.srcRank == move.dstRank &&
            std::abs(move.dstFile - move.srcFile) == 2;

        if (isCastlingMove) {
            board[move.dstRank][move.dstFile] = movingPiece;
            board[move.srcRank][move.srcFile] = EMPTY;

            // Move the rook as part of castling.
            if (move.dstFile == 6) {
                board[move.srcRank][5] = board[move.srcRank][7];
                board[move.srcRank][7] = EMPTY;
            } else {
                board[move.srcRank][3] = board[move.srcRank][0];
                board[move.srcRank][0] = EMPTY;
            }
        } else {
            board[move.dstRank][move.dstFile] = movingPiece;
            board[move.srcRank][move.srcFile] = EMPTY;
        }

        // Update castling rights after king/rook moves.
        if (movingPiece == W_KING) {
            castlingRights.whiteKingMoved = true;
        }
        if (movingPiece == B_KING) {
            castlingRights.blackKingMoved = true;
        }
        if (movingPiece == W_ROOK) {
            if (move.srcRank == 0 && move.srcFile == 0) {
                castlingRights.whiteRookA_Moved = true;
            }
            if (move.srcRank == 0 && move.srcFile == 7) {
                castlingRights.whiteRookH_Moved = true;
            }
        }
        if (movingPiece == B_ROOK) {
            if (move.srcRank == 7 && move.srcFile == 0) {
                castlingRights.blackRookA_Moved = true;
            }
            if (move.srcRank == 7 && move.srcFile == 7) {
                castlingRights.blackRookH_Moved = true;
            }
        }

        whiteToMove = !whiteToMove;
    }

    return 0;
}
