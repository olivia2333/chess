#include "queen.h"
using namespace std;

Queen::Queen(string color, int row, int col):Chess{color, row, col}{
	if(color == "black"){
		type = 'q';
	} else {
		type = 'Q';
	}
}

bool Queen::legalMove(int r, int c){
	if (r < 0 or c < 0 or r > 7 or c > 7){
		return false;
	}
	if (((r - Chess::row == c - Chess::col) or (Chess::row - r == c - Chess::col)) and 
		(r - Chess::row != 0)){
		return true;
	} else if (r == Chess::row and c - Chess::col != 0){
		return true;
	} else if (c == Chess::col and r - Chess::row != 0){
		return true;
	} else {
		return false;
	}
}

char Queen::getType(){
	return type;
} 
