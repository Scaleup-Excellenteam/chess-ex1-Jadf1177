#pragma once
#include <iostream>

class Move {
public:
    Move(int fromRow, int fromCol, int toRow, int toCol, int score)
        : fromRow(fromRow), fromCol(fromCol), toRow(toRow), toCol(toCol), score(score) {}
    Move() : fromRow(-1), fromCol(-1), toRow(-1), toCol(-1), score(-1) {} // Default constructor representing an invalid move

    int getFromRow() const { return fromRow; }
    int getFromCol() const { return fromCol; }
    int getToRow() const { return toRow; }
    int getToCol() const { return toCol; }
    int getScore() const { return score; }

    friend std::ostream& operator<<(std::ostream& os, const Move& move);

    bool operator<(const Move& other) const {
        return score < other.score;
    }

private:
    int fromRow;
    int fromCol;
    int toRow;
    int toCol;
    int score;
};