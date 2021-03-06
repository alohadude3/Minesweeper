/** Class file for the class ClassBoard
 * Author: Leo Huang
 * Student ID: 26886294
 * Date: 11/08/2017
 */

#include "ClassBoard.h"
#include <algorithm> //std::random_shuffle
#include <iostream> //std::cin and std::cout;
#include <ctime> //srand for seeding
#include <fstream> //ifstream and ofstream
#include <sstream> //stringstream
#include <vector>

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
	this->nonBombsLeft = boardWidth * boardHeight - maxBombs;
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

/** Method makeBoard
 * Creates the board of the right size with blank values
 */
void ClassBoard::makeBoard()
{
	for (int i = 0; i < (boardWidth * boardHeight); i++)
	{
		board.push_back(10);
	}
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
void ClassBoard::initialiseBoard(int x, int y)
{
	vector<int> vectorBombs;
	/** Add 0 values to the board */
	for (int i = 0; i < (boardWidth * boardHeight); i++) //simulate a 2 dimensional array with a 1 dimensional vector
	{
		vectorBombs.push_back(i);
	}
	srand(time(NULL));
	random_shuffle(vectorBombs.begin(), vectorBombs.end()); //shuffle the list of possible positions on the board
	int i = 0;
	int bombCount = 0;
	while (bombCount < maxBombs) //then set the first few positions up to maximum amount of bombs allowed to contain bombs
	{
		if (vectorBombs[i] != y * boardWidth + x) //if the bomb doesn't go to the first cell
		{
			board[vectorBombs[i]] = 19; //set up the bombs (19 = concealed bomb)
			bombCount++;
			/** Condition check to  make sure the adjacent grids are ok before incrementing their values
			 * Conditions are:
			 * Must be within the bounds of the board (Boundary check)
			 * Must not be a bomb
			*/
			int tempIndex = vectorBombs[i] - boardWidth - 1; //top left adjacent grid
			if (tempIndex >= 0 && vectorBombs[i] % boardWidth > tempIndex % boardWidth && board[tempIndex] != 19)
			{
				board[tempIndex] += 1;
			}
			tempIndex = vectorBombs[i] - boardWidth; //top adjacent grid
			if ((tempIndex >= 0) && board[tempIndex] != 19)
			{
				board[tempIndex] += 1;
			}
			tempIndex = vectorBombs[i] - boardWidth + 1; //top right adjacent grid
			if ((tempIndex >= 0) && vectorBombs[i] % boardWidth < tempIndex % boardWidth && board[tempIndex] != 19)
			{
				board[tempIndex] += 1;
			}
			tempIndex = vectorBombs[i] - 1; //left adjacent grid
			if ((tempIndex >= 0) && vectorBombs[i] % boardWidth > tempIndex % boardWidth && board[tempIndex] != 19)
			{
				board[tempIndex] += 1;
			}
			tempIndex = vectorBombs[i] + 1; //right adjacent grid
			if ((tempIndex < (boardWidth * boardHeight)) && vectorBombs[i] % boardWidth < tempIndex % boardWidth && board[tempIndex] != 19)
			{
				board[tempIndex] += 1;
			}
			tempIndex = vectorBombs[i] + boardWidth - 1; //bottom left adjacent grid
			if ((tempIndex < (boardWidth * boardHeight)) && vectorBombs[i] % boardWidth > tempIndex % boardWidth && board[tempIndex] != 19)
			{
				board[tempIndex] += 1;
			}
			tempIndex = vectorBombs[i] + boardWidth; //bottom adjacent grid
			if ((tempIndex < (boardWidth * boardHeight)) && board[tempIndex] != 19)
			{
				board[tempIndex] += 1;
			}
			tempIndex = vectorBombs[i] + boardWidth + 1; //bottom right adjacent grid
			if ((tempIndex < (boardWidth * boardHeight)) && vectorBombs[i] % boardWidth < tempIndex % boardWidth && board[tempIndex] != 19)
			{
				board[tempIndex] += 1;
			}
		}
		i++;
	}
}

/** Method drawBoard
 * Draws the game board
 */
void ClassBoard::drawBoard()
{
	system("cls"); //clear the terminal so the board can be redrawn
	cout << "Welcome to Minesweeper\n\n";
	cout << "There are " << getBombsLeft() << " bombs remaining\n\n";
	cout << "   ||";
	for (int i = 0; i < boardWidth; i++)
	{
		char iChar = i + 65;
		cout << " " << iChar << " |";
	}
	cout << "\n=====";
	for (int i = 0; i < boardWidth; i++)
	{
		cout << "====";
	}
	cout << endl;
	for (int j = 0; j < boardHeight; j++)
	{
		if (j < 10)
		{
			cout << " " << j << " ||";
		}
		else
		{
			cout << j << " ||";
		}
		for (int i = 0; i < boardWidth; i++)
		{
			cout << " " << getChar(i, j) << " |";
		}
		cout << "\n-----";
		for (int i = 0; i < boardWidth; i++)
		{
			cout << "----";
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
			int tempOriginalIndex = y * boardWidth + x;
			int tempIndex = tempOriginalIndex - boardWidth - 1; //top left adjacent grid
			if (tempIndex >= 0 && tempOriginalIndex % boardWidth > tempIndex % boardWidth)
			{
				revealGrid(x-1, y-1);
			}
			tempIndex = tempOriginalIndex - boardWidth; //top adjacent grid
			if (tempIndex >= 0)
			{
				revealGrid(x, y-1);
			}
			tempIndex = tempOriginalIndex - boardWidth + 1; //top right adjacent grid
			if (tempIndex >= 0 && tempOriginalIndex % boardWidth < tempIndex % boardWidth)
			{
				revealGrid(x+1, y-1);
			}
			tempIndex = tempOriginalIndex - 1; //left adjacent grid
			if (tempIndex >= 0 && tempOriginalIndex % boardWidth > tempIndex % boardWidth)
			{
				revealGrid(x-1, y);
			}
			tempIndex = tempOriginalIndex + 1; //right adjacent grid
			if (tempIndex < (boardWidth * boardHeight) && tempOriginalIndex % boardWidth < tempIndex % boardWidth)
			{
				revealGrid(x+1, y);
			}
			tempIndex = tempOriginalIndex + boardWidth - 1; //bottom left adjacent grid
			if (tempIndex < (boardWidth * boardHeight) && tempOriginalIndex % boardWidth > tempIndex % boardWidth)
			{
				revealGrid(x-1, y+1);
			}
			tempIndex = tempOriginalIndex + boardWidth; //bottom adjacent grid
			if (tempIndex < (boardWidth * boardHeight))
			{
				revealGrid(x, y+1);
			}
			tempIndex = tempOriginalIndex + boardWidth + 1; //bottom right adjacent grid
			if (tempIndex < (boardWidth * boardHeight) && tempOriginalIndex % boardWidth < tempIndex % boardWidth)
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
		bombsLeft--;
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
		bombsLeft++;
		return 0;
	}
	return 1;
}

/** Method save
 * Saves the game state to the file .save
 * Returns 0 if successful, 1 otherwise
 */
int ClassBoard::save(string key, string hashkey)
{
	ofstream theFile;
	theFile.open("data.save");
	if (theFile.good())
	{
		stringstream outputstream;
		outputstream << boardWidth << ' ';
		outputstream << boardHeight << ' ';
		outputstream << maxBombs << ' ';
		outputstream << bombsLeft << ' ';
		outputstream << nonBombsLeft << ' ';
		for (int i = 0; i < boardWidth * boardHeight; i++)
		{
			outputstream << board[i] << ' ';
		}
		string output = outputstream.str();
		output = encrypt(output, hashkey); //encrypt the data as a hash
		outputstream << endl << output; //then append that after the actual data as the digital signature to a new line
		output = outputstream.str();
		output = encrypt(output, key); //then finally encrypt the whole thing using a different key
		theFile << output;
		theFile.close();
		return 0;
	}
	return 1;
}

/** Method load
 * Loads the game state from the file .save
 * Returns 0 if successful, 1 if the file cannot be accessed, 2 if the save file is corrupted
 */
int ClassBoard::load(string key, string hashkey)
{
	ifstream theFile;
	theFile.open("data.save");
	if (theFile.good())
	{
		string input((istreambuf_iterator<char>(theFile)), istreambuf_iterator<char>());
		input = encrypt(input, key);
		stringstream inputstream(input);
		string data, hashdigest;
		getline(inputstream, data);
		getline(inputstream, hashdigest);
		if (hashdigest.compare(encrypt(data, hashkey)) == 0)
		{
			stringstream datastream(data);
			datastream >> boardWidth;
			datastream >> boardHeight;
			datastream >> maxBombs;
			datastream >> bombsLeft;
			datastream >> nonBombsLeft;
			for (int i = 0; i < boardWidth * boardHeight; i++)
			{
				int value;
				datastream >> value;
				board.push_back(value);
			}
			return 0;
		}
		else
		{
			return 2;
		}
	}
	return 1;
}

/** Method encrypt
 * Performs XOR on the parameter string stream
 * Returns a string of the result of the XOR
 */
string ClassBoard::encrypt(string theString, string key)
{
	for (int i = 0; i < theString.size(); i++)
	{
		theString[i] ^= key[i % key.size()];
	}
	return theString;
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
 * Sets the number number of bombs left for the board
 */
void ClassBoard::setBombsLeft(int bombsLeft)
{
	this->bombsLeft = bombsLeft;
}

/** Method getBombsLeft
 * Retrieves the number of bombs remaining on the board
 */
int ClassBoard::getBombsLeft()
{
	return bombsLeft;
}

/** Method setNonBombsLeft
 * Sets the number of non-bombs for the board
 */
void ClassBoard::setNonBombsLeft(int nonBombsLeft)
{
	this->nonBombsLeft = nonBombsLeft;
}

/** Method getNonBombsLeft
 * Retrieves the number of non bombs remaining on the board
 */
int ClassBoard::getNonBombsLeft()
{
	return nonBombsLeft;
}