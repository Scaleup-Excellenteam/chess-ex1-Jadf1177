#pragma once
#include "ChessUnit.h"

class Pawn : public ChessUnit {
public:
    Pawn(bool light, int y, int x);
    bool validate(int targetY, int targetX, const Board& board) const override;
    char symbol() const override;
    std::vector<std::pair<int, int>> generateMoves(const Board& board) const override;
};