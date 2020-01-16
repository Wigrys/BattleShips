#pragma once
#include "model.h"
#include "view.h"
#include <memory>
#include <list>

enum State
{
	menuState,
	loadGameState,
	setShipsState,
	playState,
	pauseState,
	exitState
};

enum Tour
{
	player,
	computer
};

class Engine
{
private:
	State state;
	Model* player[2];
	Tour whoseTour;
	View* view;
	const int maxNumberOfMasts = 1;
	std::map<State, State> mapEscapeState;
public:
	Engine();
    void run();
	Model* setShipsByHand();
	Model* setShipsRandomly();
	bool playerShoot();
	bool computerShoot();
	bool areCoordinatesOfShotOkay(Coordinates);

	std::list<int> readInput(int);
};