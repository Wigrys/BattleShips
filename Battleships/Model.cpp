#include "Model.h"

Model::Model()
{
	board = new Board();
	ships = new Ship*[maxNumberOfMasts];
}

Model::~Model()
{
	delete board;
	delete ships;
}