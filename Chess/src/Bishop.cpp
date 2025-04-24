#include "Bishop.h"
#include "Board.h"

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