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
	int theValue = board[y * boardWidth + x];
	char theChar = " "; //default value for concealed grids
	if (theValue >= 20) //marked values range: [20, 29]
	{
		theChar = "X";
	}
	else if (theValue < 9) //revealed values range: [0, 9]
	{
		theChar = theValue;
	}
	else if (theValue = 9) //revealed bomb
	{
		theChar = "B";
	}
	return temp;
}

/** Method initialiseBoard
 * Generates a board with randomly placed mines
 * The board will contain integers representing the number of adjacent mines to that square (0 - 8)
 * The number 9 will be used to represent a bomb
 * The concealed values however will be the true values added to 10
 * Meaning a concealed bomb will have the integer value 19
 * And when revealed, the value will be 10
 * The marked values will be the true values added to 20 in this case
 */
void ClassBoard::initialiseBoard()
{
	vector<int> shuffler;
	/** Add 0 values to the board */
	for (int i = 0; i < (boardWidth * boardHeight); i++) //simulate a 2 dimensional array with a 1 dimensional vector
	{
		board.push_back(10); //add default value 10 (concealed 0)
		shuffler.push_back(i);
	}
	random_shuffle(shuffler.begin(), shuffler.end()); //shuffle the list of possible positions on the board
	for (int i = 0; i < maxBombs; i++) //then set the first few positions up to maximum amount of bombs allowed to contain bombs
	{
		board[shuffler[i]] = 19; //set up the bombs (19 = concealed bomb)
		/** Condition check to  make sure the adjacent grids are ok before incrementing their values
		 * Conditions are:
		 * Must be within the bounds of the board (Boundary check)
		 * Must not be a bomb
		*/
		int tempIndex = shuffler[i] - boardWidth - 1; //top left adjacent grid
		if ((tempIndex >= 0) && board[tempIndex] != 19)
		{
			board[tempIndex] += 1;
		}
		tempIndex = shuffler[i] - boardWidth; //top adjacent grid
		if ((tempIndex >= 0) && board[tempIndex] != 19)
		{
			board[tempIndex] += 1;
		}
		tempIndex = shuffler[i] - boardWidth + 1; //top right adjacent grid
		if ((tempIndex >= 0) && board[tempIndex] != 19)
		{
			board[tempIndex] += 1;
		}
		tempIndex = shuffle[i] - 1; //left adjacent grid
		if ((tempIndex >= 0) && board[tempIndex] != 19)
		{
			board[tempIndex] += 1;
		}
		tempIndex = shuffle[i] + 1; //right adjacent grid
		if ((tempIndex < (boardWidth * boardHeight)) && board[tempIndex] != 19)
		{
			board[tempIndex] += 1;
		}
		tempIndex = shuffle[i] + boardWidth - 1; //bottom left adjacent grid
		if ((tempIndex < (boardWidth * boardHeight)) && board[tempIndex] != 19)
		{
			board[tempIndex] += 1;
		}
		tempIndex = shuffle[i] + boardWidth; //bottom adjacent grid
		if ((tempIndex < (boardWidth * boardHeight)) && board[tempIndex] != 19)
		{
			board[tempIndex] += 1;
		}
		tempIndex = shuffle[i] + boardWidth + 1; //bottom right adjacent grid
		if ((tempIndex < (boardWidth * boardHeight)) && board[tempIndex] != 19)
		{
			board[tempIndex] += 1;
		}
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
		cout << endl;
		for (int i = 0; i < boardWidth; i++)
		{
			cout << "   -";
		}
		cout << endl;
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