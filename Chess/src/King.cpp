#include "King.h"
#include "Board.h"
#include <vector>

King::King(bool light, int y, int x) : ChessUnit(light, y, x) {}

bool King::validate(int ty, int tx, const Board& board) const {
    const int yd = abs(ty - y);
    const int xd = abs(tx - x);

    if (yd > 1 || xd > 1) return false;

    ChessUnit* target = board.fetch(ty, tx);
    return !(target && target->lightSide() == isLight);
}

char King::symbol() const {
    return isLight ? 'K' : 'k';
}

std::vector<std::pair<int, int>> King::generateMoves(const Board& board) const {
    std::vector<std::pair<int, int>> moves;
    const int offsets[8][2] = {{1,0}, {1,1}, {0,1}, {-1,1},
                              {-1,0}, {-1,-1}, {0,-1}, {1,-1}};

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