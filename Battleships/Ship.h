#pragma once
#include "Box.h"
#include "Coordinates.h"

class Ship
{
private:
	const int numberOfMasts;
	bool alive;
	int numberOfMastsLeft;
	Coordinates startCoords;
	Orientation orientation;
	Box** ownedBoxes;
	void setOwnerOfBoxes();
public:
	Ship(int, Box**, Coordinates, Orientation);
	~Ship();
	int getNumberOfMasts();
	Coordinates getStartCoords();
	Orientation getOrientation();
	void decrementNumberOfMasts();
	bool isAnyMastLeft();
	void setOwnedBoxesState(BoxState);
};