#pragma once
#include <list>
#include <map>
#include "Board.h"
#include "Ship.h"
#include "Coordinates.h"


class Model
{
private:
	const int maxNumberOfMasts = 4;
	Board* board;
	std::list<Ship*> ships;
	int* numberOfXMastedShips;
	std::map<BoxState, char> mapStateChar;
public:
	Model();
	~Model();

	char** getBoardConvertedToCharTable();
	void addShip(Ship*); //bede tworzyc obiekty porzebne do wywolania konstruktora i wywolam go jako argument funkcji addShip();
	bool ableToAddXMastedShip(int); // sprawdza czy jest jeszcze miejsce na x masztowy statek
	bool ableToSetShip(Coordinates, Orientation, int);
};