#pragma once
#include "Box.h"

using namespace std;

class Board
{
private:
	const int size = 10;
	Box** tableOfBoxes;
public:
	Board();
	~Board();
	int getSize();
	Box** getTableOfBoxes();
};

