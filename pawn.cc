#include "pawn.h"
using namespace std;

Pawn::Pawn(string color, int row, int col):Chess{color, row, col}, 
firstMove{true}, canMove{true}{
	if(color == "black"){
		type = 'p';
	} else {
		type = 'P';
	}
}

void Pawn::setFirstMove(){
	firstMove = false;
}

void Pawn::setCanMove(){
	canMove = false;
}

bool Pawn::legalMove(int r, int c){
	if (r < 0 or c < 0 or r > 7 or c > 7){
		return false;
	}
	if(firstMove and canMove){
		if (Chess::color == "black"){
			if (c == Chess::col and ((r == Chess::row + 2) or (r == Chess::row + 1)) ){
				return true;
			} else {
				return false;
			}
		} else {
			if (c == Chess::col and ((r == Chess::row - 2) or (r == Chess::row - 1))){
				return true;
			} else {
				return false;
			}
		}
	} else if (canMove == true){
		if (Chess::color == "black"){
			if (c == Chess::col and r == Chess::row + 1){
				return true;
			} else {
				return false;
			}
		} else {
			if (c == Chess::col and r == Chess::row - 1){
				return true;
			} else {
				return false;
			}
		}
	} else {
		return false;
	}
}

char Pawn::getType(){
	return type;
}
