#include <iostream>
#include <time.h>
#include "Engine.h"
#include "Box.h"
#include "Ship.h"
#include "AI.h"

int main()
{
	/*int maxNumberOfMasts = 4;
	int* numberOfXMastedShips = new int[maxNumberOfMasts];
	for (int i = 0; i < maxNumberOfMasts; i++)
		numberOfXMastedShips[i] = 0;
	AI* x = new AI(maxNumberOfMasts, numberOfXMastedShips);
	x->shot();
	return 0;*/
	srand(time(NULL));
	Engine* a = new Engine();
	a->run();
	return 0;
}

