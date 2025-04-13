#pragma once
#include "Piece.h"
#include <string>
#include <vector>

class Board {
public:
    Board(const std::string& boardStr);
    Board(const Board& other);
    ~Board();
    Board& operator=(const Board& other);

    Piece* getPiece(int row, int col) const;
    void movePiece(int srcRow, int srcCol, int destRow, int destCol);
    bool isPathClear(int srcRow, int srcCol, int destRow, int destCol) const;
    bool isInCheck(bool isWhite) const;

private:
    Piece* pieces[8][8];
    void clear();
    void copyFrom(const Board& other);
    bool findKing(bool isWhite, int& kingRow, int& kingCol) const;
};