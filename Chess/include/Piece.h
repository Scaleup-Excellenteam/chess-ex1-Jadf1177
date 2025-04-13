#pragma once
class Board; // Forward declaration instead of #include "Board.h"

class Piece {
public:
    virtual ~Piece() = default;
    virtual bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const = 0;
    virtual bool isWhite() const = 0;
    virtual char getSymbol() const = 0;
    virtual Piece* clone() const = 0;
};

class Rook : public Piece {
    bool white;
public:
    Rook(bool isWhite) : white(isWhite) {}
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const override;
    bool isWhite() const override { return white; }
    char getSymbol() const override { return white ? 'R' : 'r'; }
    Piece* clone() const override { return new Rook(*this); }
};

class Knight : public Piece {
    bool white;
public:
    Knight(bool isWhite) : white(isWhite) {}
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const override;
    bool isWhite() const override { return white; }
    char getSymbol() const override { return white ? 'N' : 'n'; }
    Piece* clone() const override { return new Knight(*this); }
};

class Bishop : public Piece {
    bool white;
public:
    Bishop(bool isWhite) : white(isWhite) {}
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const override;
    bool isWhite() const override { return white; }
    char getSymbol() const override { return white ? 'B' : 'b'; }
    Piece* clone() const override { return new Bishop(*this); }
};

class Queen : public Piece {
    bool white;
public:
    Queen(bool isWhite) : white(isWhite) {}
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const override;
    bool isWhite() const override { return white; }
    char getSymbol() const override { return white ? 'Q' : 'q'; }
    Piece* clone() const override { return new Queen(*this); }
};

class King : public Piece {
    bool white;
public:
    King(bool isWhite) : white(isWhite) {}
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const override;
    bool isWhite() const override { return white; }
    char getSymbol() const override { return white ? 'K' : 'k'; }
    Piece* clone() const override { return new King(*this); }
};

class Pawn : public Piece {
    bool white;
public:
    Pawn(bool isWhite) : white(isWhite) {}
    bool isValidMove(int srcRow, int srcCol, int destRow, int destCol, const Board& board) const override;
    bool isWhite() const override { return white; }
    char getSymbol() const override { return white ? 'P' : 'p'; }
    Piece* clone() const override { return new Pawn(*this); }
};