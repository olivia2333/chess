#include "rook.h"
using namespace std;

Rook::Rook(string color, int row, int col): Chess{color, row, col}, firstMove{true}{
	if(color == "black"){
		type = 'r';
	} else {
		type = 'R';
	}
}

bool Rook::legalMove(int r, int c){
	if (r < 0 or c < 0 or r > 7 or c > 7){
		return false;
	}
	if (r == Chess::row and c != Chess::col){
		return true;
	} else if (r != Chess::row and c == Chess::col){
		return true;
	} else {
		return false;
	}
}

void Rook::setFirstMove(){
	firstMove = false;
}

char Rook::getType(){
	return type;
}
bool Rook::if_firstmv(){
	return firstMove;
}
