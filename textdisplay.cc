#include <sstream>
#include "textdisplay.h"

using namespace std;

// ctor
TextDisplay::TextDisplay(){
	theDisplay.clear();

	for (int i = 0; i < 8; i++){
		vector<char> row;
		for (int j = 0; j < 8; j++) {
			if (i == 0){
				if (j == 0 or j == 7){
					row.emplace_back('r');
				} else if (j == 1 or j == 6){
					row.emplace_back('n');
				} else if (j == 2 or j == 5){
					row.emplace_back('b');
				} else if (j == 3) {
					row.emplace_back('q');
				} else {
					row.emplace_back('k');
				}
			} else if (i == 1){
				row.emplace_back('p');
			} else if (i == 6){
				row.emplace_back('P');
			} else if (i == 7){
				if (j == 0 or j == 7){
					row.emplace_back('R');
				} else if (j == 1 or j == 6){
					row.emplace_back('N');
				} else if (j == 2 or j == 5){
					row.emplace_back('B');
				} else if (j == 3) {
					row.emplace_back('Q');
				} else {
					row.emplace_back('K');
				}
			} else if ((i % 2 == 0 and j % 2 == 0) or 
						(i % 2 != 0 and j % 2 != 0)){
				row.emplace_back(' ');
			} else {
				row.emplace_back('_');
			}
		}
		theDisplay.emplace_back(row);
	}
}

bool TextDisplay::valid(){
	int whiteKing = 0;
	int blackKing = 0;

	for (int i = 0; i < 8; i++){
		for (int j = 0; j < 8; j++){
			if (i == 0 or i == 7) {
				if (theDisplay[i][j] == 'p' or theDisplay[i][j] == 'P') {
					return false;
				}
			}
			if (theDisplay[i][j] == 'K'){
				if (whiteKing == 1){
					return false;
				} else {
					whiteKing ++;
				}
			} 
			if (theDisplay[i][j] == 'k'){
				if (blackKing == 1){
					return false;
				} else {
					blackKing ++;
				}
			}
		}
	}

	if (blackKing == 1 and whiteKing == 1){
		return true;
	} else {
		return false;
	}
}


void TextDisplay::notify(Subject &board){	
	InfoType i = board.getState();
	string type = i.type;
	char piece = i.piece;
	int startR = i.startR;
	int startC = i.startC;
	int endR = i.endR;
	int endC = i.endC;

	if (type == "set"){
		if (startC < 8 and startC >= 0 and startR >= 0 and startR < 8){
			if (piece == '-'){
				if ((startC % 2 == 0 and startR % 2 == 0) or
					(startC % 2 != 0 and startR % 2 != 0)) {
					theDisplay[startR][startC] = ' ';
				} else {
					theDisplay[startR][startC] = '_';
				}
			} else {
				theDisplay[startR][startC] = piece;
			}
		}
	} else if (type == "move"){
		theDisplay[endR][endC] = piece;
		if ((startC % 2 == 0 and startR % 2 == 0) or
			(startC % 2 != 0 and startR % 2 != 0)) {
			theDisplay[startR][startC] = ' ';
		} else {
			theDisplay[startR][startC] = '_';
		}
	} else if (type == "enPassant"){
		theDisplay[endR][endC] = piece;
		if ((startC % 2 == 0 and startR % 2 == 0) or
			(startC % 2 != 0 and startR % 2 != 0)) {
			theDisplay[startR][startC] = ' ';
		} else {
			theDisplay[startR][startC] = '_';
		}
		if ((endC % 2 == 0 and startR % 2 == 0) or
			(endC % 2 != 0 and startR % 2 != 0)) {
			theDisplay[startR][endC] = ' ';
		} else {
			theDisplay[startR][endC] = '_';
		}
	} else if (type == "castling"){
		int casSR = i.casSR;
        int casSC = i.casSC;
        int casER = i.casER;
        int casEC = i.casEC;
		theDisplay[endR][endC] = piece;
		if ((startC % 2 == 0 and startR % 2 == 0) or
			(startC % 2 != 0 and startR % 2 != 0)) {
			theDisplay[startR][startC] = ' ';
		} else {
			theDisplay[startR][startC] = '_';
		}
		if(islower(piece)){
			theDisplay[casER][casEC] = 'r';
		} else {
			theDisplay[casER][casEC] = 'R';
		}
		if ((casSR % 2 == 0 and casSC % 2 == 0) or
			(casSR % 2 != 0 and casSC % 2 != 0)) {
			theDisplay[casSR][casSC] = ' ';
		} else {
			theDisplay[casSR][casSC] = '_';
		}
	}
}

// operator<<(out, td) prints the textdisplay
ostream &operator<<(std::ostream &out, const TextDisplay &td) {
	for(int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++){
			out << (td.theDisplay)[i][j];
		}
		out << endl;
	}
	return out;
}
