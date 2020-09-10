#include "chess.h"
using namespace std;

Chess::Chess(string color, int row, int col): color{color}, row{row}, col{col}{}

bool Chess::if_firstmv(){return false;}
void Chess::setFirstMove(){}

Chess::~Chess(){}
