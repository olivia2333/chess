#ifndef KNIGHT_H
#define KNIGHT_H
#include "chess.h"

class Knight: public Chess {
	char type;

public:
	Knight(std::string, int, int);

	bool legalMove(int row, int col) override;

	char getType() override;
};

#endif
