#pragma once
#include <list>
#include <map>
#include "Board.h"
#include "Ship.h"
#include "Coordinates.h"


class Model
{
private:
	const int maxNumberOfMasts; // ustawianie liczby statkow (5 - jeden 5 masztowiec, dwa 4 masztowce itd... 4 - jeden 4 masztowiec, dwa 3 masztowce itd...)
	Board* board;
	std::list<Ship*> ships;
	int* numberOfXMastedShips;
	std::map<BoxState, char> mapStateChar;

public:
	Model(int maxNumberOfMasts);
	~Model();

	int getBoardSize();
	int getMaxNumberOfMasts();
	std::list<Ship*> getShips();
	char** getBoardConvertedToCharTable();
	int* getNumberOfXMastedShips();
	char** getEnemyBoardConvertedToCharTable();

	void decrementNumberOfXMastedShips(int);
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