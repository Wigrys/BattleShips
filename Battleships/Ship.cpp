#include "Ship.h"

void Ship::setOwnerOfBoxes()
{
	for (int i = 0; i < numberOfMasts; i++)
	{
		ownedBoxes[i]->setOwner(this);
	}
}

Ship::Ship(int _numOfMasts, Box** tableOfBoxes) : numberOfMasts(_numOfMasts)
{
	alive = true;
	ownedBoxes = tableOfBoxes;
	numberOfMastsLeft = numberOfMasts;
	setOwnerOfBoxes();
}

Ship::~Ship()
{
	for (int i = 0; i < numberOfMasts; i++)
		delete ownedBoxes[i];
	delete[] ownedBoxes;
}

int Ship::getNumberOfMasts()
{
	return numberOfMasts;
}

void Ship::decrementNumberOfMasts()
{
	numberOfMastsLeft--;
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

