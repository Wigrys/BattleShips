#include "Engine.h"
#include <conio.h>

Engine::Engine()
{
	model = std::make_shared<Model>();
	view = std::make_shared <View>();
	state = menu;
}

void Engine::run()
{
	bool close = false;
	while (!close)
	{
		switch (state)
		{
		case menu:
		{
			view->printMenu();
			auto input = readInput(1);
			switch (*input.begin())
			{
			case '1':
				state = setShips;
				break;
			case '2':
				state = loadGame;
				break;
			case '0':
				state = exitState;
				break;
			default:
				view->setMessage("There is no such operation! Try again:\n");
			}
			break;
		}
		case setShips:
		{
			view->printSetShips();
			auto input = readInput(1);
			switch (*input.begin())
			{
			case '1':
				view->printSetShipsRandomly();
				break;
			case '2':
				view->printSetShipsByHand();
				break;
			default:
				view->setMessage("There is no such operation! Try again:\n");
			}
			break;
		}
		case loadGame:
			view->printLoadGame();
			break;
		case exitState:
			view->printExit();
			close = true;
			break;
		}
	}
}

std::list<int> Engine::readInput(int numberOfInput) //zczytuje okreslona ilosc znakow
{
	std::list<int> inputList;
	for (int i = 0; i < numberOfInput; i++)
	{
		inputList.push_back(_getch());
	}
	return inputList;
}

