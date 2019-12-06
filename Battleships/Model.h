#pragma once
#include "Board.h"
#include "Ship.h"

class Model
{
private:
	const int maxNumberOfMasts = 4;
	Board* board;
	Ship** ships;
public:
	Model();
	~Model();
};

