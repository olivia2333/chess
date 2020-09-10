#include "knight.h"
using namespace std;

Knight::Knight(string color, int row, int col):Chess{color, row, col}{
	if(color == "black"){
		type = 'n';
	} else {
		type = 'N';
	}
}

bool Knight::legalMove(int r, int c){
	if (r < 0 or c < 0 or r > 7 or c > 7){
		return false;
	}
	if (((r - Chess::row == 2) or (r - Chess::row == -2)) and 
		((c - Chess::col == 1) or (c - Chess::col == -1))){
		return true;
	} else if (((r - Chess::row == 1) or (r - Chess::row == -1)) and 
		((c - Chess::col == 2) or (c - Chess::col == -2))){
		return true;
	} else {
		return false;
	}
}

char Knight::getType(){
	return type;
} 
