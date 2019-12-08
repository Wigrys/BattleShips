#pragma once

#include "BoxState.h"
class Ship;

class Box
{
private:
	BoxState state;
	Ship* owner;

public:
	Box();
	~Box();
	BoxState getState();
	void setState(BoxState);
	Ship* getOwner();
	void setOwner(Ship*);
};

