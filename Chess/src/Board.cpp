#include "Board.h"
#include <cmath>

Board::Board(const std::string& boardStr) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            char c = boardStr[i * 8 + j];
            switch (toupper(c)) {
            case 'R': pieces[i][j] = new Rook(isupper(c)); break;
            case 'N': pieces[i][j] = new Knight(isupper(c)); break;
            case 'B': pieces[i][j] = new Bishop(isupper(c)); break;
            case 'Q': pieces[i][j] = new Queen(isupper(c)); break;
            case 'K': pieces[i][j] = new King(isupper(c)); break;
            case 'P': pieces[i][j] = new Pawn(isupper(c)); break;
            default: pieces[i][j] = nullptr; break;
            }
        }
    }
}

Board::Board(const Board& other) {
    copyFrom(other);
}

Board::~Board() {
    clear();
}

Board& Board::operator=(const Board& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

Piece* Board::getPiece(int row, int col) const {
    if (row < 0 || row >= 8 || col < 0 || col >= 8) return nullptr;
    return pieces[row][col];
}

void Board::movePiece(int srcRow, int srcCol, int destRow, int destCol) {
    delete pieces[destRow][destCol];
    pieces[destRow][destCol] = pieces[srcRow][srcCol];
    pieces[srcRow][srcCol] = nullptr;
}

bool Board::isPathClear(int srcRow, int srcCol, int destRow, int destCol) const {
    int rowStep = (destRow > srcRow) ? 1 : (destRow < srcRow) ? -1 : 0;
    int colStep = (destCol > srcCol) ? 1 : (destCol < srcCol) ? -1 : 0;

    int steps = std::max(abs(destRow - srcRow), abs(destCol - srcCol));
    for (int i = 1; i < steps; ++i) {
        int checkRow = srcRow + i * rowStep;
        int checkCol = srcCol + i * colStep;
        if (getPiece(checkRow, checkCol) != nullptr) return false;
    }
    return true;
}

bool Board::isInCheck(bool isWhite) const {
    int kingRow, kingCol;
    if (!findKing(isWhite, kingRow, kingCol)) return false;

    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = getPiece(i, j);
            if (piece && piece->isWhite() != isWhite) {
                if (piece->isValidMove(i, j, kingRow, kingCol, *this)) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Board::clear() {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            delete pieces[i][j];
            pieces[i][j] = nullptr;
        }
    }
}

void Board::copyFrom(const Board& other) {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            pieces[i][j] = other.pieces[i][j] ? other.pieces[i][j]->clone() : nullptr;
        }
    }
}

bool Board::findKing(bool isWhite, int& kingRow, int& kingCol) const {
    for (int i = 0; i < 8; ++i) {
        for (int j = 0; j < 8; ++j) {
            Piece* piece = getPiece(i, j);
            if (piece && piece->isWhite() == isWhite && dynamic_cast<King*>(piece)) {
                kingRow = i;
                kingCol = j;
                return true;
            }
        }
    }
    return false;
}