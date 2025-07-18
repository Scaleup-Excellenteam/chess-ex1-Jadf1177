#pragma once
#include "Board.h"
#include "Move.h"
#include "PriorityQueue.h"
#include <unordered_map>
#include <vector>
#include "ThreadPool.h"
#include <mutex>  

//struct MoveInfo {
//    int row, col, toRow, toCol;
//    std::future<int> future;
//};

class MoveEvaluator {
public:
    MoveEvaluator(Board& board, char playerColor);
    void evaluateMoves(int depth, int threads);
    std::vector<Move> getBestMoves() const;

private:
    Board& board;
    char playerColor;
    PriorityQueue<Move, MyComparator> moveQueue;
    std::unordered_map<char, int> pieceValues;
    std::mutex queueMutex;  // Add this declaration

    //ThreadPool pool;
    void initializePieceValues();
    int evaluateMove(int currentRow, int currentColumn, int goalRow, int goalColumn, int depth, Board& board);
    int evaluateBoardControl() const;
    int evaluateThreats(int currentRow, int currentColumn, int goalRow, int goalColumn, const std::shared_ptr<Piece>& piece, Board& board);

    //void evaluatePieceMoves(int row, int col, int depth);
};

std::ostream& operator<<(std::ostream& os, const std::vector<Move>& moves);