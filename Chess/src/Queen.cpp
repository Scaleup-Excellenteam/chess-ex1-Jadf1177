#include "Queen.h"
#include "Board.h"
#include "Rook.h"
#include "Bishop.h"
#include <vector>

Queen::Queen(bool light, int y, int x)
    : Piece(light ? 'W' : 'B', 'Q'), Rook(light, y, x), Bishop(light, y, x), ChessUnit(light, y, x) {}

bool Queen::validate(int ty, int tx, const Board& board) const {
    if ((y != ty && x != tx) && (abs(ty - y) != abs(tx - x))) return false;
    if (pathObstructed(ty, tx, board)) return false;

    ChessUnit* target = board.fetch(ty, tx);
    return !(target && target->lightSide() == isLight);
}

char Queen::symbol() const {
    return isLight ? 'Q' : 'q';
}

std::vector<std::pair<int, int>> Queen::generateMoves(const Board& board) const {
    std::vector<std::pair<int, int>> moves;

    // Combine rook and bishop moves
    Rook tempRook(isLight, y, x);
    Bishop tempBishop(isLight, y, x);

    auto rookMoves = tempRook.generateMoves(board);
    auto bishopMoves = tempBishop.generateMoves(board);

    moves.insert(moves.end(), rookMoves.begin(), rookMoves.end());
    moves.insert(moves.end(), bishopMoves.begin(), bishopMoves.end());

    return moves;
}