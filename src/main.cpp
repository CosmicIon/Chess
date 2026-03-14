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
        system("cls"); //to clear the terminal screen.
        printBoard();

        std::cout << (whiteToMove ? "White" : "Black") << " to move: ";
        std::string input;
        std::cin >> input;

        if (input == "quit") {
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

        //making the move .. without checking any rule for now.
        board[move.dstRank][move.dstFile] = board[move.srcRank][move.srcFile];
        board[move.srcRank][move.srcFile] = EMPTY;

        whiteToMove = !whiteToMove;
    }

    return 0;
}
