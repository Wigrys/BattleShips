#include <iostream>
#include <time.h>
#include "Engine.h"
#include "Box.h"
#include "Ship.h"

int main()
{
	srand((unsigned)time(NULL));
	Engine* a = new Engine();
	a->run();
	return 0;
}

