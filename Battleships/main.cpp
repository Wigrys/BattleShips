#include <iostream>
#include "Engine.h"
#include "Box.h"
#include "Ship.h"

int main()
{
	//Engine a;
	//a.run();
	Model* test = new Model();
	char** tableOfChars = test->getBoardConvertedToCharTable();
	for (int i = 0; i < 10; i++)
	{
		for (int h = 0; h < 10; h++)
		{
			std::cout << tableOfChars[i][h] << " ";
		}
		std::cout << std::endl;
	}

	return 0;
}
