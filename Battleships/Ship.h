#pragma once
#include "Box.h"

class Ship
{
private:
	const int numberOfMasts;
	int numberOfMastsLeft;
	Box* ownedBoxes[];
public:

	Ship(int _numOfMasts, Box* tableOfBoxes[]);
	~Ship();

	void decrementNumberOfMasts();
	bool isAnyMastLeft();
};