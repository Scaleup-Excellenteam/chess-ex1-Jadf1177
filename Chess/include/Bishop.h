#pragma once
#include "ChessUnit.h"

class Bishop : public ChessUnit {
public:
    Bishop(bool light, int y, int x);
    bool validate(int targetY, int targetX, const Board& board) const override;
    char symbol() const override;
    std::vector<std::pair<int, int>> generateMoves(const Board& board) const override;
};