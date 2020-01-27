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
	View* view;
	int maxNumberOfMasts = 4;
	Model* player[2];

	Tour whoseTour;
	bool gameInProgress;
	bool playerWon;
	bool wasEscapePressed;

	Model* setShipsByHand();
	Model* setShipsRandomly();

	bool playerShoot();
	bool computerShoot();
	bool areCoordinatesOfShotOkay(Coordinates);

	std::list<int> readInput(int);
	std::string makeSavedGamePath(std::string);
	std::list<std::string>* getListOfSaveGames();
	bool saveGame(std::string);
	bool loadGame(std::string);
public:

	Engine();
    void run();

};