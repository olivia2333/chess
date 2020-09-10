#ifndef Player_H
#define Player_H
#include <vector>
#include "move.h"
#include "board.h"

class Player {
public:
	bool isWhite;
	bool isAI;

	Player();
	Player(bool, bool);

	virtual Move makeMove(Board&);
	virtual ~Player();
};

#endif
