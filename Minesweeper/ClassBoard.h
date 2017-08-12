/** Header file for the class ClassBoard
 * Author: Leo Huang
 * Student ID: 26886294
 * Date: 11/08/2017
 */

#ifndef CLASSBOARD_H
#define CLASSBOARD_H

#include <vector>

using namespace std;

/** Class declaration */
class ClassBoard
{
	public:
		ClassBoard();
		ClassBoard(int boardHeight, int boardWidth, int maxBombs);
		~ClassBoard();
		char getItem(int x, int y);
		void initialiseBoard();
		void drawBoard();
		void setBoardWidth(int boardWidth);
		int getBoardWidth();
		void setBoardHeight(int boardHeight);
		int getBoardHeight();
		void setMaxBombs(int maxBombs);
		int getMaxBombs();
		void setBombsLeft(int bombsLeft);
		int getbombsLeft();
		void reduceBombsLeft();
	private:
		int boardWidth;
		int boardHeight;
		int maxBombs;
		int bombsLeft;
		vector<int> board;
};

#endif