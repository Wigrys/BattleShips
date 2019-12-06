#include "Ship.h"

Ship::Ship(int _numOfMasts, Box* tableOfBoxes[]) : numberOfMasts(_numOfMasts)
{
	*ownedBoxes = *tableOfBoxes;
	numberOfMastsLeft = numberOfMasts;
}

Ship::~Ship()
{
	delete[] ownedBoxes;
}

void Ship::decrementNumberOfMasts()
{
	numberOfMastsLeft--;
}

bool Ship::isAnyMastAlive()
{
	if (numberOfMastsLeft == 0)
		return false;
	return true;
}
