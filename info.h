#ifndef INFO_H
#define INFO_H
#include <string>

struct InfoType{
  std::string type; //enPassant, move, set, castling
  char piece;
  int startR;
  int startC;
  int endR;
  int endC;
  int casSR;
  int casSC;
  int casER;
  int casEC;
};

#endif
