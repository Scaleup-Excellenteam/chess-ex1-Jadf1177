#pragma once
#include "ChessUnit.h" 

class King : public ChessUnit { 
public:
    King(bool light, int y, int x);
    bool validate(int ty, int tx, const Board& board) const override; 
    char symbol() const override;
    std::vector<std::pair<int, int>> generateMoves(const Board& board) const override;
};