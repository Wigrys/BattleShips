#include "Model.h"
#include <iostream>

Model::Model()
{
	board = new Board();
	numberOfXMastedShips = new int[maxNumberOfMasts];
	mapStateChar =
	{
		{ BoxState::free, 'f' },
		{ BoxState::set, 's' },
		{ BoxState::unableToSet, 'u' },
		{ BoxState::hit, 'h' },
		{ BoxState::down, 'd' },
	};
}

Model::~Model()
{
	delete board;
}

char** Model::getBoardConvertedToCharTable()
{
	Box** tableOfBoxes = board->getTableOfBoxes();
	char** tableOfChars = new char* [board->getSize()];
	for (int i = 0; i < board->getSize(); i++)
	{
		tableOfChars[i] = new char[board->getSize()];
	}
	for (int i = 0; i < board->getSize(); i++)
	{
		for (int h = 0; h < board->getSize(); h++)
		{
			tableOfChars[i][h] = mapStateChar[tableOfBoxes[i][h].getState()];
		}
	}
	return tableOfChars;
}

void Model::addShip(Ship* _ship)
{
	ships.push_back(_ship);
	numberOfXMastedShips[_ship->getNumberOfMasts() - 1]++; //mast 1 is counted in table[0], mast 2 -> table[1] etc
}

bool Model::ableToAddXMastedShip(int numberOfMasts) //liczba masztow (1 ; 4)
{
	if (numberOfXMastedShips[numberOfMasts] <= maxNumberOfMasts - (numberOfMasts - 1))
	{
		return true;
	}
	else
		return false;
}

bool Model::ableToSetShipOnBoard(Coordinates c, Orientation o, int n)
{
	return board->ableToSetShip(c, o, n);
}

void Model::setShipOnBoard(Coordinates c, Orientation o, int n)
{
	board->setShip(c, o, n);
}

//identyczne cos musze napisac po prostu w engine gdy bede stawial statki
void Model::tempSetShip(Coordinates c, Orientation o, int n)
{
	if (ableToAddXMastedShip(n))
	{
		if (ableToSetShipOnBoard(c, o, n))
		{
			Box** boxes;
			boxes = board->setShip(c, o, n);
			Ship* s = new Ship(n, boxes);
			addShip(s);
		}
		else
			std::cout << "\nUnable to set Ship On Board - probably these boxes are already occupied.\n";
	}
	else
		std::cout << "\nUnable to set Ship On Board - probably there are too many of ships with this number of masts.\n";
}
