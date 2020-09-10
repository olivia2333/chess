#ifndef ROOK_H
#define ROOK_H
#include "chess.h"

class Rook: public Chess{
	char type;
	bool firstMove;

public:
	Rook(std::string, int, int);
	bool legalMove(int, int) override;
	void setFirstMove();
	char getType() override;
	bool if_firstmv();
};

#endif
