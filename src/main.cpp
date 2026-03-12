#include "board.h"
#include "defs.h"
#include "input.h"
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

        //check source square has a piece
        if (board[move.srcRank][move.srcFile] == EMPTY) {
            std::cout << "No piece at that square. Press Enter to continue." << std::endl;
            std::cin.get(); std::cin.get(); //this will consume the Enter we press. that way user get a chance to read the error message.
            continue;
        }

        //making the move .. without checking any rule for now.
        board[move.dstRank][move.dstFile] = board[move.srcRank][move.srcFile];
        board[move.srcRank][move.srcFile] = EMPTY;

        whiteToMove = !whiteToMove;
    }

    return 0;
}
