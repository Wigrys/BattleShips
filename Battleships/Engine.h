#pragma once
#include "model.h"
#include "view.h"
#include <memory>
#include <list>

enum State
{
	menuState,
	loadGameState,
	saveGameState,

	setShipsState,
	setShipsRandomlyState,
	setShipsByHandState,

	playState,
	endGameState,
	finishGameState,

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
	bool gameInProgress;
	bool playerWon;
	bool wasEscapePressed;

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

	bool AIShoot(Board* enemyBoard);

	bool areCoordinatesOfShotOkay(Coordinates);

	std::list<int> readInput(int);
	std::string makeSaveGamePath(std::string);
	bool saveGame(std::string);

};