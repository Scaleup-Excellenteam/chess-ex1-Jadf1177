#include "Bishop.h"
#include "Board.h"
#include <vector>

Bishop::Bishop(bool light, int y, int x) : ChessUnit(light, y, x) {}

bool Bishop::validate(int ty, int tx, const Board& b) const {
    const int yd = abs(ty - y);
    const int xd = abs(tx - x);

    if (yd * yd != xd * xd) return false; 

    if (!pathObstructed(ty, tx, b)) return false;

    ChessUnit* target = b.fetch(ty, tx);
    return !(target && target->lightSide() == isLight);
}

char Bishop::symbol() const {
    return isLight ? 'B' : 'b';
}

std::vector<std::pair<int, int>> Bishop::generateMoves(const Board& board) const {
    std::vector<std::pair<int, int>> moves;

    const int directions[4][2] = {{1,1}, {1,-1}, {-1,1}, {-1,-1}};

    for (const auto& dir : directions) {
        int cy = y + dir[0];
        int cx = x + dir[1];
        while (cy >= 0 && cy < 8 && cx >= 0 && cx < 8) {
            ChessUnit* target = board.fetch(cy, cx);
            if (!target) {
                moves.emplace_back(cy, cx);
            } else {
                if (target->lightSide() != isLight) {
                    moves.emplace_back(cy, cx);
                }
                break;
            }
            cy += dir[0];
            cx += dir[1];
        }
    }

    return moves;
}