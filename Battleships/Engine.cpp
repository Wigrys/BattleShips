#include "Engine.h"
#include <conio.h>
#include <windows.h>

Engine::Engine()
{
	player[0] = new Model(); //player[0] is first player
	player[1] = new Model(); //player[1] is second player/computer
	view = new View();
	state = menuState;
}

void Engine::run()
{
	bool close = false;
	while (!close)
	{
		switch (state)
		{
		case menuState:
		{
			view->printMenu();
			auto input = readInput(1);
			switch (*input.begin())
			{
			case '1':
				state = setShipsState;
				break;
			case '2':
				state = loadGameState;
				break;
			case '0':
				state = exitState;
				break;
			default:
				view->setMessage("There is no such operation! Try again:\n");
			}
			break;
		}
		case setShipsState:
		{
			view->printSetShips();
			auto input = readInput(1);
			switch (*input.begin())
			{
			case '1':
				view->printSetShipsRandomly();
				while ((player[0] = setShipsRandomly()) == nullptr);
				break;
			case '2':
				//ustawianie swoich statkow recznie
				while((player[0] = setShipsByHand()) == nullptr);
				view->printBoardAsCharTable(player[0]->getBoardConvertedToCharTable());
			default:
				view->setMessage("There is no such operation! Try again:\n");
				break;
			}
			//ustawianie statkow komputera losowo
			view->printRandomizationComputerShipsLocation();
			while ((player[1] = setShipsRandomly()) == nullptr);
			std::cout << "Every single ship is placed... get ready to play!";
			state = State::playState;
			break;
		}
		case loadGameState:
			view->printLoadGame();
			break;
		case playState:
			while (1)
			{
				while (playerShoot());
				if (player[1]->isAnyShipAlive() == false)
				{
					break;
				}
				while (computerShoot());
				if (player[0]->isAnyShipAlive() == false)
				{
					break;
				}
			}
			Sleep(5000);
			state = State::menuState;
			break;
		case exitState:
			view->printExit();
			close = true;
			break;
		}
	}
}

int randFromRange(int x, int y)
{
	return rand() % (y - x) + x;
}

Model* Engine::setShipsByHand()
{
	Model* preModel = new Model();
	for (int numberOfMasts = preModel->getMaxNumberOfMasts(); numberOfMasts > 0; numberOfMasts--)
	{
		while (preModel->ableToAddXMastedShip(numberOfMasts))
		{
			view->printSetXMastedShip(numberOfMasts);
			view->printBoardAsCharTable(preModel->getBoardConvertedToCharTable(), preModel->getBoardSize());
			auto input = readInput(3);
			std::list<int>::iterator iterator = input.begin();
			Coordinates c = { *iterator++ - '0', *iterator++ - '0' };
			Orientation o = Orientation::none;
			if (*iterator == 'h')
				o = Orientation::horizontal;
			if (*iterator == 'v')
				o = Orientation::vertical;
			if (!preModel->addShipToList(c, o, numberOfMasts) || o == Orientation::none)
			{
				std::cout << "\nUnable to set this ship. Try again.";
			}
			else
				std::cout << "\nSet ship at: " << c.x << ", " << c.y;
			Sleep(1000);
		}
	}
	bool agree = true; // tutaj bedzie pytanie czy plansza odpowiada graczowi
	if (agree)
	{
		return preModel;
	}
	delete preModel;
	return false;
}

Model* Engine::setShipsRandomly()
{
	bool success = true;
	int attempts = 0;
	Model* preModel = new Model();
	for (int numberOfMasts = preModel->getMaxNumberOfMasts(); numberOfMasts > 0; numberOfMasts--)
	{
		while (preModel->ableToAddXMastedShip(numberOfMasts))
		{
			Coordinates c = { randFromRange(0, 9), randFromRange(0, 9) };
			Orientation o = Orientation::none;
			if (randFromRange(0, 2))
				o = Orientation::horizontal;
			else
				o = Orientation::vertical;
			preModel->addShipToList(c, o, numberOfMasts);
			attempts++;
			if (attempts > 100)
			{
				success = false;
				break;
			}
		}
		if (!success)
			break;
	}
	if (success)
	{
		return preModel;
	}
	return nullptr;
}

bool Engine::computerShoot()
{
	return player[0]->receiveShot(Coordinates() = { randFromRange(0, 9), randFromRange(0, 9) });
}

bool Engine::playerShoot()
{
	view->printPlayingBoards(player[0]->getBoardConvertedToCharTable(), player[1]->getEnemyBoardConvertedToCharTable());
	auto input = readInput(2);
	std::list<int>::iterator iterator = input.begin();
	return player[1]->receiveShot(Coordinates() = { *iterator++ - '0', *iterator - '0' });
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
		Sleep(200);
	}
	return inputList;
}

