#include "TicTacToe.h"

TicTacToe::TicTacToe() {
	//start on top left tile
	selectedTile = {0 ,0};
	//Build the board
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (i == get<0>(selectedTile) && j == get<1>(selectedTile)) {
				gameBoard[i][j] = '_';
				selectedTileValue = '-';
			}
			else {
				gameBoard[i][j] = '-';
			}
		}
	}
	setCurPlayer("PlayerX");
}

void TicTacToe::printBoard() {
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			cout << gameBoard[row][col] << " ";
		}
		cout << "\n";
	}
}

void TicTacToe::updateTileUI(UICOMMAND cmd) {
	switch (cmd) {
		case(moveLeft):
			//if selected tile is not as far left as you it can be:
			if (get<1>(selectedTile) != 0) {
				gameBoard[get<0>(selectedTile)][get<1>(selectedTile)] = selectedTileValue;	//Replace the '_' with that positions original value
				get<1>(selectedTile) -= 1;													//move the 'x' coordinate one space left
				selectedTileValue = gameBoard[get<0>(selectedTile)][get<1>(selectedTile)];	//store the value of the new selected tile
				gameBoard[get<0>(selectedTile)][get<1>(selectedTile)] = '_';				//replace that tile with a '_' to indicate selection
			}
			break;
		case(moveRight):
			//if selected tile is not as far right as you it can be:
			if (get<1>(selectedTile) != 2) {
				gameBoard[get<0>(selectedTile)][get<1>(selectedTile)] = selectedTileValue;	//Replace the '_' with that positions original value
				get<1>(selectedTile) += 1;													//move the 'x' coordinate one space left
				selectedTileValue = gameBoard[get<0>(selectedTile)][get<1>(selectedTile)];	//store the value of the new selected tile
				gameBoard[get<0>(selectedTile)][get<1>(selectedTile)] = '_';				//replace that tile with a '_' to indicate selection
			}
			break;
		case(moveUp):
			//if selected tile is not as far up as you it can be:
			if (get<0>(selectedTile) != 0) {
				gameBoard[get<0>(selectedTile)][get<1>(selectedTile)] = selectedTileValue;	//Replace the '_' with that positions original value
				get<0>(selectedTile) -= 1;													//move the 'y' coordinate one space up
				selectedTileValue = gameBoard[get<0>(selectedTile)][get<1>(selectedTile)];	//store the value of the new selected tile
				gameBoard[get<0>(selectedTile)][get<1>(selectedTile)] = '_';				//replace that tile with a '_' to indicate selection
			}
			break;
		case(moveDown):
			//if selected tile is not as far down as you it can be:
			if (get<0>(selectedTile) != 2) {
				gameBoard[get<0>(selectedTile)][get<1>(selectedTile)] = selectedTileValue;	//Replace the '_' with that positions original value
				get<0>(selectedTile) += 1;													//move the 'y' coordinate one space down
				selectedTileValue = gameBoard[get<0>(selectedTile)][get<1>(selectedTile)];	//store the value of the new selected tile
				gameBoard[get<0>(selectedTile)][get<1>(selectedTile)] = '_';				//replace that tile with a '_' to indicate selection
			}
			break;
		case(placeMove):
			if (getCurPlayer() == "PlayerX") {
				gameBoard[get<0>(selectedTile)][get<1>(selectedTile)] = 'X';
			}
			else {
				gameBoard[get<0>(selectedTile)][get<1>(selectedTile)] = 'O';
			}
			selectedTile = { 0 ,0 };
			selectedTileValue = gameBoard[get<0>(selectedTile)][get<1>(selectedTile)];
			gameBoard[get<0>(selectedTile)][get<1>(selectedTile)] = '_';
			break;
		default:
			cout << "Unexpected Command, please try again" << endl;
			break;
	}
	printBoard();
}

void TicTacToe::setCurPlayer(string player) {
	curPlayer = player;
}

void TicTacToe::switchPlayer() {
	if (curPlayer == "PlayerX") {
		curPlayer = "PlayerO";
	}
	else {
		curPlayer = "PlayerX";
	}
}

string TicTacToe::getCurPlayer() {
	return curPlayer;
}

bool TicTacToe::checkEnd() {
	return checkTie();
}

bool TicTacToe::checkTie() {
	bool gameTie = true;
	for (int i = 0; i < 3; i++) {
		for (int j = 0; j < 3; j++) {
			if (gameBoard[i][j] == '-') {
				gameTie = false;
				break;
			}
		}
	}
	
	return gameTie;
}