#pragma once
#include "Box.h"

class Ship
{
private:
	const int numberOfMasts;
	bool alive;
	int numberOfMastsLeft;
	Box** ownedBoxes;
public:

	Ship(int _numOfMasts, Box tableOfBoxes[]) : numberOfMasts(_numOfMasts)
	{
		alive = true;
		*ownedBoxes = tableOfBoxes;
		numberOfMastsLeft = numberOfMasts;
	}
	~Ship();

	void decrementNumberOfMasts();
	bool getAlivenessStatus();
	bool isAnyMastLeft();
	void setOwnedBoxesState(BoxState state)
	{
		for (int i = 0; i < numberOfMasts; i++)
		{
			ownedBoxes[i]->setState(state);
		}
		alive = false;
	}
};