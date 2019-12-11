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
	BoxState getBoxStateOfBox(Coordinates);
	void setBoxStateOfBox(Coordinates, BoxState);
	Ship* getBoxOwner(Coordinates);

	bool ableToSetShip(Coordinates, Orientation, int);
	Box** setShip(Coordinates, Orientation, int);
};

