#include "MoveEvaluator.h"
#include <iostream>
#include <climits>





/**
 * @brief Constructs a MoveEvaluator for a given board and player color.
 *
 * @param board The chess board to evaluate moves on.
 * @param playerColor The color of the player ('W' for white, 'B' for black).
 */
MoveEvaluator::MoveEvaluator(Board& board, char playerColor)
    : board(board), playerColor(playerColor), moveQueue(5) {
    initializePieceValues();
}




/**
 * @brief Initializes the piece values for evaluating moves.
 *
 * This function sets the values for different chess pieces to be used in move evaluation and checks the piece strength.
 */
void MoveEvaluator::initializePieceValues() {
    pieceValues['P'] = 1;    // Pawn
    pieceValues['N'] = 3;    // Knight
    pieceValues['B'] = 3;    // Bishop
    pieceValues['R'] = 5;    // Rook
    pieceValues['Q'] = 9;    // Queen
    pieceValues['K'] = 1000; // King
}




/**
 * @brief Evaluates all possible moves for the current player up to a specified depth.
 *
 * This function evaluates all legal moves for the current player and stores the best moves
 * in a priority queue.
 *
 * @param depth The depth of move evaluation.
 */
void MoveEvaluator::evaluateMoves(int depth, int threads) {
    ThreadPool pool(threads);
    std::vector<std::future<void>> futures; 

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            std::shared_ptr<Piece> piece = board.getPiece(row, col);
            if (piece && piece->getColor() == playerColor) {
                futures.emplace_back(pool.executeTask([this, row, col, depth]() {     //
                    for (int toRow = 0; toRow < BOARD_SIZE; ++toRow) {
                        for (int toCol = 0; toCol < BOARD_SIZE; ++toCol) {

                            /*futures.emplace_back(pool.executeTask(std::bind(&MoveEvaluator::evaluateMove, this, std::placeholders::_1, 
                                std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5), row, col, toRow, toCol, depth));*/


                            if (board.getPiece(row, col)->isMoveLegal(row, col, toRow, toCol, board)) {
                                //std::lock_guard<std::mutex> lock(this->queueMutex);
                                Board board = this->board;
                                int moveScore = evaluateMove(row, col, toRow, toCol, depth, board);
                                std::lock_guard<std::mutex> lock(queueMutex);
                                moveQueue.push(Move(row, col, toRow, toCol, moveScore));
                            }
                        }
                    }

                    }));   //
            }
        }
    }

    for (auto& future : futures) {
        future.get();
    }
}





/**
 * @brief Retrieves the best moves evaluated.
 *
 * This function returns a vector of the best 5 moves stored in the priority queue.
 *
 * @return std::vector<Move> The best moves evaluated.
 */
std::vector<Move> MoveEvaluator::getBestMoves() const {
    std::vector<Move> bestMoves;
    PriorityQueue<Move, MyComparator> tempQueue = this->moveQueue; // Creating a copy of the queue
    int count = 0;
    while (!tempQueue.isEmpty() && count < 5) {
        bestMoves.push_back(tempQueue.poll());
        count++;
    }
    return bestMoves;
}




/**
 * @brief Evaluates a single move.
 *
 * This function evaluates the score of a move from the current position to the goal position,
 * considering the specified depth of evaluation.
 *
 * @param currentRow The starting row of the piece.
 * @param currentColumn The starting column of the piece.
 * @param goalRow The destination row of the piece.
 * @param goalColumn The destination column of the piece.
 * @param depth The depth of move evaluation.
 * @return int The score of the evaluated move.
 */
int MoveEvaluator::evaluateMove(int currentRow, int currentColumn, int goalRow, int goalColumn, int depth, Board& board) {
    std::shared_ptr<Piece> piece = board.getPiece(currentRow, currentColumn);
    std::shared_ptr<Piece> targetPiece = board.getPiece(goalRow, goalColumn);

    int score = 0;

    // Add value for capturing a piece
    if (targetPiece) {
        score += pieceValues[targetPiece->getName()];
    }

    // Control of the center
    if ((goalRow >= 2 && goalRow <= 5) && (goalColumn >= 2 && goalColumn <= 5)) {
        score += 3;
    }

    // Simulate the move
    std::shared_ptr<Piece> temp = board.getPiece(goalRow, goalColumn);
    board.setPiece(goalRow, goalColumn, board.getPiece(currentRow, currentColumn));
    board.setPiece(currentRow, currentColumn, nullptr);

    // Check if the move puts the piece in danger
    if(piece!= nullptr) // !!!
        score += evaluateThreats(currentRow, currentColumn, goalRow, goalColumn, piece, board);

    // Evaluate board control
    score += evaluateBoardControl();

    char opponentColor = (playerColor == 'W') ? 'B' : 'W';
    if (board.isKingInCheck(opponentColor) && !board.canEscapeCheck(opponentColor)) {
        score += 10000;  // Arbitrary high score for checkmate

    }
    if (board.isKingInCheck(playerColor))
        score -= 10000; // Arbitrary low score for losing

    // Evaluate opponent's response if depth > 0
    if (depth > 0) {
        int bestOpponentScore = INT_MIN;
        for (int row = 0; row < BOARD_SIZE; ++row) {
            for (int col = 0; col < BOARD_SIZE; ++col) {
                std::shared_ptr<Piece> opponentPiece = board.getPiece(row, col);
                if (opponentPiece && opponentPiece->getColor() != playerColor) {
                    for (int toRow = 0; toRow < BOARD_SIZE; ++toRow) {
                        for (int toCol = 0; toCol < BOARD_SIZE; ++toCol) {
                            if (opponentPiece->isMoveLegal(row, col, toRow, toCol, board)) {
                                int opponentScore = evaluateMove(row, col, toRow, toCol, depth - 1, board);
                                if (opponentScore > bestOpponentScore) {
                                    bestOpponentScore = opponentScore;
                                }
                            }
                        }
                    }
                }
            }
        }
        score -= bestOpponentScore;
    }

    // Undo the move
    board.setPiece(currentRow, currentColumn, board.getPiece(goalRow, goalColumn));
    board.setPiece(goalRow, goalColumn, temp);

    //std::cout << currentRow << currentColumn << '-' << goalRow << goalColumn << '-' << score << std::endl;

    return score;
}




/**
 * @brief Evaluates the threats to and from a piece for a given move.
 *
 * This function calculates the score based on potential threats to the piece and threats posed by the piece
 * if it moves to the specified position.
 *
 * @param currentRow The current row of the piece.
 * @param currentColumn The current column of the piece.
 * @param goalRow The goal row for the piece.
 * @param goalColumn The goal column for the piece.
 * @param piece The piece being evaluated.
 * @return int The score based on evaluated threats.
 */
int MoveEvaluator::evaluateThreats(int currentRow, int currentColumn, int goalRow, int goalColumn, const std::shared_ptr<Piece>& piece, Board& board) {
    int score = 0;
    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            std::shared_ptr<Piece> opponentPiece = board.getPiece(row, col);
            if (opponentPiece && opponentPiece->getColor() != playerColor) {
                if (opponentPiece->isMoveLegal(row, col, goalRow, goalColumn, board)) {
                    if (pieceValues[opponentPiece->getName()] < pieceValues[piece->getName()]) {
                        //std::cout << pieceValues[opponentPiece->getName()] <<'----' << pieceValues[piece->getName()] << std::endl;
                        score -= pieceValues[piece->getName()]; // In danger by a weaker piece
                    }
                }
                if (opponentPiece->isMoveLegal(row, col, currentRow, currentColumn, board)) {
                    if (pieceValues[opponentPiece->getName()] > pieceValues[piece->getName()]) {
                        score += pieceValues[opponentPiece->getName()]; // Threatening a stronger piece
                    }
                }
            }
        }
    }
    return score;
}




/**
 * @brief Evaluates the control of the board.
 *
 * This function calculates a score based on the control of the board by the player's pieces
 * compared to the opponent's pieces.
 *
 * @return int The score based on board control.
 */
int MoveEvaluator::evaluateBoardControl() const {
    int controlScore = 0;
    int playerCoverage = 0;
    int opponentCoverage = 0;

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            std::shared_ptr<Piece> piece = board.getPiece(row, col);
            if (piece) {
                for (int toRow = 0; toRow < BOARD_SIZE; ++toRow) {
                    for (int toCol = 0; toCol < BOARD_SIZE; ++toCol) {
                        if (piece->isMoveLegal(row, col, toRow, toCol, board)) {
                            if (piece->getColor() == playerColor) {
                                playerCoverage++;
                            }
                            else {
                                opponentCoverage++;
                            }
                        }
                    }
                }
            }
        }
    }

    controlScore = playerCoverage - opponentCoverage;
    return controlScore;
}




/**
 * @brief Overloaded output stream operator for a vector of Move objects.
 *
 * This function prints the details of a vector of Move objects to the provided output stream.
 *
 * @param os The output stream to print to.
 * @param moves The vector of Move objects to print.
 * @return std::ostream& The output stream.
 */
std::ostream& operator<<(std::ostream& os, const std::vector<Move>& moves) {
    for (const auto& move : moves) {
        os << move << "\n";
    }
    return os;
}
