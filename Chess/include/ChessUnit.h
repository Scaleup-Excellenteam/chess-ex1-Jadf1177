#pragma once
#include <string>

class Board;

class ChessUnit { 
protected:
    bool isLight; 
    int y;        
    int x;        

public:
    ChessUnit(bool light, int yPos, int xPos); 
    virtual ~ChessUnit() {}

    virtual bool validate(int dy, int dx, const Board& b) const = 0; 
    virtual char symbol() const = 0; 

    bool lightSide() const; 
    int getY() const;
    int getX() const;
    void relocate(int ny, int nx); 

    bool pathObstructed(int ty, int tx, const Board& board) const;
};