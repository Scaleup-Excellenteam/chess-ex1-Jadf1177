#include "ChessUnit.h"
#include "Board.h"
#include <algorithm>

ChessUnit::ChessUnit(bool isLight, int y, int x) : isLight(isLight), y(y), x(x) {}
bool ChessUnit::lightSide() const { return isLight; }
int ChessUnit::getX() const { return x; }
int ChessUnit::getY() const { return y; }
void ChessUnit::relocate(int newRow, int newCol) { x = newRow; y = newCol; }

bool ChessUnit::pathObstructed(int ty, int tx, const Board& board) const {
    int dx = (tx > x) ? 1 : (tx < x) ? -1 : 0;
    int dy = (ty > y) ? 1 : (ty < y) ? -1 : 0;

    int currentX = x + dx;
    int currentY = y + dy;

    while (currentX != tx || currentY != ty) {
        if (board.fetch(currentY, currentX) != nullptr) {
            return true; // Corrected to return true when obstructed
        }
        currentX += dx;
        currentY += dy;
    }
    return false;
}