#include "Rook.h"
#include "Board.h"
#include <vector>

Rook::Rook(bool light, int y, int x) : ChessUnit(light, y, x) {}

bool Rook::validate(int ty, int tx, const Board& board) const {
    if (y != ty && x != tx) return false;
    if (pathObstructed(ty, tx, board)) return false;

    ChessUnit* target = board.fetch(ty, tx);
    return !(target && target->lightSide() == isLight);
}

char Rook::symbol() const {
    return isLight ? 'R' : 'r';
}

std::vector<std::pair<int, int>> Rook::generateMoves(const Board& board) const {
    std::vector<std::pair<int, int>> moves;

    // Horizontal moves
    for (int dx : {-1, 1}) {
        int cx = x + dx;
        while (cx >= 0 && cx < 8) {
            ChessUnit* target = board.fetch(y, cx);
            if (!target) {
                moves.emplace_back(y, cx);
            } else {
                if (target->lightSide() != isLight) {
                    moves.emplace_back(y, cx);
                }
                break;
            }
            cx += dx;
        }
    }

    // Vertical moves
    for (int dy : {-1, 1}) {
        int cy = y + dy;
        while (cy >= 0 && cy < 8) {
            ChessUnit* target = board.fetch(cy, x);
            if (!target) {
                moves.emplace_back(cy, x);
            } else {
                if (target->lightSide() != isLight) {
                    moves.emplace_back(cy, x);
                }
                break;
            }
            cy += dy;
        }
    }

    return moves;
}