#ifndef INPUT_H
#define INPUT_H

#include <string>

int charToFile(char c);
int charToRank(char c);
std::string indexToSquare(int rank, int file);

struct Move {
    int srcRank, srcFile;
    int dstRank, dstFile;
    char promotion; // '\0' if none
};

bool parseMove(const std::string &input, Move &move);

#endif
