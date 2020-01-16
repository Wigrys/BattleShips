#include "AI.h"
#include <iostream>


bool* AI::prepareXMastedShipLeft()
{
	bool* XMastedShipsLeft = new bool[maxNumberOfMasts];
	for (int i = 0; i < maxNumberOfMasts; i++)
	{
		if (numberOfXMastedShips[i] != 0)
			XMastedShipsLeft[i] = true;
	}
	return XMastedShipsLeft;
}

AI::AI(int _maxNumberOfMasts, int* _numberOfXMastedShips)
{
	maxNumberOfMasts = _maxNumberOfMasts;
	numberOfXMastedShips = _numberOfXMastedShips;
	enemyBoard = new Board();
	lastShotResult = miss;
}

AI::~AI()
{
	delete enemyBoard;
}

Coordinates AI::shot()
{
	if (lastShotResult == ShotResult::miss)
	{
		bool* XMastedShipsLeft = prepareXMastedShipLeft();
		int possibilities[10][10] = { 0 };
		for (int x = 0; x < enemyBoard->getSize(); x++)
		{
			for (int y = 0; y < enemyBoard->getSize(); y++)
			{
				for (int g = 1; g <= maxNumberOfMasts; g++)
				{
					if (XMastedShipsLeft[g] != false)
					{
						//vertical
						if (enemyBoard->ableToSetShip({ x, y }, vertical, g))
							possibilities[x][y]++;
						//horizontal
						if (enemyBoard->ableToSetShip({ x, y }, horizontal, g))
							possibilities[x][y]++;
					}
				}
			}
		}
		for (int x = 0; x < enemyBoard->getSize(); x++)
		{
			for (int y = 0; y < enemyBoard->getSize(); y++)
			{
				std::cout << possibilities[x][y] << " ";
			}
			std::cout << std::endl;
		}
	}
	else
	{

	}
	return Coordinates();
}
