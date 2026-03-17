#include "board.h"
#include "defs.h"
#include "input.h"
#include "validation.h"
#include <iostream>
#include <string>

int main() {
    initBoard();
    bool whiteToMove = true;

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
        //pawn move check.
        if ((movingPiece == W_PAWN || movingPiece == B_PAWN) &&
            !isValidPawnMove(move.srcRank, move.srcFile, move.dstRank, move.dstFile, whiteToMove)) {
            std::cout << "Illegal pawn move! Press Enter to continue." << std::endl;
            std::cin.get(); std::cin.get();
            continue;
        }

        //knight move check.
        if((movingPiece == W_KNIGHT || movingPiece == B_KNIGHT) && !isValidKnightMove(move.srcRank, move.srcFile, move.dstRank, move.dstFile)) {
            std::cout << "Illegal knight move! Press Enter to continue." << std::endl;
            std::cin.get(); std::cin.get();
            continue;
        }

        //king move check.
        if((movingPiece == W_KING || movingPiece == B_KING) && !isValidKingMove(move.srcRank, move.srcFile, move.dstRank, move.dstFile)) {
            std::cout << "Illegal king move! Press Enter to continue." << std::endl;
            std::cin.get(); std::cin.get();
            continue;
        } 

        //rook move check.
        if((movingPiece == W_ROOK || movingPiece == B_ROOK) && !isValidRookMove(move.srcRank, move.srcFile, move.dstRank, move.dstFile)) {
            std::cout << "Illegal rook move! Press Enter to continue." << std::endl;
            std::cin.get(); std::cin.get();
            continue;
        } 

        //bishop move check.
        if((movingPiece == W_BISHOP || movingPiece == B_BISHOP) && !isValidBishopMove(move.srcRank, move.srcFile, move.dstRank, move.dstFile)) {
            std::cout << "Illegal bishop move! Press Enter to continue." << std::endl;
            std::cin.get(); std::cin.get();
            continue;
        }

        //queen move check.
        if((movingPiece == W_QUEEN || movingPiece == B_QUEEN) && !isValidQueenMove(move.srcRank, move.srcFile, move.dstRank, move.dstFile)) {
            std::cout << "Illegal queen move! Press Enter to continue." << std::endl;
            std::cin.get(); std::cin.get();
            continue;
        }

        //making the move .. without checking any rule for now.
        board[move.dstRank][move.dstFile] = movingPiece;
        board[move.srcRank][move.srcFile] = EMPTY;

        whiteToMove = !whiteToMove;
    }

    return 0;
}
