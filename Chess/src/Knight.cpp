#include "Knight.h"
#include "Board.h"
#include <vector>

Knight::Knight(bool light, int y, int x) : ChessUnit(light, y, x) {}

bool Knight::validate(int ty, int tx, const Board& b) const {
    const int yd = abs(ty - y);
    const int xd = abs(tx - x);
    return (yd == 2 && xd == 1) || (yd == 1 && xd == 2); 
}

char Knight::symbol() const {
    return isLight ? 'N' : 'n';
}

std::vector<std::pair<int, int>> Knight::generateMoves(const Board& board) const {
    std::vector<std::pair<int, int>> moves;
    const int offsets[8][2] = {{2,1}, {1,2}, {-1,2}, {-2,1},
                              {-2,-1}, {-1,-2}, {1,-2}, {2,-1}};

    for (const auto& offset : offsets) {
        int newY = y + offset[0];
        int newX = x + offset[1];
        if (newY >= 0 && newY < 8 && newX >= 0 && newX < 8) {
            ChessUnit* target = board.fetch(newY, newX);
            if (!target || target->lightSide() != isLight) {
                moves.emplace_back(newY, newX);
            }
        }
    }
    return moves;
}