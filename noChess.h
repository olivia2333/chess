#ifndef NOCHESS_H
#define NOCHESS_H
#include "chess.h"

class noChess: public Chess{
	char type;

public:
	noChess(std::string, int, int);

	bool legalMove(int row, int col) override;

	char getType() override;

};

#endif
