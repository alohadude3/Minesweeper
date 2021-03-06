/** Header file for the class ClassBoard
 * Author: Leo Huang
 * Student ID: 26886294
 * Date: 11/08/2017
 */

 //inclusion guards
#ifndef CLASSBOARD_H
#define CLASSBOARD_H

//#pragma once //could use this in place of inclusion guards

#include <vector>

using namespace std;

/** Class declaration */
class ClassBoard
{
	public:
		ClassBoard();
		ClassBoard(int boardHeight, int boardWidth, int maxBombs);
		~ClassBoard();
		char getChar(int x, int y);
		int getValue(int x, int y);
		void makeBoard();
		void initialiseBoard(int x, int y);
		void drawBoard();
		int revealGrid(int x, int y);
		int markGrid(int x, int y);
		int unmarkGrid(int x, int y);
		int save(string key, string hashkey);
		int load(string key, string hashkey);
		string encrypt(string theString, string key);
		void setBoardWidth(int boardWidth);
		int getBoardWidth();
		void setBoardHeight(int boardHeight);
		int getBoardHeight();
		void setMaxBombs(int maxBombs);
		int getMaxBombs();
		void setBombsLeft(int bombsLeft);
		int getBombsLeft();
		void setNonBombsLeft(int nonBombsLeft);
		int getNonBombsLeft();
	private:
		int boardWidth;
		int boardHeight;
		int maxBombs;
		int bombsLeft;
		int nonBombsLeft;
		vector<int> board;
};

#endif