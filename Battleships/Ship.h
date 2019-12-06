#pragma once
#include "Box.h"

class Ship
{
private:
	const int numberOfMasts;
	Box* ownedBoxes[];
public:
	Ship(int _numOfMasts, Box* tableOfBoxes[]);
	~Ship();
};