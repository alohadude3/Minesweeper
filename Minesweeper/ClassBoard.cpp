/** Class file for the class ClassBoard
 * Author: Leo Huang
 * Student ID: 26886294
 * Date: 11/08/2017
 */

#include "ClassBoard.h"
#include <algorithm> //std::random_shuffle
#include <iostream> //std::cin and std::cout;
#include <ctime> //srand for seeding

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
	this->bombsLeft = maxBombs;
	this->nonBombsLeft = (boardWidth * boardHeight) - maxBombs;
	this->markingsCount = 0;
}

/** Deconstructor */
ClassBoard::~ClassBoard()
{

}

/** Method getValue
 * Retrieves the value stored at the coordinates (x, y) on the board
 */
int ClassBoard::getValue(int x, int y)
{
	return board[y * boardWidth + x];
}

/** Method getChar
 * Retrieves the character stored at the coordinates (x, y) on the board
 */
char ClassBoard::getChar(int x, int y)
{
	int theValue = getValue(x, y);
	char theChar = ' '; //default value for concealed grids
	if (theValue >= 20) //marked values range: [20, 29]
	{
		theChar = 'X';
	}
	else if (theValue < 9) //revealed values range: [0, 9]
	{
		theChar = theValue + 48;
	}
	else if (theValue == 9) //revealed bomb
	{
		theChar = 'B';
	}
	return theChar;
}

/** Method initialiseBoard
 * Generates a board with randomly placed mines
 * The board will contain integers representing the number of adjacent mines to that square (0 - 8)
 * The number 9 will be used to represent a bomb
 * The concealed values however will be the true values added to 10
 * Meaning a concealed bomb will have the integer value 19
 * And when revealed, the value will be 10
 * The marked values will be the true values added to 20 in this case
 * To simply retrieve the true value just apply modulo 10 to the stored value
 */
void ClassBoard::initialiseBoard()
{
	vector<int> vectorBombs;
	/** Add 0 values to the board */
	for (int i = 0; i < (boardWidth * boardHeight); i++) //simulate a 2 dimensional array with a 1 dimensional vector
	{
		board.push_back(10); //add default value 10 (concealed 0)
		vectorBombs.push_back(i);
	}
	srand(time(NULL));
	random_shuffle(vectorBombs.begin(), vectorBombs.end()); //shuffle the list of possible positions on the board
	for (int i = 0; i < maxBombs; i++) //then set the first few positions up to maximum amount of bombs allowed to contain bombs
	{
		board[vectorBombs[i]] = 19; //set up the bombs (19 = concealed bomb)
		/** Condition check to  make sure the adjacent grids are ok before incrementing their values
		 * Conditions are:
		 * Must be within the bounds of the board (Boundary check)
		 * Must not be a bomb
		*/
		int tempIndex = vectorBombs[i] - boardWidth - 1; //top left adjacent grid
		if ((tempIndex >= 0) && board[tempIndex] != 19)
		{
			board[tempIndex] += 1;
		}
		tempIndex = vectorBombs[i] - boardWidth; //top adjacent grid
		if ((tempIndex >= 0) && board[tempIndex] != 19)
		{
			board[tempIndex] += 1;
		}
		tempIndex = vectorBombs[i] - boardWidth + 1; //top right adjacent grid
		if ((tempIndex >= 0) && board[tempIndex] != 19)
		{
			board[tempIndex] += 1;
		}
		tempIndex = vectorBombs[i] - 1; //left adjacent grid
		if ((tempIndex >= 0) && board[tempIndex] != 19)
		{
			board[tempIndex] += 1;
		}
		tempIndex = vectorBombs[i] + 1; //right adjacent grid
		if ((tempIndex < (boardWidth * boardHeight)) && board[tempIndex] != 19)
		{
			board[tempIndex] += 1;
		}
		tempIndex = vectorBombs[i] + boardWidth - 1; //bottom left adjacent grid
		if ((tempIndex < (boardWidth * boardHeight)) && board[tempIndex] != 19)
		{
			board[tempIndex] += 1;
		}
		tempIndex = vectorBombs[i] + boardWidth; //bottom adjacent grid
		if ((tempIndex < (boardWidth * boardHeight)) && board[tempIndex] != 19)
		{
			board[tempIndex] += 1;
		}
		tempIndex = vectorBombs[i] + boardWidth + 1; //bottom right adjacent grid
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
	cout << "  ";
	for (int i = 0; i < boardWidth; i++)
	{
		cout << "   " << i;
	}
	cout << " \n  ";
	for (int i = 0; i < boardWidth; i++)
	{
		cout << "   -";
	}
	cout << endl;
	for (int j = 0; j < boardHeight; j++)
	{
		cout << j << "  |";
		for (int i = 0; i < boardWidth; i++)
		{
			cout << " " << getChar(i, j) << " |";
		}
		cout << "\n  ";
		for (int i = 0; i < boardWidth; i++)
		{
			cout << "   -";
		}
		cout << endl;
	}
}

/** Method revealGrid
 * Reveals the specified grid if it is concealed
 * Returns 0 on successful execution, 1 otherwise
 */
int ClassBoard::revealGrid(int x, int y)
{
	if (getChar(x, y) == ' ')
	{
		board[y * boardWidth + x] = getValue(x, y) % 10; //sets the true value on reveal
		if (getValue(x, y) % 10 != 9) //update nonBombsLeft
		{
			nonBombsLeft--;
		}
		if (getValue(x, y) == 0) //recursively reveal adjacent grids if current one is 0
		{
			/** Boundary checks */
			int tempIndex = y * boardWidth + x - boardWidth - 1; //top left adjacent grid
			if (tempIndex >= 0)
			{
				revealGrid(x-1, y-1);
			}
			tempIndex = y * boardWidth + x - boardWidth; //top adjacent grid
			if (tempIndex >= 0)
			{
				revealGrid(x, y-1);
			}
			tempIndex = y * boardWidth + x - boardWidth + 1; //top right adjacent grid
			if (tempIndex >= 0)
			{
				revealGrid(x+1, y-1);
			}
			tempIndex = y * boardWidth + x - 1; //left adjacent grid
			if (tempIndex >= 0)
			{
				revealGrid(x-1, y);
			}
			tempIndex = y * boardWidth + x + 1; //right adjacent grid
			if (tempIndex < (boardWidth * boardHeight))
			{
				revealGrid(x+1, y);
			}
			tempIndex = y * boardWidth + x + boardWidth - 1; //bottom left adjacent grid
			if (tempIndex < (boardWidth * boardHeight))
			{
				revealGrid(x-1, y+1);
			}
			tempIndex = y * boardWidth + x + boardWidth; //bottom adjacent grid
			if (tempIndex < (boardWidth * boardHeight))
			{
				revealGrid(x, y+1);
			}
			tempIndex = y * boardWidth + x + boardWidth + 1; //bottom right adjacent grid
			if (tempIndex < (boardWidth * boardHeight))
			{
				revealGrid(x+1, y+1);
			}
		}
		return 0;
	}
	return 1;
}

/** Method markGrid
 * Marks the specified grid if it is concealed
 * Returns 0 on successful execution, 1 otherwise
 */
int ClassBoard::markGrid(int x, int y)
{
	if (getChar(x, y) == ' ')
	{
		board[x + (y * boardWidth)] = getValue(x, y) % 10 + 20; //sets the marked value
		if (getValue(x, y) % 10 == 9) //update bombsLeft
		{
			bombsLeft--;
		}
		markingsCount++;
		return 0;
	}
	return 1;
}

/** Method unmarkGrid
 * Unmarks the specified grid if it is marked
 * Returns 0 on successful execution, 1 otherwise
 */
int ClassBoard::unmarkGrid(int x, int y)
{
	if (getChar(x, y) == 'X')
	{
		board[x + (y * boardWidth)] = getValue(x, y) % 10 + 10; //sets the concealed value
		if (getValue(x, y) % 10 == 9) //update bombsLeft
		{
			bombsLeft++;
		}
		markingsCount--;
		return 0;
	}
	return 1;
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

/** Method getBombsLeft
 * Retrieves the number of bombs remaining on the board
 */
int ClassBoard::getBombsLeft()
{
	return bombsLeft;
}

/** Method getNonBombsLeft
 * Retrieves the number of non bombs remaining on the board
 */
int ClassBoard::getNonBombsLeft()
{
	return nonBombsLeft;
}

/** Method getMarkingsCount
 * Retrieves the number of grids that have been marked
 */
int ClassBoard::getMarkingsCount()
{
	return markingsCount;
}