#include "Box.h"

Box::Box()
{
	state = BoxState::free;
	owner = nullptr;
}

Box::~Box()
{
	owner = nullptr;
}

BoxState Box::getState()
{
	return state;
}

void Box::setState(BoxState s)
{
	state = s;
}

Ship* Box::getOwner()
{
	return owner;
}

void Box::setOwner(Ship* ship)
{
	owner = ship;
}
