#include "Pawn.h"
#include "Board.h"

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