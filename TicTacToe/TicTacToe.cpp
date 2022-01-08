#include "TicTacToe.h"

TicTacToe::TicTacToe() {
	//start on top left tile
	selectedTile = {0 ,0};
	state = inProgress;
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
			state = checkEnd(get<0>(selectedTile), get<1>(selectedTile), getCurPlayer());
			if(state == inProgress){ gameBoard[get<0>(selectedTile)][get<1>(selectedTile)] = '_'; }
			break;
		default:
			cout << "Unexpected Command, please try again" << endl;
			break;
	}
	system("CLS");
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

CURSTATE TicTacToe::checkEnd(int row, int col, string player) {
	if(!checkTie()) {
		CURSTATE state = checkWin(row, col, player);
		return state;
	}
	else{
		return draw;
	}
}

CURSTATE TicTacToe::checkWin(int row, int col, string player) {
	char curPlayer = player.back();
	CURSTATE diags = checkDiagonals(curPlayer);
	if (diags == inProgress) {
		CURSTATE rows = checkRows(curPlayer);
		if (rows == inProgress) {
			CURSTATE cols = checkColumns(curPlayer);
			if (cols == inProgress) {
				return inProgress;
			}
			else {
				return cols;
			}
		}
		else {
			return rows;
		}
	}
	else {
		return diags;
	}
}

bool TicTacToe::checkValidMove() {
	if (selectedTileValue == '-') {
		return true;
	}
	else {
		return false;
	}
}

CURSTATE TicTacToe::checkColumns(char player) {
	for (int i = 0; i < 3; i++) {
		bool colFull = true;
		for (int j = 0; j < 3; j++) {
			if (gameBoard[j][i] != player) {
				colFull = false;
			}
		}
		if (colFull) {
			if (player == 'X') { return xWin; }
			else { return oWin; }
		}
	}
	return inProgress;
}

CURSTATE TicTacToe::checkRows(char player) {
	for (int i = 0; i < 3; i++) {
		bool rowFull = true;
		for (int j = 0; j < 3; j++) {
			if (gameBoard[i][j] != player) {
				rowFull = false;
			}
		}
		if (rowFull) {
			if (player == 'X') { return xWin; }
			else { return oWin; }
		}
	}
	return inProgress;
}

CURSTATE TicTacToe::checkDiagonals(char player) {
	//If the middle tile is not held by the player that just moved, then diagonals will always be false.
	if (player == gameBoard[1][1]) {
		if (player == gameBoard[0][0] && player == gameBoard[2][2]) {
			if (player == 'X') { return xWin; }
			else { return oWin; }
		}
		else if (player == gameBoard[0][2] && player == gameBoard[2][0]) {
			if (player == 'X') { return xWin; }
			else { return oWin; }
		}
		else {
			return inProgress;
		}
	}
	else {
		return inProgress;
	}
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
	if (gameTie && selectedTileValue == '-') {
		gameTie = false;
	}
	
	return gameTie;
}

void TicTacToe::setCurState(CURSTATE newState) {
	state = newState;
}

CURSTATE TicTacToe::getCurState() {
	return state;
}