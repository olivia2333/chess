#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <iostream>
#include "window.h"
#include "observer.h"
#include "subject.h"
#include "info.h"
#include "scoreBoard.h"
class Xwindow;

class GraphicsDisplay:  public Observer{
	const int windowLen; // window length
	const int cellLen;	// length of each cell
	Xwindow win; // window of the graphics display
public:
	GraphicsDisplay(int windowLen, int gridSize); // ctor
	void notify(Subject &);
	void reset();
	void drawNotice(std::string step);
	void displayScore(ScoreBoard&);
};

#endif
