#include "TicTacToe.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13

int main() {

	while (true) {
		//0.1. Initialise key variables and print init statement.
		TicTacToe board;
		int keyValue = 0;
		char playAgainChoice = 'x';
		bool prevMoveInvalid = false;
		
		while (board.getCurState() == inProgress) {
			cout << "Welcome to Tic Tac Toe! " << endl;
			cout << "Use the arrow keys to select a tile, and Enter to place your move." << endl;

			if(prevMoveInvalid){ cout << "Invalid Move! Try Again: " << endl; }
			//1. Init players turn, and refresh the board state.
			cout << board.getCurPlayer() << "'s turn: " << endl;
			board.printBoard();

			bool validMove = board.checkValidMove();
			//2. Listen for arrow inputs and update UI to show selected tile.
			switch ((keyValue = _getch())) {
				case(KEY_LEFT):
					board.updateTileUI(moveLeft);
					break;
				case(KEY_RIGHT):
					board.updateTileUI(moveRight);
					break;
				case(KEY_UP):
					board.updateTileUI(moveUp);
					break;
				case(KEY_DOWN):
					board.updateTileUI(moveDown);
					break;
				case(KEY_ENTER):
					if (validMove) {
						board.updateTileUI(placeMove);
						if (prevMoveInvalid) { prevMoveInvalid = false; }
					}
					else {
						prevMoveInvalid = true;
					}
					
					break;
				default:
					break;
			}
			CURSTATE state = board.getCurState();
			if (state == inProgress && validMove) {
				board.switchPlayer();
			}
			else if(state != inProgress){ 
				switch (state) {
				case(draw):
					cout << "It's a draw!" << endl;
					break;
				case(xWin):
					cout << "Player X is the Winner!!!" << endl;
					break;
				case(oWin):
					cout << "Player O is the Winner!!!" << endl;
					break;
				default:
					break;
				}
				cout << "Would you like to play again? (Y/N) \n";
				do {
					cin >> playAgainChoice;
				} while (
					playAgainChoice != 'Y' && playAgainChoice != 'N' &&
					playAgainChoice != 'y' && playAgainChoice != 'n'
					);
			}
			system("CLS");

		}
		if (playAgainChoice == 'N' || playAgainChoice == 'n') {
			break;
		}
	}
	return 0;
}