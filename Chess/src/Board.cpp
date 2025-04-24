#include "Board.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
#include "Pawn.h"
#include <cctype>
#include <algorithm> // for std::swap

Board::Board(const std::string& setup) {
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            char c = setup[y * 8 + x];
            if (c == '#') {
                grid[y][x] = nullptr;
                continue;
            }
            bool white = isupper(c);
            switch (tolower(c)) {
            case 'r': grid[y][x] = new Rook(white, y, x); break;
            case 'n': grid[y][x] = new Knight(white, y, x); break;
            case 'b': grid[y][x] = new Bishop(white, y, x); break;
            case 'q': grid[y][x] = new Queen(white, y, x); break;
            case 'k': grid[y][x] = new King(white, y, x); break;
            case 'p': grid[y][x] = new Pawn(white, y, x); break;
            default: grid[y][x] = nullptr;
            }
        }
    }
}

Board::~Board() {
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            delete grid[y][x];
            grid[y][x] = nullptr;
        }
    }
}

Board::Board(const Board& source) {
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            if (source.grid[y][x]) {
                switch (tolower(source.grid[y][x]->symbol())) {
                case 'r': grid[y][x] = new Rook(*dynamic_cast<Rook*>(source.grid[y][x])); break;
                case 'n': grid[y][x] = new Knight(*dynamic_cast<Knight*>(source.grid[y][x])); break;
                case 'b': grid[y][x] = new Bishop(*dynamic_cast<Bishop*>(source.grid[y][x])); break;
                case 'q': grid[y][x] = new Queen(*dynamic_cast<Queen*>(source.grid[y][x])); break;
                case 'k': grid[y][x] = new King(*dynamic_cast<King*>(source.grid[y][x])); break;
                case 'p': grid[y][x] = new Pawn(*dynamic_cast<Pawn*>(source.grid[y][x])); break;
                default: grid[y][x] = nullptr;
                }
            }
            else {
                grid[y][x] = nullptr;
            }
        }
    }
}

Board& Board::operator=(Board rhs) {
    swap(*this, rhs);
    return *this;
}

ChessUnit* Board::fetch(int y, int x) const {
    if (x < 0 || x >= 8 || y < 0 || y >= 8) return nullptr;
    return grid[y][x];
}

bool Board::checkThreat(bool white) const {
    // Find king's position
    int kingX = -1, kingY = -1;
    char targetSymbol = white ? 'K' : 'k';

    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            ChessUnit* current = grid[y][x];
            if (current && current->symbol() == targetSymbol) {
                kingX = x;
                kingY = y;
                break;
            }
        }
        if (kingX != -1) break;
    }

    if (kingX == -1) return false;

    // Check all opposing pieces
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            ChessUnit* attacker = grid[y][x];
            if (attacker && attacker->lightSide() != white) {
                if (attacker->validate(kingX, kingY, *this)) {
                    return true;
                }
            }
        }
    }
    return false;
}

void Board::move(int sy, int sx, int dy, int dx) {
    ChessUnit* movingPiece = grid[sy][sx];
    if (!movingPiece) return;

    // Handle capture
    delete grid[dy][dx];
    grid[dy][dx] = movingPiece;
    grid[sy][sx] = nullptr;

    // Update piece's internal position
    movingPiece->relocate(dy, dx);
}

void swap(Board& first, Board& second) noexcept {
    using std::swap;
    for (int y = 0; y < 8; ++y) {
        for (int x = 0; x < 8; ++x) {
            swap(first.grid[y][x], second.grid[y][x]);
        }
    }
}