#include "Pieces/Rook.h"
#include "Board.h"

// Rook moves any number of squares vertically or horizontally
bool Rook::isMoveLegal(int currentRow, int currentColumn, int goalRow, int goalColumn, const Board& board) const {
    if ((currentRow != goalRow && currentColumn != goalColumn) || (currentRow == goalRow && currentColumn == goalColumn))
        return false;  // Rooks move in straight lines only and can't stay in the same position

    if (currentRow == goalRow) {
        int step = (goalColumn > currentColumn) ? 1 : -1;
        for (int col = currentColumn + step; col != goalColumn; col += step) {
            if (board.getPiece(currentRow, col)) {
                return false;  // Path is blocked
            }
        }
    }
    else if (currentColumn == goalColumn) {
        int step = (goalRow > currentRow) ? 1 : -1;
        for (int row = currentRow + step; row != goalRow; row += step) {
            if (board.getPiece(row, currentColumn)) {
                return false;  // Path is blocked
            }
        }
    }

    // Check if the goal square is occupied by a piece of the same color
    std::shared_ptr<Piece> goalPiece = board.getPiece(goalRow, goalColumn);
    if (goalPiece && goalPiece->getColor() == this->getColor()) {
        return false;
    }

    return true;
}