#include "TicTacToe.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define KEY_ENTER 13

int main() {

	while (true) {
		TicTacToe board;
		int keyValue = 0;
		bool gameEnd = false;
		cout << "Welcome to Tic Tac Toe! " << endl;
		cout << "Use the arrow keys to select a tile, and Enter to place your move." << endl;

		while (!gameEnd) {
			system("CLS");

			//1. Init players turn.
			cout << board.getCurPlayer() << "'s turn: " << endl;
			board.printBoard();

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
					board.updateTileUI(placeMove);
					break;
				default:
					break;
			}
			if (!board.checkEnd()) {
				board.switchPlayer();
			}
			else {
				gameEnd = true;
				system("CLS");
			}
		}
	
		break;
	}
	return 0;
}