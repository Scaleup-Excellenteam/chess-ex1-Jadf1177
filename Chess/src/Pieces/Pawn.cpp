#include "Pieces/Pawn.h"

// Pawn moves forward by one square, but captures diagonally
bool Pawn::isMoveLegal(int currentRow, int currentColumn, int goalRow, int goalColumn, const Board& board) const {

    int forward = (color == 'W') ? 1 : -1;  // White moves up, Black moves down

    // Move forward
    if (currentColumn == goalColumn && goalRow == currentRow + forward) {
        // Ensure the destination is empty
        if (!board.getPiece(goalRow, goalColumn)) {
            return true;
        }
    }
    // Move forward two squares from starting position
    else if (currentColumn == goalColumn && goalRow == currentRow + 2 * forward) {
        if ((color == 'W' && currentRow == 1) || (color == 'B' && currentRow == 6))
            if (!board.getPiece(goalRow, goalColumn) && !board.getPiece(currentRow + forward, currentColumn))
                return true;
    }
    // Capture diagonally
    else if (abs(currentColumn - goalColumn) == 1 && goalRow == currentRow + forward) {
        if (board.getPiece(goalRow, goalColumn) && board.getPiece(goalRow, goalColumn)->getColor() != color)
            return true;  // Capture diagonally if there is an opponent's piece
    }
    return false;
}
