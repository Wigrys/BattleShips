#include "Engine.h"
#include <conio.h>
#include <windows.h>

Engine::Engine()
{
	player[0] = new Model(maxNumberOfMasts); //player[0] is first player
	player[1] = new Model(maxNumberOfMasts); //player[1] is second player/computer
	view = new View();
	state = menuState;
	if (rand() % 2 == 0)
		whoseTour = Tour::player;
	else
		whoseTour = Tour::computer;
	mapEscapeState =
	{
		{State::loadGameState, State::menuState},
		{State::setShipsState, State::menuState},
		{State::playState, State::pauseState},
		{State::pauseState, State::playState}
	};

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
				while ((player[0] = setShipsRandomly()) == nullptr);
				break;
			case '2':
				//ustawianie swoich statkow recznie
				while ((player[0] = setShipsByHand()) == nullptr);
			default:
				view->setMessage("There is no such operation! Try again:\n");
				break;
			}
			//ustawianie statkow komputera losowo
			view->printRandomizationComputerShipsLocation();
			while ((player[1] = setShipsRandomly()) == nullptr);
			std::cout << "Every single ship is placed... get ready to play!";
			Sleep(2000);
			state = State::playState;
			break;
		}
		case loadGameState:
			view->printLoadGame();
			break;
		case playState:
		{
			bool playerWon = false;
			bool gameInProgress = true;
			while (gameInProgress)
			{
				view->printPlayingBoards(player[0]->getBoardConvertedToCharTable(), player[1]->getEnemyBoardConvertedToCharTable());
				view->printShipsLeft(player[1]->getNumberOfXMastedShips(), player[1]->getMaxNumberOfMasts());
				if (whoseTour == 0)
				{
					if (!playerShoot())
						whoseTour = Tour::computer;
				}
				else
				{
					if (!computerShoot())
						whoseTour = Tour::player;
				}
				if (!player[0]->isAnyShipAlive())
				{
					playerWon = false;
					gameInProgress = false;
				}
				if (!player[1]->isAnyShipAlive())
				{
					playerWon = true;
					gameInProgress = false;
				}
			}
			view->printPlayingBoards(player[0]->getBoardConvertedToCharTable(), player[1]->getEnemyBoardConvertedToCharTable());
			if (playerWon)
				view->printPlayerWon();
			else
				view->printComputerWon();
			Sleep(3000);
			state = State::menuState;
			delete player[0];
			delete player[1];
			break;
		}
		case pauseState:
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
	Model* preModel = new Model(maxNumberOfMasts);
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
	view->printSetShipsRandomly();
	bool success = true;
	int attempts = 0;
	Model* preModel = new Model(maxNumberOfMasts);
	for (int numberOfMasts = preModel->getMaxNumberOfMasts(); numberOfMasts > 0; numberOfMasts--)
	{
		while (preModel->ableToAddXMastedShip(numberOfMasts))
		{
			Coordinates c = { randFromRange(0, 10), randFromRange(0, 10) };
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
	int x = randFromRange(0, 10);
	int y = randFromRange(0, 10);
	bool hit = player[0]->receiveShot(Coordinates() = { x, y });
	view->printComputerShot(x, y, hit);
	Sleep(1000);
	return hit;
}

bool Engine::areCoordinatesOfShotOkay(Coordinates coords)
{
	if (coords.x < 0 || coords.x > 9 || coords.y < 0 || coords.y > 9)
		return false;
	return true;
}

bool Engine::playerShoot()
{
	bool madeShot = false;
	bool hit = false;
	do
	{
		view->printPlayerShot();
		auto input = readInput(2);
		std::list<int>::iterator iterator = input.begin();
		if (areCoordinatesOfShotOkay(Coordinates() = { *iterator++ - '0', *iterator - '0' }))
		{
			iterator = input.begin();
			hit = player[1]->receiveShot(Coordinates() = { *iterator++ - '0', *iterator - '0' });
			view->printPlayerShotComment(hit);
			Sleep(1000);
			madeShot = true;
			break;
		}
		else
		{
			view->printInvalidCoordinates();
			madeShot = false;
		}
	} while (!madeShot);
	return hit;
}

std::list<int> Engine::readInput(int numberOfInput) //zczytuje okreslona ilosc znakow
{
	std::list<int> inputList;
	for (int i = 0; i < numberOfInput;)
	{
		int inp = _getch();
		//if (inp = 27) //27 = ESC
			//state = pauseState; 
		if ((inp >= '0' && inp <= '9') || (inp == 'h' || inp == 'v'))
		{
			inputList.push_back(inp);
			std::list<int>::iterator iter = inputList.begin();

			for (int h = 0; h < i; h++)
				iter++;
			std::cout << (char)*iter;
			if (i != numberOfInput - 1)
				std::cout << ", ";
			else
				std::cout << ".";
			Sleep(200);
			i++;
		}
	}
	return inputList;
}