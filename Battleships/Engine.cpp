#include "Engine.h"
#include <conio.h>
#include <windows.h>
#include <fstream>
#include <filesystem>
#include <string>

Engine::Engine()
{
	view = new View();
	state = menuState;
	if (rand() % 2 == 0)
		whoseTour = Tour::player;
	else
		whoseTour = Tour::computer;
	gameInProgress = false;
	playerWon = false;
	wasEscapePressed = false;
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
		case loadGameState:
		{
			std::string nameOfFile;
			bool result = true;
			view->printLoadGame();
			view->printExistingSaveGames(getListOfSaveGames());
			std::cin >> nameOfFile;
			result = loadGame(nameOfFile);
			view->printLoadGameResult(result);
			Sleep(1000);
			if (result)
				state = playState;
			else
				state = menuState;
			break;
		}
		case saveGameState: //done
		{
			std::string nameOfFile;
			bool result = true;
			do
			{
				view->printSaveGame();
				std::cin >> nameOfFile;
				result = saveGame(nameOfFile);
				view->printSaveGameResult(result);
				Sleep(1000);
			} while (!result);
			state = pauseState;
			break;
		}
		case setShipsState:
		{
			view->printSetShips();
			auto input = readInput(1);
			switch (*input.begin())
			{
			case '1':
				state = setShipsRandomlyState;
				break;
			case '2':
				state = setShipsByHandState;
				break;
			default:
				view->setMessage("There is no such operation! Try again:\n");
				break;
			}
			break;
		}
		case setShipsRandomlyState:
		{
			while ((player[0] = setShipsRandomly()) == nullptr);
			view->printRandomizationComputerShipsLocation();
			while ((player[1] = setShipsRandomly()) == nullptr);
			std::cout << "Every single ship is placed... get ready to play!";
			Sleep(2000);
			state = playState;
			break;
		}
		case setShipsByHandState:
		{
			while ((player[0] = setShipsByHand()) == nullptr);
			view->printRandomizationComputerShipsLocation();
			while ((player[1] = setShipsRandomly()) == nullptr);
			std::cout << "Every single ship is placed... get ready to play!";
			Sleep(2000);
			state = playState;
			break;
		}
		case playState:
		{
			view->printPlayingBoards(player[0]->getBoardConvertedToCharTable(), player[1]->getEnemyBoardConvertedToCharTable());
			view->printShipsLeft(player[1]->getNumberOfXMastedShips(), player[1]->getMaxNumberOfMasts());
			if (whoseTour == 0)
			{
				if (!playerShoot())
					whoseTour = Tour::computer;

				if (!player[1]->isAnyShipAlive())
				{
					playerWon = true;
					state = endGameState;
				}
			}
			else
			{
				if (!computerShoot())
					whoseTour = Tour::player;

				if (!player[0]->isAnyShipAlive())
				{
					playerWon = false;
					state = endGameState;
				}
			}
			break;
		}
		case endGameState:
		{
			view->printPlayingBoards(player[0]->getBoardConvertedToCharTable(), player[1]->getEnemyBoardConvertedToCharTable());
			if (playerWon)
				view->printPlayerWon();
			else
				view->printComputerWon();
			Sleep(3000);
			state = finishGameState;
			break;
		}
		case finishGameState:
		{
			delete player[0];
			delete player[1];
			state = menuState;
			break;
		}
		case pauseState:
		{
			wasEscapePressed = false;
			view->printPause();
			auto input = readInput(1);
			switch (*input.begin())
			{
			case '1':
				state = playState;
				break;
			case '2':
				state = saveGameState;
				break;
			case '3':
				state = finishGameState;
				break;
			default:
				view->setMessage("There is no such operation! Try again:\n");
			}
			break;
		}
		case exitState:
		{
			view->printExit();
			close = true;
			break;
		}
		default:
		{
			view->printToBeDone();
		}
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

bool Engine::computerShoot() //completely random shot
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
		if (wasEscapePressed)
		{
			state = pauseState;
			return true;
		}
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
		if ((inp >= '0' && inp <= '9') || (inp == 'h' || inp == 'v') || inp == 27) //27 == ESC
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
		if (inp == 27 && state == playState)
		{
			wasEscapePressed = true;
			inputList.push_back(inp);
			return inputList;
		}
	}
	return inputList;
}

std::string Engine::makeSavedGamePath(std::string path)
{
	if (path.find(".save") == std::string::npos)
	{
		path += ".save";
	}
	return ".\\savegames\\" + path;
}

std::list<std::string>* Engine::getListOfSaveGames()
{
	std::list<std::string>* savegames = new std::list<std::string>();
	std::string path = ".\\savegames";
	std::string ext = ".save";
	namespace fs = std::filesystem;
	if (!fs::exists(path))
		fs::create_directory(path);

	for (fs::directory_iterator itr(path); itr != fs::directory_iterator(); ++itr)
	{
		if (itr->path().extension() == ext)
			savegames->push_back(itr->path().stem().string());
	}
	return savegames;
}

bool Engine::saveGame(std::string nameOfFile)
{
	if (!std::filesystem::exists(std::filesystem::path(".\\savegames")))
	{
		std::filesystem::create_directories(std::filesystem::path(".\\savegames"));
	}
	std::ofstream file;
	file.open((makeSavedGamePath(nameOfFile)).c_str());

	if (!file.good())
		return false;

	//liczba masztow najwiekszego zestatkow + czyja tura
	file << maxNumberOfMasts << " " << whoseTour << "\n";
	for (int i = 0; i < 2; i++)
	{
		//ktory gracz jest zapisywany
		file << i << "\n";

		//zapisywanie statkow (w kolejnosci z listy) -> 1;2 5;h  / 1;1 2;v
		auto ships = player[i]->getShips();
		for (std::list<Ship*>::iterator it = ships.begin(); it != ships.end(); it++)
		{
			Coordinates startCoords = (*it)->getStartCoords();
			Orientation orientation = (*it)->getOrientation();
			file << (*it)->getNumberOfMasts()
				<< ";" << startCoords.x << " " << startCoords.y
				<< ";" << ((orientation == Orientation::horizontal) ? 'h' : 'v');
			file << "\n";
		}

		//zapisywanie boardu z pominieciem unableToSet oraz Free BoxStateow
		int which = (i == 0 ? 1 : 0);
		auto board = player[which]->getBoardConvertedToCharTable();
		for (int y = 0; y < player[0]->getBoardSize(); y++)
		{
			for (int x = 0; x < player[0]->getBoardSize(); x++)
			{
				file << board[x][y];
			}
			file << "\n";
		}
	}
	if (file.good())
	{
		file.close();
		return true;
	}
	else
	{
		file.close();
		return false;
	}
}

bool Engine::loadGame(std::string nameOfFile)
{
	if (!std::filesystem::exists(std::filesystem::path(".\\savegames")))
	{
		std::filesystem::create_directories(std::filesystem::path(".\\savegames"));
	}
	std::ifstream file;
	file.open(makeSavedGamePath(nameOfFile).c_str());

	if (!file.good())
		return false;

	std::string line;
	std::getline(file, line); //to moze sprawic problem
	maxNumberOfMasts = line[0] - '0';
	whoseTour = ((line[2] == '0') ? Tour::player : Tour::computer);

	bool shotsOnBoard[10][10][2] = { false };

	for (int i = 0; i < 2; i++)
	{
		player[i] = new Model(maxNumberOfMasts);
		std::getline(file, line);
		int numOfPlayer = std::stoi(line);
		float numOfShips = (((float)maxNumberOfMasts + 1) / 2) * (float)maxNumberOfMasts;
		for (int h = 0; h < numOfShips; h++)
		{
			std::getline(file, line);
			int numberOfMasts = line[0] - '0';
			Coordinates coords = { line[2] - '0', line[4] - '0' };
			Orientation orientation = (line[6] == 'v' ? vertical : horizontal);
			player[i]->addShipToList(coords, orientation, numberOfMasts);
		}

		int which = ((i == 0) ? 1 : 0);
		for (int y = 0; y < 10; ++y)
		{
			std::getline(file, line);
			for (int x = 0; x < 10; ++x)
			{
				if (line[x] == 'h' || line[x] == 'd' || line[x] == 'o')
					shotsOnBoard[x][y][which] = true;
			}
		}
	}
	for (int i = 0; i < 2; i++)
	{
		for (int y = 0; y < 10; ++y)
		{
			std::getline(file, line);
			for (int x = 0; x < 10; ++x)
			{
				if (shotsOnBoard[x][y][i])
					player[i]->receiveShot({ x, y });
			}
		}
	}
	return true;
}