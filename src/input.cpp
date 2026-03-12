#include "input.h"
#include <iostream>

int charToFile(char c) {
    return c - 'a'; // input a will return 0
}

int charToRank(char c) {
    return c - '1'; // input 1 will return 0
}

std::string indexToSquare(int rank, int file) {
    // input (0, 0) will return 'a1'
    return std::string(1, 'a' + file) + std::string(1, '1' + rank);
}

bool parseMove(const std::string &input, Move &move) {
    //length will either 4 (e2e4) or 5 (e7e8q) in case of promotion of pawn to queen.
    if (input.length() != 4 && input.length() != 5) {
        std::cout << "Invalid input. Length either 4 or 5. Press Enter to continue." << std::endl;
        std::cin.get(); std::cin.get(); //this will consume the Enter we press. that way user get a chance to read the error message.
        return false;
    }

    if (input[0] < 'a' || input[0] > 'h' ||
        input[1] < '1' || input[1] > '8' ||
        input[2] < 'a' || input[2] > 'h' ||
        input[3] < '1' || input[3] > '8') {
        std::cout << "Invalid input. Use format like e2e4. Press Enter to continue." << std::endl;
        std::cin.get(); std::cin.get(); //this will consume the Enter we press. that way user get a chance to read the error message.
        return false;
    }

    move.srcFile = charToFile(input[0]);
    move.srcRank = charToRank(input[1]);
    move.dstFile = charToFile(input[2]);
    move.dstRank = charToRank(input[3]);
    move.promotion = '\0';

    //handle promotion piece
    if (input.length() == 5) {
        char promo = input[4];
        if (promo != 'q' && promo != 'r' && promo != 'b' && promo != 'n') {
            std::cout << "Invalid promotion piece. Use q, r, b, or n. Press Enter to continue." << std::endl;
            std::cin.get(); std::cin.get(); //this will consume the Enter we press. that way user get a chance to read the error message.
            return false;
        }
        move.promotion = promo;
    }
    return true;
}
