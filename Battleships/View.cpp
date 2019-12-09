#include "View.h"

View::View()
{
}

void View::setMessage(std::string sentMessage)
{
	message = sentMessage;
}

void View::printMenu()
{
	system("cls");
	std::cout << "1. START GAME \n"
		<< "2. LOAD GAME \n"
		<< "0. EXIT\n";
	printMessage();
}

void View::printLoadGame()
{
	system("cls");
	std::cout << "To be done";
}

void View::printExit()
{
	system("cls");
	std::cout << "Bye.\n";
}

void View::printSetShips()
{
	system("cls");
	std::cout << "How u want to fill your board?\n"
		<< "(1)randomly or (2)by hand?\n";
}

void View::printSetShipsRandomly()
{
	system("cls");
}
void View::printSetShipsByHand()
{
	system("cls");
}

void View::printSetXMastedShip(int x)
{
	system("cls");
	std::cout << "Please enter coordinates (first x, then y)\nand orientation (horizontal [h]/vertical [v])\nof your " << x << " masted ship:\n";
}

void View::printBoardAsCharTable(char** board, int size)
{
	for (int i = 0; i < size; i++)
	{
		if (i == 0)
		{
			std::cout << " ";
			for (int k = 0; k < size; k++)
				std::cout << " " << k;
			std::cout << "\n";
		}
		for (int h = 0; h < size; h++)
		{
			if (h == 0)
				std::cout << i;
			std::cout << " " << board[h][i]; // wypisywanie dziwnie dziala, nie wiem czemu ale jak jest tak to jest dobrze, a jakby bylo [i][h] to zle
		}
		std::cout << std::endl;
	}
}

void View::printMessage()
{
	if (message != "")
	{
		std::cout << std::endl;
		std::cout << message;
		message = "";
	}
}