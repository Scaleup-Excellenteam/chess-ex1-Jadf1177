#include "Pawn.h"
#include "Board.h"
#include <vector>

Pawn::Pawn(bool light, int y, int x) : ChessUnit(light, y, x) {}

bool Pawn::validate(int ty, int tx, const Board& b) const {
    const int dir = lightSide() ? -1 : 1; 
    const int start = lightSide() ? 6 : 1;

    if (tx == x) {
        if ((ty == y + dir) && !b.fetch(ty, tx)) return true;
        if ((y == start) && (ty == y + 2 * dir) &&
            !b.fetch(y + dir, x) && !b.fetch(ty, tx)) return true;
    }
    else if (abs(tx - x) == 1 && ty == y + dir) {
        ChessUnit* target = b.fetch(ty, tx);
        if (target && target->lightSide() != isLight) return true;
    }
    return false;
}

char Pawn::symbol() const {
    return isLight ? 'P' : 'p';
}

std::vector<std::pair<int, int>> Pawn::generateMoves(const Board& board) const {
    std::vector<std::pair<int, int>> moves;
    int direction = isLight ? -1 : 1;
    int startRow = isLight ? 6 : 1;

    // Normal moves
    if (board.fetch(y + direction, x) == nullptr) {
        moves.emplace_back(y + direction, x);
        if (y == startRow && board.fetch(y + 2*direction, x) == nullptr) {
            moves.emplace_back(y + 2*direction, x);
        }
    }

    // Captures
    for (int dx : {-1, 1}) {
        int newX = x + dx;
        if (newX >= 0 && newX < 8) {
            ChessUnit* target = board.fetch(y + direction, newX);
            if (target && target->lightSide() != isLight) {
                moves.emplace_back(y + direction, newX);
            }
        }
    }

    return moves;
}