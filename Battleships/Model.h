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

	int getBoardSize();
	int getMaxNumberOfMasts();
	char** getBoardConvertedToCharTable();
	char** getEnemyBoardConvertedToCharTable();


	bool ableToAddXMastedShip(int); // sprawdza czy jest jeszcze miejsce na x masztowy statek
	bool ableToSetShipOnBoard(Coordinates, Orientation, int); //ten Ship w nazwie to nie jest dokladnie ship obiektowy
	void setShipOnBoard(Coordinates, Orientation, int);
	bool addShipToList(Coordinates, Orientation, int);

	bool isAnyShipAlive();
	bool receiveShot(Coordinates);
};

/*

Trzeba niektore funkcje zagniezdzic i wywolywac tylko w innych funkcjach
i ustwaic te funkcje jako private

*/