#include "Box.h"

Box::Box()
{
	state = State::free;
	owner = nullptr;
}

Box::~Box()
{
	delete owner;
}

State Box::getState()
{
	return state;
}

void Box::setState(State s)
{
	state = s;
}

Ship* Box::getOwner()
{
	return owner;
}
