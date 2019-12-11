#include <iostream>
#include <time.h>
#include "Engine.h"
#include "Box.h"
#include "Ship.h"


int main()
{
	srand(time(NULL));
	Engine a;
	a.run();
		
	/*Model* player[2] = new Model();
	View* view = new View();
	view->printBoardAsCharTable(player[0]->getBoardConvertedToCharTable(), 10);
	player[0]->tempSetShip(Coordinates() = { 4,2 }, vertical, 3);

	std::cout << "\n\n";
	view->printBoardAsCharTable(player[0]->getBoardConvertedToCharTable(), 10);*/
	return 0;
}