#pragma once
#include "Piece.h"
#include "Board.h"
#include "Pieces/Rook.h"
#include "Pieces/Bishop.h"
class Queen : public Rook, public Bishop {
public:
    Queen(const char color, const char name) : Piece(color, name), Rook(color, name), Bishop(color, name) {}
    virtual bool isMoveLegal(int currentRow, int currentColumn, int goalRow, int goalColumn, const Board& board) const override;
};
