/** Class file for the class ClassBoard
 * Author: Leo Huang
 * Student ID: 26886294
 * Date: 11/08/2017
 */

#include "ClassBoard.h"
#include <algorithm> //std::random_shuffle

using namespace std;

/** Empty constructor */
ClassBoard::ClassBoard()
{

}

/** Full constructor */
ClassBoard::ClassBoard(int boardWidth, int boardHeight, int maxBombs)
{
	this->boardWidth = boardWidth;
	this->boardHeight = boardHeight;
	this->maxBombs = maxBombs;
}

/** Deconstructor */
ClassBoard::~ClassBoard()
{

}

/** Method getItem
 * Retrieves the value stored at the coordinates (x, y) on the board
 */
char ClassBoard::getItem(int x, int y)
{
	return board[y * boardWidth + x];
}

/** Method initialiseBoard
 * Generates a board with randomly placed mines
 */
void ClassBoard::initialiseBoard()
{
	vector<int> shuffler;
	for (int i = 0; i < (boardWidth * boardHeight); i++)
	{
		board.push_back('0');
		shuffler.push_back(i);
	}
	random_shuffle(shuffler.begin(), shuffler.end());
	for (int i = 0; i < maxBombs; i++)
	{
		board[shuffler[i]] = 'B';
	}
}

/** Method drawBoard
 * Draws the game board
 */
void ClassBoard::drawBoard()
{
	cout << " ";
	for (int i = 0; i < boardWidth; i++)
	{
		cout << "   " << i;
	}
	cout << " \n";
	for (int i = 0; i < boardWidth; i++)
	{
		cout << "   -";
	}
	cout << endl;
	for (int j = 0; j < boardWidth; j++)
	{
		cout << j << "  |";
		for (int i = 0; i < boardHeight; i++)
		{
			count << " " << board[i][j] << " |";
		}
	}
}

/** Method setBoardWidth
 * Sets the board width variable
 */
void ClassBoard::setBoardWidth(int boardWidth)
{
	this->boardWidth = boardWidth;
}

/** Method getBoardWidth
 * Retrieves the width of the board
 */
int ClassBoard::getBoardWidth()
{
	return boardWidth;
}

/** Method setBoardHeight
 * Sets the board height variable
 */
void ClassBoard::setBoardHeight(int boardHeight)
{
	this->boardHeight = boardHeight;
}

/** Method getBoardHeight
 * retrieves the height of the board
 */
int ClassBoard::getBoardHeight()
{
	return boardHeight;
}

/** Method setMaxBombs
 * Sets the maximum number of bombs for the board
 */
void ClassBoard::setMaxBombs(int maxBombs)
{
	this->maxBombs = maxBombs;
}

/** Method getMaxBombs
 * Retrieves the value of the maximum number of bombs for the board
 */
int ClassBoard::getMaxBombs()
{
	return maxBombs;
}

/** Method setBombsLeft
 * Sets the value of the number of bombs remaining
 */
void ClassBoard::setBombsLeft(int bombsLeft)
{
	this->bombsLeft = bombsLeft;
}

/** Method getBombsLeft
 * Retrieves the number of bombs remaining on the board
 */
int ClassBoard::getbombsLeft()
{
	return bombsLeft;
}

/** Method reduceBombsLeft
 * Reduces the amount of bombs left by 1
 */
int ClassBoard::reduceBombsLeft()
{
	bombsLeft--;
}