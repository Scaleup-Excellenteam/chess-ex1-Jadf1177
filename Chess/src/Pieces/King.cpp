#include "Pieces/King.h"

// King moves one square in any direction
bool King::isMoveLegal(int currentRow, int currentColumn, int goalRow, int goalColumn, const Board& board) const {
    if (currentRow == goalRow && currentColumn == goalColumn)
        return false;
    int rowDiff = abs(goalRow - currentRow);
    int colDiff = abs(goalColumn - currentColumn);
    
    std::shared_ptr<Piece> goalPiece = board.getPiece(goalRow, goalColumn);
    if (goalPiece && goalPiece->getColor() == this->getColor())
        return false; // Move is not legal because a piece of the same color is in the goal position

    return (rowDiff <= 1 && colDiff <= 1);  
}