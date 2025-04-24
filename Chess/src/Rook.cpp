#include "Rook.h"
#include "Board.h"

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