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


	return 0;
}
