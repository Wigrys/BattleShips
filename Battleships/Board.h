#pragma once
#include "Box.h"
#include "Coordinates.h"

class Board
{
private:
	const int size = 10;
	Box** tableOfBoxes;
public:
	Board();
	~Board();
	int getSize();
	Box** getTableOfBoxes();
	bool ableToSetShip(Coordinates, Orientation, int);
};

