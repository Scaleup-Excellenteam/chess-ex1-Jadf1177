#pragma once
#include <iostream>
#include <Windows.h>
#include <string>
#include "Move.h"
using std::cout;
using std::cin; 
using std::endl;
using std::string; 

const int _SIZE = 21;

class Chess {
	unsigned char m_board[_SIZE][_SIZE] = { 0 };
	bool m_turn = true;
	string m_boardString;
	string m_input;
	string m_msg = "\n";
	string m_errorMsg = "\n";
	int m_codeResponse;
	Move move;
	char pawnChangedTo;

	void clear() const;
	void setFrames();
	void setPieces();
	void show() const;
	void displayBoard() const;
	void showAskInput() const;
	bool isSame() const;
	bool isValid() const;
	bool isExit() const;
	void excute();
	void doTurn();
	void executeCastling();
	void excutePromotePawn(char pawnChangedTo);

public:
	Chess(const string& start = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr");
	Chess(const Chess&)=delete;
	Chess& operator=(const Chess&) = delete;
	string getInput();
	void setCodeResponse(int codeResponse);
	void SetEvaluateMove(Move move);
	enum GameState { WHITE_WIN, BLACK_WIN, DRAW, STILL_PLAYING };
	GameState gameState;
	void setGameState(GameState state); 
	void changeBoardString(string newBoard);
	void setpawnChangedTo(char pawnChangedTo);

};