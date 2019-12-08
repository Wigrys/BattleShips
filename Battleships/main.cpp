#include <iostream>
#include "Engine.h"
#include "Box.h"
#include "Ship.h"

int main()
{
	/*Engine a;
	a.run();*/
		
	Model* model = new Model();
	View* view = new View();
	view->printBoardAsCharTable(model->getBoardConvertedToCharTable(), 10);
	model->tempSetShip(Coordinates() = { 5,0 }, vertical, 3);

	std::cout << "\n\n";
	view->printBoardAsCharTable(model->getBoardConvertedToCharTable(), 10);
	return 0;
}