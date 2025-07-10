#pragma once
#include "Piece.h"
#include "Board.h"

class Rook : virtual public Piece {
    
public:
    Rook(const char color, const char name) : Piece(color, name), FirstMove(true) {}
    virtual bool isMoveLegal(int currentRow, int currentColumn, int goalRow, int goalColumn, const Board& board) const override;
    mutable bool FirstMove;
    bool hasMoved() const override { return !FirstMove; }

};
