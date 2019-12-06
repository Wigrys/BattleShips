#include "Ship.h"

Ship::Ship(int _numOfMasts, Box* tableOfBoxes[]) : numberOfMasts(_numOfMasts)
{
	*ownedBoxes = *tableOfBoxes;
}

Ship::~Ship()
{
	delete[] ownedBoxes;
}
