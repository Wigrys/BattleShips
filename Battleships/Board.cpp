#include "Board.h"

Board::Board()
{
	board = new Box*[size];
	for (int i = 0; i < size; i++)
	{
		board[i] = new Box[size];
	}
}

Board::~Board()
{
	for (int i = 0; i < size; ++i)
		delete[] board[i];
	delete[] board;
}