#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <vector>
#include "textdisplay.h"
#include "GraphicsDisplay.h"
#include "chess.h"
#include "move.h"
class TextDisplay;

class Board : public Subject
{
  std::vector<std::vector<Chess *>> board;
  TextDisplay *td = nullptr;
  Observer* graphics = nullptr;

  int whiteKingR;
  int whiteKingC;
  int blackKingR;
  int blackKingC;

  bool firstPlay;

  std::vector<Move> whitePos;
  std::vector<Move> blackPos;
  std::vector<Move> wEnPassant;
  std::vector<Move> bEnPassant;

public:
  Board();
  bool valid(); // check if the initial board is valid
  
  //bool makeMove(); // check if the move is legal
  void set(char, int, int); // update board
  void setObserver(Observer*);
  //底下的bool white 就输入 true
  std::vector<Move> generateMove(bool);                    // generate all possible moves
  std::vector<Move>& castlingMove(std::vector<Move>&, bool); // generate king-rook castling move
  std::vector<Move>& legalizeMove(std::vector<Move>&, bool);
  bool testCheckOpponent(Move);
  
  
  void makeMove(char, int, int, int, int);
  void movePiece(int, int, int, int);
  bool whiteChecked(int, int); // check if whiteKing is checked
  bool blackChecked(int, int); // check if blackKing is checked
  bool testmove(Move, bool);
  bool whiteCheckmate();       // check if whiteKing is checkmated
  bool blackCheckmate();       // check if blackKing is checkmated


  void printpossiblemove();
  ~Board();

  friend std::ostream &operator<<(std::ostream &out, const Board &b);
};

#endif
