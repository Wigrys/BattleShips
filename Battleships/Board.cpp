#include "Board.h"
#include "Coordinates.h"


Board::Board()
{
	tableOfBoxes = new Box*[size];
	for (int i = 0; i < size; i++)
	{
		tableOfBoxes[i] = new Box[size];
	}
}

Board::~Board()
{
	for (int i = 0; i < size; ++i)
		delete[] tableOfBoxes[i];
	delete[] tableOfBoxes;
}

int Board::getSize()
{
	return size;
}

Box** Board::getTableOfBoxes()
{
	return tableOfBoxes;
}

Coordinates convertOrientationIntoCoordinates(Orientation orientation) // coordinates posluzy mi jako zespol vectora x i vectora y
{
	Coordinates v{ -1, -1 };
	switch (orientation)
	{
	case horizontal:
		v.x = 1;
		v.y = 0;
		break;
	case vertical:
		v.x = 0;
		v.y = 1;
		break;
	}
	return v;
}

bool coordinatesOutOfBoard(Coordinates c)
{
	if (c.x < 0 || c.x > 9 || c.y < 0 || c.y > 9)
		return false;
	else
		return true;
}


bool Board::ableToSetShip(Coordinates coords, Orientation orientation, int numberOfMasts)
{
	Coordinates v = convertOrientationIntoCoordinates(orientation);
	if (orientation == horizontal)
		coords.x--;
	else
		coords.y--;
	for (int i = numberOfMasts - 1; i < numberOfMasts + 1; i++) 
	{
		if (coordinatesOutOfBoard(coords))
			return false;
		else
		{
			if (tableOfBoxes[coords.x][coords.y].getState() != BoxState::free)
				return false;
		}
	}
	return true;
}