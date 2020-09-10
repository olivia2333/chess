#ifndef SCORE_H
#define SCORE_H
#include <iostream>
#include <string>

class ScoreBoard{
	float whiteScore;
	float blackScore;

public:
	ScoreBoard();
	void changeScore(std::string); // whiteCheckmate, blackCheckmate, draw, blackResign, whiteResign

	friend std::ostream &operator<<(std::ostream &out, const ScoreBoard &s); 
	friend class GraphicsDisplay;
};

#endif
