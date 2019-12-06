#include "Ship.h"

Ship::~Ship()
{
	delete ownedBoxes;
}

void Ship::decrementNumberOfMasts()
{
	numberOfMastsLeft--;
}

bool Ship::getAlivenessStatus()
{
	return alive;
}

bool Ship::isAnyMastLeft()
{
	if (numberOfMastsLeft == 0)
		return false;
	return true;
}

