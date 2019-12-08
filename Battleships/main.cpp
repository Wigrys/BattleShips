#include <iostream>
#include "Engine.h"
#include "Box.h"
#include "Ship.h"

int main()
{
	/*Engine a;
	a.run();*/
	/*Model* model = new Model();
	View* view = new View();
	view->printBoardAsCharTable(model->getBoardConvertedToCharTable(), 10);*/

	Board* b = new Board();
	Coordinates c = { 1, 1 };
	Orientation o = Orientation::horizontal;
	int n = 3;
	
	return 0;
}
