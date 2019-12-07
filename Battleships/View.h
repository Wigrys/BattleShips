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
	void printSetShipsByHand();

	void printBoardAsCharTable(char**, int);
};

