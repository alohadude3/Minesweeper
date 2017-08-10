/*
author: Leo Huang
student id: 26886294
date: 10/8/2017
*/

#include <iostream>
#include <string>

using namespace std;

//main function
int main()
{
	//initialise variables
	const int boardWidth = 10, boardHeight = 10, totalBombs = 20;
	int bombsLeft = totalBombs;
	bool alive = true;
	char board[boardWidth][boardHeight];
	//main game loop
	while (bombsLeft > 0 && alive)
	{
		drawBoard(boardWidth, boardHeight, bombsLeft);
		cin.clear();
		cin.sync();
	}
	system("pause");
	return 0;
}

/*
function drawBoard
clears the terminal (windows specific) then redraws the board
*/
void drawBoard(int boardWidth, int boardHeight, int bombsLeft)
{
	//clear the terminal
	system("cls");
	//setup the visual representation of the board
	cout << "Welcome to Minesweeper\n\n";
	cout << "There are " << bombsLeft << " bombs remaining\n\n";
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
}