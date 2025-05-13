#include "Pieces/Knight.h"

// Knight moves in an L-shape
bool Knight::isMoveLegal(int currentRow, int currentColumn, int goalRow, int goalColumn, const Board& board) const {
    if (currentRow == goalRow && currentColumn == goalColumn)
        return false;

    int rowDiff = abs(goalRow - currentRow);
    int colDiff = abs(goalColumn - currentColumn);

    // Check if the move is in L-shape
    if (!((rowDiff == 2 && colDiff == 1) || (rowDiff == 1 && colDiff == 2)))
        return false;

    // Get the piece at the goal cell
    std::shared_ptr<Piece> goalPiece = board.getPiece(goalRow, goalColumn);

    // Check if the goal cell is empty or contains an opponent's piece
    if (goalPiece == nullptr || goalPiece->getColor() != this->getColor())
        return true;

    return false;
}