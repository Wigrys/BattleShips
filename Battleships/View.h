#pragma once
#include <iostream>
#include <string>
class Board;

class View
{
private:
	std::string message = "";
	void printMessage();
public:
	View();
	void setMessage(std::string);
	void printMenu();
	void printLoadGame();
	void printExit();

	void printSetShips();
	void printSetShipsRandomly();
	void printSetXMastedShip(int);
	void printRandomizationComputerShipsLocation();

	void printPlayerShot();
	void printPlayerShotComment(bool);
	void printComputerShot(int, int, bool);
	void printPlayingBoards(char**, char**, int = 10);


	void printBoardAsCharTable(char**, int = 10);
};

