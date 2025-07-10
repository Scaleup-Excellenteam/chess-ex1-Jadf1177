#include "Pieces/Bishop.h"

// Bishops move diagonally
bool Bishop::isMoveLegal(int currentRow, int currentColumn, int goalRow, int goalColumn, const Board& board) const {
    if (abs(goalRow - currentRow) != abs(goalColumn - currentColumn) || (currentRow == goalRow && currentColumn == goalColumn))
        return false;  

    // Check if path is clear
    int rowStep = (goalRow > currentRow) ? 1 : -1;
    int colStep = (goalColumn > currentColumn) ? 1 : -1;
    int row = currentRow + rowStep;
    int col = currentColumn + colStep;

    while (row != goalRow && col != goalColumn) {
        if (board.getPiece(row, col))
            return false;  // Path is blocked
        row += rowStep;
        col += colStep;
    }

    std::shared_ptr<Piece> goalPiece = board.getPiece(goalRow, goalColumn);
    if (goalPiece != nullptr && goalPiece->getColor() == this->getColor())
        return false;
    return true;
}
