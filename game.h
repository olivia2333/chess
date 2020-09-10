#ifndef GAME_H
#define GAME_H
#include "board.h"
#include "player.h"
#include "AIplayer.h"
#include "move.h"
#include <iostream>
#include <string>

class Board;
class Observer;

class Game{
	Board *board;
	Player* players[2];
	std::string status;
	Player* current;

public:
	Game();
	void setPlayers(char, int);
	void reset();
	bool currentAI();
	bool currentWhite();
	void AImove();
	std::string getStatus();
	void setStatus(std::string);
	void set(char, std::string);
	void setObserver(Observer *ob);
	bool valid();
	void kingChecked();
	void makeMove(int, int, int, int);
	void makeMove(std::string, std::string);
	bool canMove();
	~Game();

	friend std::ostream &operator<<(std::ostream &out, const Game &g);

//	void printPos();
};

#endif
