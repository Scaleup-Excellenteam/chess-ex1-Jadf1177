	#include "Chess.h"
#include "ChessExceptions.h"

// clear the screen "cls"
void Chess::clear() const 
{
	COORD topLeft = { 0, 0 };
	HANDLE console = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_SCREEN_BUFFER_INFO screen;
	DWORD written;

	GetConsoleScreenBufferInfo(console, &screen);
	FillConsoleOutputCharacterA(
		console, ' ', screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	FillConsoleOutputAttribute(
		console, FOREGROUND_GREEN | FOREGROUND_RED | FOREGROUND_BLUE,
		screen.dwSize.X * screen.dwSize.Y, topLeft, &written
	);
	SetConsoleCursorPosition(console, topLeft);
}
// create the GUI - ASCII art
void Chess::setFrames() 
{ 
	// set all to ' ' (space bar ascii value 32) instead of 0  
	{
		for (size_t row = 0; row < _SIZE; ++row)
			for (size_t col = 0; col < _SIZE; ++col)
				m_board[row][col] = 32;
	}
	// set out frame
	{
		m_board[0][0] = 201;  m_board[0][20] = 187;
		m_board[20][0] = 200; m_board[20][20] = 188;

		for (size_t i = 1; i < 20; ++i)
		{
			m_board[0][i] = 205;
			m_board[20][i] = 205;
			m_board[i][0] = 186;
			m_board[i][20] = 186;
		}
	} 

	// set in side frame 
	{
		m_board[2][2] = 218;  m_board[2][18] = 191;
		m_board[18][2] = 192; m_board[18][18] = 217;

		for (size_t i = 4; i < 17; i += 2)
		{
			m_board[2][i] = 194;
			m_board[18][i] = 193;
			m_board[i][2] = 195;
			m_board[i][18] = 180;
		}

		for (size_t i = 2; i < 19; i += 2)
			for (size_t j = 3; j < 19; j += 2)
				m_board[i][j] = 196;
		
		for (size_t i = 3; i < 18; i += 2)
			for (size_t j = 2; j < 19; j += 2)
				m_board[i][j] = 179;

		for (size_t i = 4; i < 17; i += 2)
			for (size_t j = 4; j < 17; j += 2)
				m_board[i][j] = 197;

		for (size_t i = 4; i < 17; i += 2)
			m_board[2][i] = 194;
		for (size_t i = 4; i < 17; i += 2)
			m_board[18][i] = 193;
		for (size_t i = 4; i < 17; i += 2)
			m_board[i][2] = 195;
		for (size_t i = 4; i < 17; i += 2)
			m_board[i][18] = 180;
	}

	// set nums and letters 
	{
		// nums 
		for (size_t i = 3, t = 0; i < 19; i += 2, ++t)
			m_board[1][i] = m_board[19][i] = ('1' + t);
		// letters 
		for (size_t i = 3, t = 0; i < 19; i += 2, ++t)
			m_board[i][1] = m_board[i][19] = ('A' + t);
	}
}
// put the pieces from the boardString 
void Chess::setPieces()
{
	for (size_t row = 0, t = 0; row < 8; ++row)
		for (size_t col = 0; col < 8; ++col, ++t)
			m_board[(3 + (row * 2))][(3 + (col * 2))] = ((m_boardString[t] == '#') ? 32 : m_boardString[t]);
}
// print the only the board to screen 
void Chess::show() const 
{
	for (size_t row = 0; row < _SIZE; ++row)
	{
		for (size_t col = 0; col < _SIZE; ++col)
			cout << m_board[row][col];
		cout << endl;
	}
}
// clear screen and print the board and the relevant msg 
void Chess::displayBoard() const
{
	clear();
	show();

	// To make sure not to print the recommended move after finishing the game
	if(gameState == STILL_PLAYING)
		cout << move << endl;

	cout << m_msg<< m_errorMsg;
	
	
}
// print the who is turn before getting input 
void Chess::showAskInput() const 
{
	if (m_turn)
		cout << "Player 1 (White - Capital letters) >> ";
	else
		cout << "Player 2 (Black - Small letters)   >> ";
}
// check if the source and dest are the same 
bool Chess::isSame() const 
{
	return ((m_input[0] == m_input[2]) && (m_input[1] == m_input[3]));
} 
// check if the input is lockations at board
bool Chess::isValid() const
{
	return ((('A' <= m_input[0]) && (m_input[0] <= 'H')) || (('a' <= m_input[0]) && (m_input[0] <= 'h')) &&
		(('1' <= m_input[1]) && (m_input[1] <= '8')) &&
		(('A' <= m_input[2]) && (m_input[2] <= 'H')) || (('a' <= m_input[2]) && (m_input[2] <= 'h')) &&
		(('1' <= m_input[3]) && (m_input[3] <= '8')));
}
	
// check if the input is exit or quit  
bool Chess::isExit() const 
{
	return ((m_input == "exit") || (m_input == "quit") || (m_input == "EXIT") || (m_input == "QUIT"));
}
// execute the movement on board 
void Chess::excute()
{
	int row = (m_input[0] - 'a');
	int col = (m_input[1] - '1');
	char pieceInSource = m_boardString[(row * 8) + col]; 
	m_boardString[(row * 8) + col] = '#'; 

	row = (m_input[2] - 'a');
	col = (m_input[3] - '1');
	m_boardString[(row * 8) + col] = pieceInSource; 

	setPieces(); 
}
// check the response code and switch turn if needed 
void Chess::doTurn()
{
	m_errorMsg = "\n"; 
	switch (m_codeResponse)
	{
	case 11:
	{
		//m_msg = "there is not piece at the source \n";
		m_msg = "";
		throw PieceNotFoundException("No piece at the source location.");
		break;
	}
	case 12:
	{
		m_msg = "";
		//m_msg = "the piece in the source is piece of your opponent \n";
		throw InvalidMoveException("The piece in the source location belongs to the opponent.");
		break;
	}
	case 13:
	{
		m_msg = "";
		//m_msg = "there one of your pieces at the destination \n";
		throw InvalidMoveException("There is already a piece of the same color at the destination.");
		break;
	}
	case 21:
	{
		m_msg = "";
		throw InvalidMoveException("Illegal movement of that piece.");
		//m_msg = "illegal movement of that piece \n";
		break;
	}
	case 31:
	{
		m_msg = "";
		//m_msg = "this movement will cause you checkmate \n";
		throw CheckException("Illegal move: it leaves the king in check.");
		break;
	}
	case 41:
	{
		excute();
		m_turn = !m_turn;
		m_msg = "the last movement was legal and cause check \n";
		break;
	}
	case 42:
	{
		excute();
		m_turn = !m_turn;
		m_msg = "the last movement was legal \n";
		break;
	case 43:
		executeCastling();
		m_turn = !m_turn;
		m_msg = "Castling performed successfully \n";
		break;
	case 44:
		excute();
		switch (gameState) {
		case WHITE_WIN: 
			m_msg = "Checkmate! White wins the game.\n";
			break;
		case BLACK_WIN: 
			m_msg = "Checkmate! Black wins the game.\n";
			break;
		case DRAW: 
			m_msg = "The game is a draw.\n";
			break;
		}
		displayBoard();
		exit(0);
		break;
	case 45:
		//excute();
		excutePromotePawn(pawnChangedTo);
		m_turn = !m_turn;
		m_msg = "Pawn promoted successfully \n";
		break;
	}
	}
}

void Chess::executeCastling() {
	int row = m_input[0] - 'a';
	int col = m_input[1] - '1';

	// Determine the type of castling based on the input
	bool isKingside = (m_input[2] == m_input[0] && m_input[3] == m_input[1] + 2);
	bool isQueenside = (m_input[2] == m_input[0] && m_input[3] == m_input[1] - 2);

	char king = m_boardString[row * 8 + col];
	char rook;

	if (isKingside) {
		// Move the king two squares to the right
		m_boardString[row * 8 + col] = '#';
		m_boardString[row * 8 + (col + 2)] = king;

		// Move the rook next to the king's new position
		rook = m_boardString[row * 8 + 7];
		m_boardString[row * 8 + 7] = '#';
		m_boardString[row * 8 + (col + 1)] = rook;
	}
	else if (isQueenside) {
		// Move the king two squares to the left
		m_boardString[row * 8 + col] = '#';
		m_boardString[row * 8 + (col - 2)] = king;

		// Move the rook next to the king's new position
		rook = m_boardString[row * 8 + 0];
		m_boardString[row * 8 + 0] = '#';
		m_boardString[row * 8 + (col - 1)] = rook;
	}

	// Update the ASCII board representation
	setPieces();
}

// C'tor
Chess::Chess(const string& start)
	: m_boardString(start),m_codeResponse(-1), gameState(STILL_PLAYING)
{
	setFrames();
	setPieces();
}

// get the source and destination 
string Chess::getInput()
{
	static bool isFirst = true;
	if (isFirst)
		isFirst = false;
	else {
		try {
			doTurn();
		}
		catch (const InvalidMoveException& e) {
			m_errorMsg += "Invalid move: ";
			m_errorMsg += e.what();
			m_errorMsg += '\n';
			//std::cerr << "Invalid move: " << e.what() << std::endl;
		}
		catch (const PieceNotFoundException& e) {
			m_errorMsg += "Piece not found: ";
			m_errorMsg += e.what();
			m_errorMsg += '\n';
			//std::cerr << "Piece not found: " << e.what() << std::endl;
		}
		catch (const CheckException& e) {
			m_errorMsg += "Check error: ";
			m_errorMsg += e.what();
			m_errorMsg += '\n';
			//std::cerr << "Check error: " << e.what() << std::endl;
		}
		catch (const std::exception& e) {
			m_errorMsg += "An error occurred: ";
			m_errorMsg += e.what();
			m_errorMsg += '\n';
			//std::cerr << "An error occurred: " << e.what() << std::endl;
		} 
		

		
	}
	displayBoard();
	showAskInput();

	cin >> m_input;
	if (isExit())
		return "exit";
	while (!isValid() || isSame())
	{
		m_msg = "";
		if (!isValid())
			m_errorMsg = "Invalid input !! \n";
		else
			m_errorMsg = "The source and the destination are the same !! \n";
		displayBoard();
		showAskInput();
		cin >> m_input;
		if (isExit())
			return "exit";
	}

	if (m_input != "exit")
	{
		if (('A' <= m_input[0]) && (m_input[0] <= 'H'))
			m_input[0] = (m_input[0] - 'A' + 'a');
		if (('A' <= m_input[2]) && (m_input[2] <= 'H'))
			m_input[2] = (m_input[2] - 'A' + 'a');
	}

	return m_input;
}

void Chess::setCodeResponse(int codeResponse)
{
	if (((11 <= codeResponse) && (codeResponse <= 13)) ||
		((21 == codeResponse) || (codeResponse == 31)) ||
		((41 <= codeResponse) && (codeResponse <= 45)))
		m_codeResponse = codeResponse;
}

void Chess::setGameState(GameState state) {
	gameState = state;
}

void Chess::SetEvaluateMove(Move move)
{
	this->move = move;
}





void Chess::changeBoardString(string newBoardString) {
	this->m_boardString = newBoardString;
	setPieces();
	//excute();
}





void Chess::setpawnChangedTo(char pawnChangedTo) {
	this->pawnChangedTo = pawnChangedTo;
}





//void Chess::checkAndPromotePawn(char pawnChangedTo) {
//	for (size_t col = 8; col < 16; ++col) {
//		// Check for white pawn promotion
//		if (m_boardString[col] == 'p') {
//			m_boardString[col] = '#';
//			m_boardString[col+8] = char(pawnChangedTo);
//		}
//		// Check for black pawn promotion
//		if (m_boardString[40 + col] == 'P') {
//			m_boardString[40 + col] = '#';
//			m_boardString[48 + col] = char(pawnChangedTo);
//		}
//	}
//	std::cout << m_boardString;
//	setPieces();
//}



void Chess::excutePromotePawn(char pawnChangedTo) {
	int row = (m_input[0] - 'a');
	int col = (m_input[1] - '1');
	char pieceInSource = m_boardString[(row * 8) + col];
	m_boardString[(row * 8) + col] = '#';

	row = (m_input[2] - 'a');
	col = (m_input[3] - '1');
	m_boardString[(row * 8) + col] = pawnChangedTo;

	setPieces();
}