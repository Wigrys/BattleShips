#pragma once
#include "Box.h"

using namespace std;

class Board
{
private:
	const int size = 10;
	Box** board;

public:
	Board();
	~Board();
};

