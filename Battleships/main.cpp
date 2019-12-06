#include <iostream>
#include "Engine.h"
#include "Box.h"
#include "Ship.h"

int main()
{
	//Engine a;
	//a.run();
	Box **tablica = new Box*[10];
	for (int i = 0; i < 10; i++)
	{
		tablica[i] = new Box[10];
		for (int h = 0; h < 10; h++)
		{
			tablica[i][h] = Box();
		}
	} 
	Box* tab[2];
	tab[0] = &tablica[0][1];
	tab[1] = &tablica[0][2];

	if (tablica[0][1].getState() == BoxState::free)
		std::cout << "free";

	Ship* stateczek = new Ship(2, tab);
	stateczek->setOwnedBoxesState(BoxState::hit);

	if (tablica[0][1].getState() == BoxState::hit)
		std::cout << "hit";

	return 0;
}
