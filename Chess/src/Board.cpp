#include "Board.h"
#include "Pieces/Rook.h"
#include "Pieces/Knight.h"
#include "Pieces/Bishop.h"
#include "Pieces/Queen.h"
#include "Pieces/King.h"
#include "Pieces/Pawn.h"
#include <cctype>  
#include <memory>  
#include <string>
#include <stdexcept>
#include <iostream>
#include <memory>  

/**
 * @brief Constructs the Board and sets up the initial pieces.
 */
Board::Board() : board(BOARD_SIZE, std::vector<std::shared_ptr<Piece>>(BOARD_SIZE)) {
    setupBoard();
}





/**
 * @brief Constructs the Board from a string representation of the board state.
 */
Board::Board(const std::string& boardStr) : board(BOARD_SIZE, std::vector<std::shared_ptr<Piece>>(BOARD_SIZE)) {
    setupBoard(boardStr);
}





/**
 * @brief Sets up the initial positions of all the pieces on the board.
 */
void Board::setupBoard() {
    // Place Rooks
    board[0][0] = createPiece('R', 'W');
    board[0][7] = createPiece('R', 'W');
    board[7][0] = createPiece('R', 'B');
    board[7][7] = createPiece('R', 'B');
    // Place Knights
    board[0][1] = createPiece('N', 'W');
    board[0][6] = createPiece('N', 'W');
    board[7][1] = createPiece('N', 'B');
    board[7][6] = createPiece('N', 'B');
    // Place Bishops
    board[0][2] = createPiece('B', 'W');
    board[0][5] = createPiece('B', 'W');
    board[7][2] = createPiece('B', 'B');
    board[7][5] = createPiece('B', 'B');
    // Place Queens
    board[0][3] = createPiece('Q', 'W');
    board[7][3] = createPiece('Q', 'B');
    // Place Kings
    board[0][4] = createPiece('K', 'W');
    board[7][4] = createPiece('K', 'B');
    // Place Pawns
    for (int i = 0; i < BOARD_SIZE; i++) {
        board[1][i] = createPiece('P', 'W');
        board[6][i] = createPiece('P', 'B');
    }
}





/**
 * @brief Sets up the board based on a string representation.
 *
 * This method initializes the board according to a given string representation.
 * The string should be of length BOARD_SIZE * BOARD_SIZE, where each character represents
 * a piece or an empty square on the board:
 * - 'R'/'r' for Rook
 * - 'N'/'n' for Knight
 * - 'B'/'b' for Bishop
 * - 'Q'/'q' for Queen
 * - 'K'/'k' for King
 * - 'P'/'p' for Pawn
 * - '#' for an empty square
 *
 * Uppercase letters represent white pieces, and lowercase letters represent black pieces.
 *
 * @param boardStr A string representing the initial state of the board.
 * @throw std::invalid_argument if the length of the boardStr is not BOARD_SIZE * BOARD_SIZE.
 */
void Board::setupBoard(const std::string& boardStr) {
    if (boardStr.size() != BOARD_SIZE * BOARD_SIZE) {
        throw std::invalid_argument("Invalid board string length");
    }

    for (int row = 0; row < BOARD_SIZE; ++row) {
        for (int col = 0; col < BOARD_SIZE; ++col) {
            char pieceChar = boardStr[row * BOARD_SIZE + col];
            char color = (std::isupper(pieceChar) ? 'W' : 'B');
            if (pieceChar == '#') {
                board[row][col] = nullptr;
            }
            else {
                board[row][col] = createPiece(std::toupper(pieceChar), color);
            }
        }
    }
}





/**
 * @brief Returns the piece at the specified position.
 *
 * This method retrieves the piece located at the specified row and column on the board.
 * If the position is out of bounds, it returns nullptr.
 *
 * @param row The row index of the position (0-based).
 * @param column The column index of the position (0-based).
 * @return std::shared_ptr<Piece> The piece at the specified position, or nullptr if the position is out of bounds or empty.
 */
std::shared_ptr<Piece> Board::getPiece(int row, int column) const {
    if(row >= 0 && row < BOARD_SIZE && column >= 0 && column < BOARD_SIZE)
        return board[row][column];
    return nullptr;
}




/**
 * @brief Sets a piece at the specified position on the board.
 *
 * This method places the given piece at the specified row and column on the board.
 *
 * @param row The row index of the position (0-based).
 * @param column The column index of the position (0-based).
 * @param piece A shared pointer to the piece to be placed on the board.
 */
void Board::setPiece(int row, int column, std::shared_ptr<Piece> piece) {
    board[row][column] = piece;
}





/**
 * @brief Creates a piece based on its type/name and color.
 *
 * This method instantiates a chess piece based on the given type and color.
 * It returns a shared pointer to the created piece.
 *
 * @param type The type of the piece ('R' for Rook, 'N' for Knight, 'B' for Bishop, 'Q' for Queen, 'K' for King, 'P' for Pawn).
 * @param color The color of the piece ('W' for white, 'B' for black).
 * @return std::shared_ptr<Piece> A shared pointer to the created piece.
 */
std::shared_ptr<Piece> Board::createPiece(const char type, const char color) {
    switch (std::toupper(type)) {
    case 'R':
        return std::make_shared<Rook>(color, type);
    case 'N':
        return std::make_shared<Knight>(color, type);
    case 'B':
        return std::make_shared<Bishop>(color, type);
    case 'Q':
        return std::make_shared<Queen>(color, type);
    case 'K':
        return std::make_shared<King>(color, type);
    case 'P':
        return std::make_shared<Pawn>(color, type);
    default:
        return nullptr;
    }
}





/**
 * @brief Checks the validity of a move and returns a code indicating the result.
 *
 * This method verifies whether a move from the current position to the goal position is valid.
 * It checks for various conditions such as the presence of a piece at the source, ownership of the piece,
 * legality of the move, and whether the move puts the player's king in check.
 *
 * @param currentRow The starting row of the piece.
 * @param currentColumn The starting column of the piece.
 * @param goalRow The destination row of the piece.
 * @param goalColumn The destination column of the piece.
 * @param playerColor The color of the player making the move.
 * @return int A code indicating the result of the move .
 */
int Board::checkMove(const int currentRow, const int currentColumn, const int goalRow, const int goalColumn, const char playerColor) {

    // This statement is handled in the Chess.cpp

    /*if (currentRow < 0 || currentRow >= BOARD_SIZE || currentColumn < 0 || 
        currentColumn >= BOARD_SIZE || goalRow < 0 || goalRow >= BOARD_SIZE || 
        goalColumn < 0 || goalColumn >= BOARD_SIZE) {
        
        return 21;
    }*/
    boardToString();
    char opponentColor = (playerColor == 'W' ? 'B' : 'W');
    if (!board[currentRow][currentColumn])
        return 11;  // there is no piece at the source

    if (board[currentRow][currentColumn]->getColor() != playerColor)
        return 12;  // the piece in the source is a piece of your opponent

    if (board[goalRow][goalColumn] && board[goalRow][goalColumn]->getColor() == playerColor)
        return 13;  // there is one of your pieces at the destination 

    // Check for castling
    if (checkForCastling(currentRow, currentColumn, goalRow, goalColumn, playerColor)) {
        return 43;  // Castling performed successfully
    }

    if (!board[currentRow][currentColumn]->isMoveLegal(currentRow, currentColumn, goalRow, goalColumn, *this))
        return 21;  // illegal movement of that piece

    
    // Simulate the move
    std::shared_ptr<Piece> temp = board[goalRow][goalColumn];
    board[goalRow][goalColumn] = board[currentRow][currentColumn];
    board[currentRow][currentColumn] = nullptr;

    // Check if the move leaves the player's own king in check
    bool causesSelfCheck = isKingInCheck(playerColor);

    // Undo the move
    board[currentRow][currentColumn] = board[goalRow][goalColumn];
    board[goalRow][goalColumn] = temp;

    // If the move leaves the player's own king in check, it is illegal
    if (causesSelfCheck) {
        return 31;  // illegal movement of that piece (because it does not protect the king)
    }

    

    // Finalize the move (now that we know it does not leave the king in check) 
    board[goalRow][goalColumn] = board[currentRow][currentColumn];
    board[currentRow][currentColumn] = nullptr;

    // Check if the move causes checkmate
    bool causesCheckmate = isKingInCheck(opponentColor) && !canEscapeCheck(opponentColor); // out of range 

    //win the game, i will add this in the future, you did not ask for that 
    if (causesCheckmate) {
        if(playerColor=='W')
            gameState = WHITE_WIN;
        else
            gameState = BLACK_WIN;

        return 44;  // this movement will cause checkmate
    }

    if (handlePawnPromotion(goalRow, board[goalRow][goalColumn]))
        return 45;
    
    // Check if the move causes check
    if (isKingInCheck(opponentColor)) {
        return 41;  // the last movement was legal and caused check
    }
    else {
        return 42;  // the last movement was legal, next turn
    }
}





/**
 * @brief Retrieves the king of the specified color.
 *
 * This method returns a reference to the king piece of the given color on the board.
 * If the king is not found, it returns a reference to a static null shared pointer.
 *
 * @param color The color of the king ('W' for white, 'B' for black).
 * @return std::shared_ptr<Piece>& A reference to the king piece of the specified color.
 */
std::shared_ptr<Piece>& Board::getTheKingByColor(const char color) {
    for (auto& row : board) {
        for (auto& piece : row) {
            if (piece && piece->getName() == 'K' && piece->getColor() == color) {
                return piece;
            }
        }
    }
    // Return a static null shared_ptr to ensure the return reference is always valid.
    // Returning just nullptr would be invalid as it would be a reference to a temporary value.
    static std::shared_ptr<Piece> nullPiece = nullptr; // i make this because will return a refrence value
    return nullPiece;

}





/**
 * @brief Retrieves the position of the king of the specified color.
 *
 * This method returns the position of the king of the given color on the board as a pair of row and column indices.
 * If the king is not found, it returns a pair of invalid indices (-1, -1).
 *
 * @param color The color of the king ('W' for white, 'B' for black).
 * @return std::pair<int, int> The row and column indices of the king's position, or (-1, -1) if the king is not found.
 */
std::pair<int, int> Board::getKingPositionByColor(const char color) {
    for (int row = 0; row < board.size(); ++row) {
        for (int col = 0; col < board[row].size(); ++col) {
            if (board[row][col] && board[row][col]->getName() == 'K' && board[row][col]->getColor() == color) {
                return { row, col };
            }
        }
    }
    return { -1, -1 };  // Return an invalid position if the king is not found
}





/**
 * @brief Checks if the king of the specified color is in check.
 *
 * This method determines whether the king of the given color is in check.
 * It iterates over all pieces on the board and checks if any of them can legally move to the king's position.
 *
 * @param color The color of the king ('W' for white, 'B' for black).
 * @return bool True if the king is in check, false otherwise.
 */
bool Board::isKingInCheck(const char color) {
    std::pair<int, int> kingPosition = getKingPositionByColor(color);
    int kingRow = kingPosition.first;
    int kingColumn = kingPosition.second;

    if (kingRow == -1 || kingColumn == -1)
        return false;  // King not found (shouldn't happen in a valid game)

    for (int row = 0; row < board.size(); ++row) {
        for (int col = 0; col < board[row].size(); ++col) {
            std::shared_ptr<Piece> piece = board[row][col];
            if (piece && piece->getColor() != color) {
                if (piece->isMoveLegal(row, col, kingRow, kingColumn, *this)) {
                    return true;  // King is in check
                }
            }
        }
    }
    return false;
}





/**
 * @brief Checks if the king of the specified color can escape check.
 *
 * This method determines whether the king of the given color can escape check by making a legal move.
 * It iterates over all pieces of the given color and checks if any legal move can remove the check condition.
 *
 * @param color The color of the king ('W' for white, 'B' for black).
 * @return bool True if the king can escape check, false otherwise.
 */
bool Board::canEscapeCheck(const char color) {
    for (int currentRow = 0; currentRow < BOARD_SIZE; ++currentRow) {
        for (int currentColumn = 0; currentColumn < BOARD_SIZE; ++currentColumn) {
            std::shared_ptr<Piece> piece = board[currentRow][currentColumn];

            // Check if the cell contains a piece of the current player's color
            if (piece && piece->getColor() == color) {
                for (int goalRow = 0; goalRow < BOARD_SIZE; ++goalRow) {
                    for (int goalColumn = 0; goalColumn < BOARD_SIZE; ++goalColumn) {
                        if (goalRow == currentRow && goalColumn == currentColumn)
                            continue;  // Skip if the goal is the same as the current position

                        // Check if the piece can legally move to the goal position
                        if (piece->isMoveLegal(currentRow, currentColumn, goalRow, goalColumn, *this)) {
                            // Simulate the move
                            std::shared_ptr<Piece> temp = board[goalRow][goalColumn];
                            board[goalRow][goalColumn] = piece;
                            board[currentRow][currentColumn] = nullptr;

                            bool isInCheck = isKingInCheck(color);

                            // Undo the move
                            board[currentRow][currentColumn] = piece;
                            board[goalRow][goalColumn] = temp;

                            if (!isInCheck) {
                                /*std::cout << "Move from (" << currentRow << ", " << currentColumn << ") to ("
                                    << goalRow << ", " << goalColumn << ") is legal and avoids check." << std::endl;*/
                                return true;  // Found a legal move to escape check
                            }
                        }
                    }
                }
            }
        }
    }
    return false;
}





/**
 * @brief Checks if castling is possible and performs it if legal.
 *
 * This method verifies whether castling is possible for the king at the given position.
 * It checks for the conditions required for castling and performs the move if it is legal.
 *
 * @param currentRow The row of the king's current position.
 * @param currentColumn The column of the king's current position.
 * @param goalRow The row of the king's destination position.
 * @param goalColumn The column of the king's destination position.
 * @param playerColor The color of the player making the move.
 * @return bool True if castling was performed successfully, false otherwise.
 */
bool Board::checkForCastling(int currentRow, int currentColumn, int goalRow, int goalColumn, const char playerColor) {
    if (board[currentRow][currentColumn]->getName() == 'K' && !board[currentRow][currentColumn]->hasMoved() && currentRow == goalRow) {
        bool validCastling = false;

        // Handle kingside castling
        if (currentColumn == goalColumn - 2) {
            // Check if the rook on the kingside exists and hasn't moved
            if (board[currentRow][7] != nullptr && !board[currentRow][7]->hasMoved()) {
                // Check if the squares between the king and rook are empty
                if (board[currentRow][currentColumn + 1] == nullptr && board[currentRow][currentColumn + 2] == nullptr) {
                    // Perform the move and check if it puts the king in check
                    std::shared_ptr<Piece> temp = board[goalRow][goalColumn];
                    board[goalRow][goalColumn] = board[currentRow][currentColumn];
                    board[currentRow][currentColumn] = nullptr;

                    // Check if the move leaves the player's own king in check
                    bool causesSelfCheck = isKingInCheck(playerColor);

                    // Undo the move
                    board[currentRow][currentColumn] = board[goalRow][goalColumn];
                    board[goalRow][goalColumn] = temp;

                    if (!causesSelfCheck) {
                        board[goalRow][goalColumn] = board[currentRow][currentColumn];
                        board[goalRow][currentColumn + 1] = board[currentRow][7];
                        board[currentRow][7] = nullptr;
                        board[currentRow][currentColumn] = nullptr;

                        validCastling = true;

                        std::shared_ptr<Piece> rook_ = board[goalRow][currentColumn + 1];
                        auto rookPiece = std::dynamic_pointer_cast<Rook>(rook_);  // Cast to King

                        if (rookPiece) {  // Check if the cast was successful
                            rookPiece->FirstMove = false;  // Access and modify FirstMove
                        }
                    }
                }
            }
        }
        // Handle queenside castling
        else if (currentColumn == goalColumn + 2) {
            // Check if the rook on the queenside exists and hasn't moved
            if (board[currentRow][0] != nullptr && !board[currentRow][0]->hasMoved()) {
                // Check if the squares between the king and rook are empty
                if (board[currentRow][currentColumn - 1] == nullptr && board[currentRow][currentColumn - 2] == nullptr && board[currentRow][currentColumn - 3] == nullptr) {
                    // Perform the move and check if it puts the king in check
                    std::shared_ptr<Piece> temp = board[goalRow][goalColumn];
                    board[goalRow][goalColumn] = board[currentRow][currentColumn];
                    board[currentRow][currentColumn] = nullptr;

                    // Check if the move leaves the player's own king in check
                    bool causesSelfCheck = isKingInCheck(playerColor);

                    // Undo the move
                    board[currentRow][currentColumn] = board[goalRow][goalColumn];
                    board[goalRow][goalColumn] = temp;

                    if (!causesSelfCheck) {
                        board[goalRow][goalColumn] = board[currentRow][currentColumn];
                        board[goalRow][currentColumn - 1] = board[currentRow][0];
                        board[currentRow][0] = nullptr;
                        board[currentRow][currentColumn] = nullptr;

                        validCastling = true;

                        std::shared_ptr<Piece> rook_ = board[goalRow][currentColumn - 1];
                        auto rookPiece = std::dynamic_pointer_cast<Rook>(rook_);  // Cast to King

                        if (rookPiece) {  // Check if the cast was successful
                            rookPiece->FirstMove = false;  // Access and modify FirstMove
                        }
                    }
                }
            }
        }

        if (validCastling) {
            std::shared_ptr<Piece> piece = board[currentRow][currentColumn];
            auto kingPiece = std::dynamic_pointer_cast<King>(piece);  // Cast to King

            if (kingPiece) {  // Check if the cast was successful
                kingPiece->FirstMove = false;  // Access and modify FirstMove
            }
            return true;  // Castling performed successfully
        }
    }
    return false;
}





/**
 * @brief Retrieves the current game state.
 *
 * This method returns the current state of the game, indicating whether white wins, black wins, the game is a draw, or still playing.
 *
 * @return GameState The current state of the game.
 */
Board::GameState Board::getGameState() const {
    return gameState;
}



/**
 * @brief Gets the best move for the given player color with the specified depth.
 *
 * This function uses the MoveEvaluator to evaluate all possible moves for the given player color
 * up to the specified depth. It returns the best move found.
 *
 * @param playerColor The color of the player ('W' for white, 'B' for black).
 * @param depth The depth of the move evaluation.
 * @return Move The best move found for the given player color.
 * @throw std::runtime_error If no valid moves are available.
 */
Move Board::getBestMove(char playerColor, int depth, size_t numThreads) {
    MoveEvaluator evaluator(*this, playerColor/*, numThreads*/);
    evaluator.evaluateMoves(depth, numThreads);
    std::vector<Move> bestMoves = evaluator.getBestMoves();
    //std::cout << bestMoves << std::endl;

    if (!bestMoves.empty()) {
        return bestMoves.front(); // Return the best move
    }

    throw std::runtime_error("No valid moves available.");
}





/**
 * @brief Handles the promotion of a pawn when it reaches the end of the board.
 *
 * This function prompts the user to choose a piece for the pawn to be promoted to when it reaches
 * the last row of the board. The user can choose to promote the pawn to a Queen, Rook, Bishop, or Knight.
 *
 * @param goalRow The row where the pawn has reached.
 * @param piece The shared pointer to the pawn piece.
 * @return bool True if the promotion was successful, false otherwise.
 */
bool Board::handlePawnPromotion(int goalRow, std::shared_ptr<Piece>& piece) {
    if (!piece)
        return false;

    if (piece->getName() == 'P' && (goalRow == 0 || goalRow == 7)) {
        char choice;
        std::cout << "Promote pawn to (Q/R/B/N): ";
        std::cin >> choice;
        char color = piece->getColor();
        switch (choice) {
        case 'Q':
            piece = createPiece('Q',color);
            Pawn_promotion_value = ( color=='W'? Q : q );
            return true;
        case 'R':
            piece = createPiece('R', color);
            Pawn_promotion_value = ( color == 'W' ? R : r );
            return true;
        case 'B':
            piece = createPiece('B', color);
            Pawn_promotion_value = ( color == 'W' ? B : b );
            return true;
        case 'N':
            piece = createPiece('N', color);
            Pawn_promotion_value = ( color == 'W' ? N : n );
            return true;
        default:
            return false;
        }
        return false;
    }
    return false;
}





/**
 * @brief Converts the board to a string representation.
 *
 * This function creates a string representation of the current state of the board.
 * Each piece is represented by its character, and empty squares are represented by '#'.
 * White pieces are represented in uppercase, and black pieces are represented in lowercase.
 *
 * @return std::string The string representation of the board.
 */
std::string Board::boardToString() const {
    std::stringstream ss;
    for (const auto& row : board) {
        for (const auto& piece : row) {
            if (piece) {
                char pieceChar = piece->getName();
                if (piece->getColor() == 'W') {
                    ss << pieceChar;  // White pieces already in uppercase
                }
                else {
                    ss << char(std::tolower(pieceChar));  // Black pieces in lowercase
                }
            }
            else {
                ss << '#';
            }
        }
    }
    std::string boardStr = ss.str();
    //std::cout << boardStr << std::endl;
    return boardStr;
}




/**
 * @brief Gets the current pawn promotion value.
 *
 * This function returns the current value set for pawn promotion.
 * The value corresponds to the type of piece to which a pawn will be promoted
 * when it reaches the end of the board.
 *
 * @return Board::PawnPromotionValue The current pawn promotion value.
 */
Board::PawnPromotionValue Board::getPawnPromotionValue() {
    return Pawn_promotion_value;
}
