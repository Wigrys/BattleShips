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
	void printSetXMastedShip(int x);

	void printBoardAsCharTable(char**, int);
};

