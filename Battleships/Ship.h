#pragma once
#include "Box.h"

class Ship
{
private:
	const int numberOfMasts;
	bool alive;
	int numberOfMastsLeft;
	Box** ownedBoxes;
	void setOwnerOfBoxes();
public:
	Ship(int, Box**);
	~Ship();
	int getNumberOfMasts();
	void decrementNumberOfMasts();
	bool isAnyMastLeft();
	void setOwnedBoxesState(BoxState);
};