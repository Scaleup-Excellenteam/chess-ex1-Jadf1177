#include "King.h"
#include "Board.h"

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