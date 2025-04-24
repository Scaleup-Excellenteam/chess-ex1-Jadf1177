#include "Knight.h"
#include "Board.h"

Knight::Knight(bool light, int y, int x) : ChessUnit(light, y, x) {}

bool Knight::validate(int ty, int tx, const Board& b) const {
    const int yd = abs(ty - y);
    const int xd = abs(tx - x);
    return (yd == 2 && xd == 1) || (yd == 1 && xd == 2); 
}

char Knight::symbol() const {
    return isLight ? 'N' : 'n';
}