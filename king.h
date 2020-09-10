#ifndef KING_H
#define KING_H
#include "chess.h"

class King: public Chess{
	char type;
	bool firstMove;

public:
	King(std::string, int, int);
	bool legalMove(int, int) override;
	void setFirstMove();
	char getType() override;
	bool if_firstmv();
};

#endif
