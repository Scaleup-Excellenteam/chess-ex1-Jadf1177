#include "ChessUnit.h"
#include "Board.h"
#include <algorithm>

ChessUnit::ChessUnit(bool isLight, int y, int x) : isLight(isLight), y(y), x(x) {}
bool ChessUnit::lightSide() const { return isLight; }
int ChessUnit::getX() const { return x; }
int ChessUnit::getY() const { return y; }
void ChessUnit::relocate(int newRow, int newCol) { x = newRow; y = newCol; }

bool ChessUnit::pathObstructed(int destRow, int destCol, const Board& board) const {
    int rowStep = (destRow > x) ? 1 : (destRow < x) ? -1 : 0;
    int colStep = (destCol > y) ? 1 : (destCol < y) ? -1 : 0;

    int steps = std::max(abs(destRow - x), abs(destCol - y));

    int currentRow = x + rowStep;
    int currentCol = y + colStep;

    for (int i = 0; i < steps - 1; ++i) {
        if (board.fetch(currentRow, currentCol) != nullptr) {
            return false;
        }
        currentRow += rowStep;
        currentCol += colStep;
    }

    return true;
}