#pragma once
#include "Board.h"
#include "Ship.h"
#include <list>
#include <map>

class Model
{
private:
	const int maxNumberOfMasts = 4;
	Board* board;
	list<Ship*> ships;
	int* numberOfXMastedShips;
	std::map<BoxState, char> mapStateChar;
public:
	Model();
	~Model();

	char** getBoardConvertedToCharTable();
	void addShip(Ship*);
	bool isAbleToAddXMastedShip(int); // sprawdza czy jest jeszcze miejsce na x masztowy statek
};

