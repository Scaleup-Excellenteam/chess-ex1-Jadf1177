/**
 * @brief Base class for all chess pieces.
 *
 * This class defines common functionality for all chess pieces, including their color and name,
 * as well as methods for checking the legality of moves.
 */

#pragma once
class Board;  // Forward declaration to avoid circular dependency

class Piece {
protected:
    const char color;  // 'W' for white, 'B' for black
    char name; // B K N P Q R
public:
    Piece(char color, char name) : color(color), name(name) {}
    virtual ~Piece() {}

    char getColor() const { return color; }
    char getName() const { return name; }
    virtual bool hasMoved() const { return true; }
    virtual void setName(const char name) { this->name = name; }
    virtual bool isMoveLegal(int currentRow, int currentColumn, int goalRow, int goalColumn, const Board& board) const = 0;
};
