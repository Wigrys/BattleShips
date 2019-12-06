#include "Ship.h"

Ship::Ship(int _numOfMasts, Box** tableOfBoxes) : numberOfMasts(_numOfMasts)
{
	alive = true;
	ownedBoxes = tableOfBoxes;
	numberOfMastsLeft = numberOfMasts;
}

Ship::~Ship()
{
	for (int i = 0; i < numberOfMasts; i++)
		delete ownedBoxes[i];
	delete[] ownedBoxes;
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

void Ship::setOwnedBoxesState(BoxState state)
{
	for (int i = 0; i < numberOfMasts; i++)
	{
		ownedBoxes[i]->setState(state);
	}
	alive = false;
}

