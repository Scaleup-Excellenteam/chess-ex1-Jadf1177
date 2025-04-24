#pragma once
#include "ChessUnit.h"

class Queen : public ChessUnit {
public:
    Queen(bool light, int y, int x);
    bool validate(int targetY, int targetX, const Board& board) const override;
    char symbol() const override;
};