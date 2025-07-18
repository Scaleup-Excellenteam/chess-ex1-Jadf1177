// Chess 
#include "Chess.h"
#include <sstream>
#include "Board.h"
int main()
{
	string board = "RNBQKBNRPPPPPPPP################################pppppppprnbqkbnr";
	//string board = "R###K##R####PPPPb###############################ppppppppr###k##r";// to check castling
	//string board = "RNBQK###PPPPPPPP##################################P##P######kbnr";// to check pawn promotion
	//string board = "RNBQK#############################################P##P######kbnr";// to check pawn promotion

	Chess a(board);

    Board myBoard(board);
	char myColor = 'W';

	int depth;
	std::cout << "Enter the depth for move evaluation (up to 2): ";
	std::cin >> depth;

	if (depth < 1 || depth > 3) {
		std::cerr << "Invalid depth. Setting depth to 2." << std::endl;
		depth = 2;
	}

	printf("\n");
	int codeResponse = 0;


	int threadCounts[] = {  2, 4, 8 };

	for (int threadCount : threadCounts) {
		std::cout << "Running with " << threadCount << " threads." << std::endl;

		auto start = std::chrono::high_resolution_clock::now();

		
		a.SetEvaluateMove(myBoard.getBestMove(myColor, depth, threadCount));

		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> elapsed = end - start;
		std::cout << "Time taken: " << elapsed.count() << " seconds." << std::endl;
		printf("\n");
	}

	int threadsNum;
	std::cout << "Enter the Threads number (0 , 2 , 4 , 8): ";
	std::cin >> threadsNum;

	if (threadsNum != 2 && threadsNum != 4 && threadsNum != 8 && threadsNum <= 0) {
		std::cerr << "Invalid Threads number. Setting Threads number to 1." << std::endl;
		threadsNum = 1;
	}

	a.SetEvaluateMove(myBoard.getBestMove(myColor, depth, threadsNum));

	string res = a.getInput();

	while (res != "exit")
	{

		/* 
		codeResponse value : 
		Illegal movements : 
		11 - there is not piece at the source  
		12 - the piece in the source is piece of your opponent
		13 - there one of your pieces at the destination 
		21 - illegal movement of that piece 
		31 - this movement will cause you checkmate

		legal movements : 
		41 - the last movement was legal and cause check 
		42 - the last movement was legal, next turn 
		43 - castling 
		44 - chess
		45- pawn promotion
		*/

		{ // put your code here instead that code

			// Smart move to checkmate:
			// senario01- black wins: b6c6 g5e5 b7d7 h4d8 
			// senario02- white wins: b5d5 g5e5 a6d3 h2f3 a4c6 g4f4 c6g6 
			// senario03- white wins: b5d5 g5e5 a4e8 h5g5 e8e5
			/*
			NOTE: During these smart moves, observe the recommended moves for the winning player.
			You'll notice that they match the moves I've written.
			This is because the depth 2 evaluation accurately identifies the best moves.

			For example, in scenario 01, the black player is recommended to move from 
			g5 to e5 (which brings them closer to winning), and then from h4 to d8 (to achieve checkmate).
			*/

            std::stringstream stringNumber1,stringNumber2;
            stringNumber1 << res[1];
            stringNumber2 << res[3];

            int currentColumn,
            goalColumn,
            currentRow = res[0] - 'a',
            goalRow = res[2] - 'a';

            stringNumber1 >> currentColumn;
            stringNumber2 >> goalColumn;
            currentColumn--;
            goalColumn--;

            codeResponse = myBoard.checkMove(currentRow,currentColumn ,goalRow,goalColumn, myColor);
				
			if (codeResponse == 45)
				a.setpawnChangedTo(myBoard.getPawnPromotionValue());

			if (codeResponse >= 41 && codeResponse <= 45)
				myColor = (myColor == 'W' ? 'B' : 'W');
			
			if (myBoard.getGameState() == Board::GameState::WHITE_WIN) { 
				a.setGameState(Chess::WHITE_WIN);
			}else if (myBoard.getGameState() == Board::GameState::BLACK_WIN) {
				a.setGameState(Chess::BLACK_WIN);
			}else if (myBoard.getGameState() == Board::GameState::DRAW) {
				a.setGameState(Chess::DRAW); 
			} 
        }

			a.setCodeResponse(codeResponse);

			a.SetEvaluateMove(myBoard.getBestMove(myColor, depth));

			res = a.getInput();
	}

	cout << endl << "Exiting " << endl; 
	return 0;
}