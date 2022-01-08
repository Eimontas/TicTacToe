#pragma once
//Prompt the first user(the 'x' user) to enter their name
//Prompt the second user(the 'o' user) to enter their name
//Prompt the 'x' user to select a grid position where they would like to place an 'x'.
//Prompt the 'o' user to select a grid position where they would like to place an 'o'.
//After each user has a turn, check for any row, column, diagonal that has 4 'x's or 4 'o's.
//If 4 'x's are found in the same col, row, diagonal, declare the 'x' user the winner.
//If 4 'o's are found in the same col, row, diagonal, declare the 'o' user the winner.
//End the game and declare the winner.
//If the grid is filled(each player gets 8 turns) and there is not a row, column, diagonal
//with 4 of the same symbol, the game is tied.Declare a tie game.
#ifndef TICTACTOE_BOARD
#define TICTACTOE_BOARD

#include <iostream>
#include <conio.h>
#include <string>
#include <tuple>

enum UICOMMAND { moveLeft, moveRight, moveUp, moveDown, placeMove };
enum CURSTATE {xWin, oWin, draw, inProgress};
using namespace std;
class TicTacToe {
	char gameBoard[3][3];
	string curPlayer;
	char selectedTileValue;
	tuple<int, int> selectedTile;
	CURSTATE state;

	CURSTATE checkDiagonals(char player);
	CURSTATE checkColumns(char player);
	CURSTATE checkRows(char player);

	public:
		TicTacToe();
		void printBoard();
		void updateTileUI(UICOMMAND cmd);
		void setCurPlayer(string player);
		void switchPlayer();
		string getCurPlayer();
		CURSTATE checkEnd(int row, int col, string player);
		CURSTATE checkWin(int row, int col, string player);
		bool checkTie();
		bool checkValidMove();
		void setCurState(CURSTATE newState);
		CURSTATE getCurState();

};

#endif
