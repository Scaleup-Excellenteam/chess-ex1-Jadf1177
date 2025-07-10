
#pragma once
class Board;

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
