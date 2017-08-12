/** Main file for Minesweeper
 * Author: Leo Huang
 * Student ID: 26886294
 * Date: 10/8/2017
 */

#include <iostream>

using namespace std;

/** Main function */
int main()
{
	//initialise variables
	int boardWidth = 10, boardHeight = 10, maxBombs = 20, bombsLeft = maxBombs, xCoord, yCoord;
	char command;
	bool alive = true, validCommand = false;
	ClassBoard theBoard(boardWidth, boardHeight, maxBombs);
	theBoard.initialiseBoard();
	//main game loop
	while (bombsLeft > 0 && alive)
	{
		system("cls"); //clear the terminal so the board can be redrawn
		cout << "Welcome to Minesweeper\n\n";
		cout << "There are " << theBoard.getbombsLeft() << " bombs remaining\n\n";
		theBoard.drawBoard();
		while (!validCommand) //get the action
		{
			cout << "What would you like to do? (r)eaveal or (m)ark?\n";
			cin >> command;
			cin.clear();
			cin.sync();
			command = tolower(command);
			switch (command)
			{
				case 'r':
					validCommand = true;
					break;
				case 'm':
					validCommand = true;
					break;
			}
		}
		validCommand = false;
		while (!validCommand) //get the x-coordinate
		{
			cout << "Enter the x-coordinate: ";
			cin >> xCoord;
			cin.clear();
			cin.sync();
			if (xCoord >= 0 && xCoord < boardWidth)
			{
				validCommand = true;
			}
		}
		validCommand = false;
		while (!validCommand) //get the y-coordinate
		{
			cout << "Enter the y-coordinate: ";
			cin >> yCoord;
			cin.clear();
			cin.sync();
			if (yCoord >= 0 && yCoord < boardHeight)
			{
				validCommand = true;
			}
		}
	}
	system("pause");
	return 0;
}