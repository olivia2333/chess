#ifndef CHESS_H
#define CHESS_H
#include <iostream>
#include <string>

class Chess {

protected:
	std::string color;
	int row;
	int col;

public:
	Chess(std::string, int, int);
	virtual bool legalMove(int, int) = 0;
	virtual char getType() = 0;
	virtual bool if_firstmv();
	virtual void setFirstMove();
	virtual ~Chess();
};

#endif
