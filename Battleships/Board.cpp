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
		return true;
	else
		return false;
}

Coordinates prepareXYLimitsAsCoordinates(Orientation orient, int numOfMasts)
{
	Coordinates limits;
	if (orient == Orientation::horizontal)
	{
		limits.x = numOfMasts + 2;
		limits.y = 3;
	}
	else
	{
		limits.x = 3;
		limits.y = numOfMasts + 2;
	}
	return limits;
}

//sprawdza mi tylko w jednej kollumnie, trzbza zrobic zeby wokol statku tez sprawdzal
bool Board::ableToSetShip(Coordinates coords, Orientation orientation, int numberOfMasts) //ogolnie to moznaby to poprawic zeby lepiej wygladalo
{
	Coordinates limit = prepareXYLimitsAsCoordinates(orientation, numberOfMasts);
	Coordinates v = convertOrientationIntoCoordinates(orientation); // zastanawiam sie czy nie zrobic klasy pochodnej od coordinates, ktora by nic nie zmianiala tylko nazwe typu
	coords.x--;
	coords.y--;
	for (int x = coords.x; x < coords.x + limit.x; x++)
	{
		for (int y = coords.y; y < coords.y + limit.y; y++)
		{

			if (!coordinatesOutOfBoard(Coordinates() = {x, y}))
			{
				if (tableOfBoxes[x][y].getState() != BoxState::free)
					return false;
			}
		}
	}
	return true;
}

Box** Board::setShip(Coordinates coords, Orientation orient, int numberOfMasts)
{
	Box** boxes = new Box * [numberOfMasts];
	Coordinates startingCoordinates = coords;
	Coordinates v = convertOrientationIntoCoordinates(orient);
	for (int i = 0; i < numberOfMasts; i++)
	{
		tableOfBoxes[coords.x][coords.y].setState(BoxState::set);
		boxes[i] = &tableOfBoxes[coords.x][coords.y];
		coords.x += v.x;
		coords.y += v.y;
	}
	Coordinates limit = prepareXYLimitsAsCoordinates(orient, numberOfMasts);
	coords = startingCoordinates;
	coords.x--;
	coords.y--;
	for (int x = coords.x; x < coords.x + limit.x; x++)
	{
		for (int y = coords.y; y < coords.y + limit.y; y++)
		{
			if (!coordinatesOutOfBoard(Coordinates() = { x, y }))
			{
				if (tableOfBoxes[x][y].getState() == BoxState::free)
					tableOfBoxes[x][y].setState(BoxState::unableToSet);
			}
		}
	}
	return boxes;
}
