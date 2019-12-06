#include <iostream>
#include "Engine.h"
#include "Box.h"

int main()
{
	//Engine a;
	//a.run();

	Box **tablica = new Box*[10];
	for (int i = 0; i < 10; i++)
	{
		*tablica = new Box();
	}

	Box* tab[3];
	tab[0] = &tablica[0][1];
	tab[1] = &tablica[0][2];
	tab[2] = &tablica[0][3];

	return 0;
}
