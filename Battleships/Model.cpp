#include "Model.h"
#include <iostream>

Model::Model()
{
	board = new Board();
	numberOfXMastedShips = new int[maxNumberOfMasts];
	for (int i = 0; i < maxNumberOfMasts; i++)
		numberOfXMastedShips[i] = 0;
	mapStateChar =
	{
		{ BoxState::free, ' ' }, // 'f'
		{ BoxState::set, 's' },
		{ BoxState::unableToSet, ' ' }, // 'u'
		{ BoxState::hit, 'h' },
		{ BoxState::down, 'd' },
	};
}

Model::~Model()
{
	delete board;
}

int Model::getBoardSize()
{
	return board->getSize();
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

void Model::addShipToList(Ship* _ship)
{
	ships.push_back(_ship);
	numberOfXMastedShips[_ship->getNumberOfMasts() - 1]++; //mast 1 is counted in table[0], mast 2 -> table[1] etc
}

bool Model::ableToAddXMastedShip(int numberOfMasts) //liczba masztow (1 ; 4)
{
	if (numberOfXMastedShips[numberOfMasts - 1] < maxNumberOfMasts - (numberOfMasts - 1))
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
bool Model::setShip(Coordinates c, Orientation o, int n)
{
	if (ableToSetShipOnBoard(c, o, n))
	{
		Box** boxes;
		boxes = board->setShip(c, o, n);
		Ship* s = new Ship(n, boxes);
		addShipToList(s);
		return true;
	}
	else
		return false;
}
