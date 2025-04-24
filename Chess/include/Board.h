#pragma once
#include "ChessUnit.h"
#include <string>

class Board {
private:
    ChessUnit* grid[8][8];

public:
    Board(const std::string& setup);
    ~Board();
    Board(const Board& source);
    Board& operator=(Board rhs);

    ChessUnit* fetch(int y, int x) const;
    bool checkThreat(bool white) const;
    void move(int sy, int sx, int dy, int dx);

    friend void swap(Board& first, Board& second) noexcept;
};