#pragma once
#include "model.h"
#include "view.h"
#include <memory>
#include <list>

enum State
{
	menuState,
	setShipsState,
	playState,
	loadGameState,
	exitState
};

class Engine
{
private:
	State state;
	Model* player[2];
	View* view;

public:
	Engine();
    void run();
	Model* setShipsByHand();
	Model* setShipsRandomly();
	bool playerShoot();
	bool computerShoot();

	std::list<int> readInput(int);
};