#pragma once
#include <iostream>
#include <string>
#include <list>
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
	void printSaveGame();
	void printExit();
	void printPause();

	void printSetShips();
	void printSetShipsRandomly();
	void printSetXMastedShip(int);
	void printRandomizationComputerShipsLocation();

	void printPlayerShot();
	void printPlayerShotComment(bool);
	void printComputerShot(int, int, bool);
	void printPlayingBoards(char**, char**, int = 10);
	void printInvalidCoordinates();
	void printPlayerWon();
	void printComputerWon();
	void printResultOfGame(bool);


	void printBoardAsCharTable(char**, int = 10);
	void printShipsLeft(int* numberOfXMastedShips, int maxNumberOfShips);
	
	void printExistingSaveGames(std::list<std::string>*);
	void printSaveGameResult(bool);
	void printLoadGameResult(bool);

	void printToBeDone();
};

