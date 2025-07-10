#pragma once
#include "Piece.h"
#include "Board.h"
#include "Rook.h"

class King : public Piece {
public:
    King(const char color, const char name) : Piece(color, name), FirstMove(true) {}
    virtual bool isMoveLegal(int currentRow, int currentColumn, int goalRow, int goalColumn, const Board& board) const override;
    mutable bool FirstMove = true;
    bool hasMoved() const override { return !FirstMove; }

};
