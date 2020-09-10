#ifndef PAWN_H
#define PAWN_H
#include "chess.h"

class Pawn: public Chess {
	char type;
	bool firstMove;
	bool canMove;

public:
	Pawn(std::string, int, int);
	void setFirstMove();
	void setCanMove();
	bool legalMove(int, int) override;
	char getType() override;
};

#endif
