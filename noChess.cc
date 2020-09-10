#include "noChess.h"
using namespace std;

noChess::noChess(string color, int row, int col):Chess{color, row, col}{
	if(color == "black"){
		type = 'e';
	} else {
		type = 'E';
	}
}

bool noChess::legalMove(int start, int end){
	return false;
}

char noChess::getType(){
	return type;
}
