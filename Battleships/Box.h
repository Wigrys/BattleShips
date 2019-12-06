#pragma once
#include "Ship.h"

enum class State
{
	free,
	set,
	unableToSet,
	hit,
	down
};


class Box
{
private:
	State state;
	Ship* owner;

public:
	Box();
	~Box();
	State getState();
	void setState(State);
	Ship* getOwner();
};

