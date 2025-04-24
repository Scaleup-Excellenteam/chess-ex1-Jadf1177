#include "Queen.h"
#include "Board.h"

Queen::Queen(bool light, int y, int x) : ChessUnit(light, y, x) {}

bool Queen::validate(int ty, int tx, const Board& board) const {
    if ((y != ty && x != tx) && (abs(ty - y) != abs(tx - x))) return false;
    if (pathObstructed(ty, tx, board)) return false;

    ChessUnit* target = board.fetch(ty, tx);
    return !(target && target->lightSide() == isLight);
}

char Queen::symbol() const {
    return isLight ? 'Q' : 'q';
}