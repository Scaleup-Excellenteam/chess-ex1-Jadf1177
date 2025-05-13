#pragma once
#include "Board.h"
#include "Move.h"
#include "PriorityQueue.h"
#include <unordered_map>
#include <vector>

class MoveEvaluator {
public:
    MoveEvaluator(Board& board, char playerColor);
    void evaluateMoves(int depth);
    std::vector<Move> getBestMoves() const;

private:
    Board& board;
    char playerColor;
    PriorityQueue<Move, MyComparator> moveQueue;
    std::unordered_map<char, int> pieceValues;

    void initializePieceValues();
    int evaluateMove(int currentRow, int currentColumn, int goalRow, int goalColumn, int depth);
    int evaluateBoardControl() const;
    int evaluateThreats(int currentRow, int currentColumn, int goalRow, int goalColumn, const std::shared_ptr<Piece>& piece);
};

std::ostream& operator<<(std::ostream& os, const std::vector<Move>& moves);