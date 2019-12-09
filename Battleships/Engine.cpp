#include "Engine.h"
#include <conio.h>
#include <windows.h>

Engine::Engine()
{
	model = new Model();
	view = new View();
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
				for (int numberOfMasts = 4; numberOfMasts > 0; numberOfMasts--)
				{
					while (model->ableToAddXMastedShip(numberOfMasts))
					{
						view->printSetXMastedShip(numberOfMasts);
						view->printBoardAsCharTable(model->getBoardConvertedToCharTable(), model->getBoardSize());
						auto input = readInput(3);
						std::list<int>::iterator iterator = input.begin();
						Coordinates c = { *iterator++ - '0', *iterator++ - '0' };
						Orientation o = *iterator == 'h' ? Orientation::horizontal : Orientation::vertical;
						if (!model->setShip(c, o, numberOfMasts))
						{
							std::cout << "\nUnable to set this ship. Try again.";
						}
						else
							std::cout << "\nSet ship at: " << c.x << ", " << c.y;
						Sleep(1000);
					}
				}
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
		std::list<int>::iterator iter = inputList.begin();
		for (int h = 0; h < i; h++)
			iter++;
		std::cout << (char)*iter;
		if ( i != numberOfInput - 1)
			std::cout << ", ";
	}
	return inputList;
}

