#include "scoreBoard.h"
using namespace std;

ScoreBoard::ScoreBoard():whiteScore{0}, blackScore{0}{}

void ScoreBoard::changeScore(string type){
	if (type == "whiteCheckmate"){
		blackScore++;
	} else if (type == "blackCheckmate"){
		whiteScore++;
	} else if (type == "draw"){
		blackScore += 0.5;
		whiteScore += 0.5;
	} else if (type == "blackResign") {
		whiteScore++;
	} else if (type == "whiteResign") {
		whiteScore++;
	}
}

ostream &operator<<(std::ostream &out, const ScoreBoard &s){
	out << "Final Score:" << endl;
	out << "White: " << s.whiteScore << endl;
	out << "Black: " << s.blackScore << endl;
	return out;
}
