#ifndef QUEEN_H
#define QUEEN_H
#include "chess.h"

class Queen: public Chess{
	char type;

public:
	Queen(std::string, int, int);

	bool legalMove(int row, int col) override;

	char getType() override;
};

#endif
