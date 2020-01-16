#pragma once
#include "Coordinates.h"
#include "Board.h"

enum ShotResult
{
	hit,
	miss
};

class AI
{
private:
	Board* enemyBoard;
	int maxNumberOfMasts;
	int* numberOfXMastedShips;
	Coordinates lastShotCoordinates;
	ShotResult lastShotResult;

	bool* prepareXMastedShipLeft();

public:
	AI(int _maxNumberOfMasts, int* _numberOfXMastedShips);
	~AI();

	Coordinates shot();
};

