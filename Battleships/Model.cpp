#include "Model.h"
#include <iostream>

Model::Model()
{
	board = new Board();
	numberOfXMastedShips = new int[maxNumberOfMasts];
	for (int i = 0; i < maxNumberOfMasts; i++)
		numberOfXMastedShips[i] = 0;
}

Model::~Model()
{
	delete board;
}

int Model::getBoardSize()
{
	return board->getSize();
}

int Model::getMaxNumberOfMasts()
{
	return maxNumberOfMasts;
}

char** Model::getBoardConvertedToCharTable()
{
	mapStateChar =
	{
		{ BoxState::free, ' ' }, // 'f'
		{ BoxState::set, 's' },
		{ BoxState::unableToSet, ' ' }, // 'u'
		{ BoxState::hit, 'h' },
		{ BoxState::shot, 'o' },
		{ BoxState::down, 'd' },
	};
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

char** Model::getEnemyBoardConvertedToCharTable()
{
	mapStateChar =
	{
		{ BoxState::free, ' ' }, // 'f'
		{ BoxState::set, 'i' },
		{ BoxState::unableToSet, ' ' }, // 'u'
		{ BoxState::hit, 'h' },
		{ BoxState::shot, 'o' },
		{ BoxState::down, 'd' },
	};
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

bool Model::addShipToList(Coordinates c, Orientation o, int n)
{
	if (ableToSetShipOnBoard(c, o, n))
	{
		Box** boxes;
		boxes = board->setShip(c, o, n);
		Ship* s = new Ship(n, boxes);
		ships.push_back(s);
		numberOfXMastedShips[s->getNumberOfMasts() - 1]++;
		return true;
	}
	else
		return false;
}

bool Model::isAnyShipAlive()
{
	std::list<Ship*>::iterator iterator;
	bool isAnyAlive = false;
	for (iterator = ships.begin(); iterator != ships.end(); iterator++)
	{
		if ((*iterator)->isAnyMastLeft())
			return true;
	}
	return false;
}

bool Model::receiveShot(Coordinates shotCoordinates)
{
	if (board->getBoxStateOfBox(shotCoordinates) == BoxState::set)
	{
		board->setBoxStateOfBox(shotCoordinates, BoxState::hit);
		board->getBoxOwner(shotCoordinates)->decrementNumberOfMasts();
		if (!board->getBoxOwner(shotCoordinates)->isAnyMastLeft())
			board->getBoxOwner(shotCoordinates)->setOwnedBoxesState(BoxState::down);
		return true;
	}
	else
	if(board->getBoxStateOfBox(shotCoordinates) == BoxState::free || board->getBoxStateOfBox(shotCoordinates) == BoxState::unableToSet)
		board->setBoxStateOfBox(shotCoordinates, BoxState::shot);
	return false;
}
