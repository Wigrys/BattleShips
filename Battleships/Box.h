#pragma once
class Ship;

enum class BoxState
{
	free = 0,
	set,
	unableToSet,
	hit,
	down
};


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
};

