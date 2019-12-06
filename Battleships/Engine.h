#pragma once
#include "model.h"
#include "view.h"
#include <memory>
#include <list>

enum State
{
	menu,
	setShips,
	loadGame,
	exitState
};

class Engine
{
private:
	State state;
	std::shared_ptr<Model> model;
	std::shared_ptr<View> view;

public:
	Engine();
    void run();
	std::list<int> readInput(int);
};