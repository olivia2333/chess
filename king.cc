#include "king.h"
using namespace std;

King::King(string color, int row, int col) : Chess{color, row, col}, firstMove{true}
{
	if (color == "black")
	{
		type = 'k';
	}
	else
	{
		type = 'K';
	}
}

bool King::legalMove(int r, int c)
{
	if (r < 0 or c < 0 or r > 7 or c > 7)
	{
		return false;
	}
	else if (r == Chess::row - 1 or r == Chess::row + 1 or c == Chess::col - 1 or c == Chess::col + 1)
	{
		return true;
	}
	if (firstMove)
	{
		if ((r == Chess::row or c == Chess::row) and ((c == Chess::col + 2) or (c == Chess::col - 2)))
		{
			return true;
		}
		else if (((c == Chess::col + 2) or (c == Chess::col - 2)) and ((r == Chess::row + 2) or (r == Chess::row - 2)))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	else
	{
		return false;
	}
}
void King::setFirstMove()
{
	firstMove = false;
}

char King::getType()
{
	return type;
}

bool King::if_firstmv()
{
	return firstMove;
}
