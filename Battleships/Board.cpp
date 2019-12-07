#include "Board.h"

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