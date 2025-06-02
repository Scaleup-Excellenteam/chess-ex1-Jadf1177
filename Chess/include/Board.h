#pragma once
#include <vector>
#include <memory>
#include "Piece.h"  // Adjust the path if necessary.
#include <string>
#include "Move.h"
#include "MoveEvaluator.h"
#include <sstream>

const int BOARD_SIZE = 8;

class Board {
public:
   
    enum GameState { WHITE_WIN, BLACK_WIN, DRAW, STILL_PLAYING };
    enum PawnPromotionValue {Q = 'Q',R = 'R',B = 'B',N = 'N',q = 'q',r = 'r',b = 'b',n = 'n'};
    Board();
    Board(const std::string& );
    int checkMove(const int currentRow, const int currentColumn, const int goalRow, const int goalColumn, const char playerColor);
    void setupBoard();
    void setupBoard(const std::string&);
    std::shared_ptr<Piece> getPiece(int row, int column) const;
    void setPiece(int row, int column, std::shared_ptr<Piece> piece);
    GameState getGameState() const;
    bool isKingInCheck(const char color);
    Move getBestMove(char playerColor, int depth = 1, size_t numThreads=2);
    std::string boardToString() const;
    bool handlePawnPromotion(int goalRow, std::shared_ptr<Piece>& piece);
    bool canEscapeCheck(const char color);
    PawnPromotionValue getPawnPromotionValue();
private:
    std::vector<std::vector<std::shared_ptr<Piece>>> board;
    std::shared_ptr<Piece> createPiece(const char type, const char color);
    std::shared_ptr<Piece>& getTheKingByColor(const char color);
    std::pair<int, int> getKingPositionByColor(const char color);
    bool checkForCastling(int currentRow, int currentColumn, int goalRow, int goalColumn, const char playerColor);
   
    GameState gameState;
    PawnPromotionValue Pawn_promotion_value;

};
