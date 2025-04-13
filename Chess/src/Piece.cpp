#include "Piece.h"
#include "Board.h"
#include <cmath>

using namespace std;

bool Rook::isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const {
    if (srcRow != destRow && srcCol != destCol) return false;
    if (!board.isPathClear(srcRow, srcCol, destRow, destCol)) return false;
    return true;
}

bool Knight::isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const {
    int dx = abs(destCol - srcCol);
    int dy = abs(destRow - srcRow);
    return (dx == 1 && dy == 2) || (dx == 2 && dy == 1);
}

bool Bishop::isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const {
    if (abs(destRow - srcRow) != abs(destCol - srcCol)) return false;
    return board.isPathClear(srcRow, srcCol, destRow, destCol);
}

bool Queen::isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const {
    if ((srcRow != destRow && srcCol != destCol) && (abs(destRow - srcRow) != abs(destCol - srcCol))) return false;
    return board.isPathClear(srcRow, srcCol, destRow, destCol);
}

bool King::isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const {
    int dx = abs(destCol - srcCol);
    int dy = abs(destRow - srcRow);
    return dx <= 1 && dy <= 1;
}

bool Pawn::isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const {
    int direction = white ? 1 : -1;
    int startRow = white ?  1 : 6;

    // Moving forward
    if (srcCol == destCol && board.getPiece(destRow, destCol) == nullptr) {
        if (destRow == srcRow + direction) return true;
        if (srcRow == startRow && destRow == srcRow + 2 * direction && board.getPiece(srcRow + direction, srcCol) == nullptr) return true;
    }

    // Capturing
    if (abs(destCol - srcCol) == 1 && destRow == srcRow + direction && board.getPiece(destRow, destCol) != nullptr && board.getPiece(destRow, destCol)->isWhite() != white) {
        return true;
    }

    return false;
}