#include "board.h"
#include "bishop.h"
#include "king.h"
#include "knight.h"
#include "noChess.h"
#include "pawn.h"
#include "queen.h"
#include "rook.h"
#include <cctype>
#include <sstream>
using namespace std;

Board::Board() : whiteKingR{7}, whiteKingC{4}, blackKingR{0}, blackKingC{4}, firstPlay{true}
{
  delete td;
  td = new TextDisplay{};
  attach(td);
  for (int i = 0; i < 8; i++)
  {
    vector<Chess *> row;
    for (int j = 0; j < 8; j++)
    {
      if (i == 0)
      {
        if (j == 0 or j == 7)
        {
          row.emplace_back(new Rook{"black", i, j});
        }
        else if (j == 1 or j == 6)
        {
          row.emplace_back(new Knight{"black", i, j});
        }
        else if (j == 2 or j == 5)
        {
          row.emplace_back(new Bishop{"black", i, j});
        }
        else if (j == 3)
        {
          row.emplace_back(new Queen{"black", i, j});
        }
        else
        {
          row.emplace_back(new King{"black", i, j});
        }
      }
      else if (i == 1)
      {
        row.emplace_back(new Pawn{"black", i, j});
      }
      else if (i == 6)
      {
        row.emplace_back(new Pawn{"white", i, j});
      }
      else if (i == 7)
      {
        if (j == 0 or j == 7)
        {
          row.emplace_back(new Rook{"white", i, j});
        }
        else if (j == 1 or j == 6)
        {
          row.emplace_back(new Knight{"white", i, j});
        }
        else if (j == 2 or j == 5)
        {
          row.emplace_back(new Bishop{"white", i, j});
        }
        else if (j == 3)
        {
          row.emplace_back(new Queen{"white", i, j});
        }
        else
        {
          row.emplace_back(new King{"white", i, j});
        }
      }
      else if ((i % 2 == 0 and j % 2 == 0) or
               (i % 2 != 0 and j % 2 != 0))
      {
        row.emplace_back(new noChess{"black", i, j});
      }
      else
      {
        row.emplace_back(new noChess{"white", i, j});
      }
    }
    board.emplace_back(row);
  }
}

void Board::setObserver(Observer *ob)
{
  graphics = ob;
  attach(ob);
}

bool Board::whiteChecked(int whiteKingR, int whiteKingC)
{
  if (this->whiteKingR == whiteKingR and this->whiteKingC == whiteKingC)
  {
    int size = blackPos.size();
    for (int i = 0; i < size; i++)
    {
      if (whiteKingR == blackPos[i].endR and whiteKingC == blackPos[i].endC)
      {
        return true;
      }
    }
    return false;
  }
  else
  {
    Chess *temp = new noChess{"white", this->whiteKingR, this->whiteKingC};
    swap(board[this->whiteKingR][this->whiteKingC], board[whiteKingR][whiteKingC]);
    swap(temp, board[this->whiteKingR][this->whiteKingC]);
    blackPos.clear();
    blackPos = generateMove(false);
    blackPos = castlingMove(blackPos, false);
    int size = blackPos.size();
    for (int i = 0; i < size; i++)
    {
      if (whiteKingR == blackPos[i].endR and whiteKingC == blackPos[i].endC)
      {
        swap(board[this->whiteKingR][this->whiteKingC], board[whiteKingR][whiteKingC]);
        swap(temp, board[whiteKingR][whiteKingC]);
        delete temp;
        return true;
      }
    }
    swap(board[this->whiteKingR][this->whiteKingC], board[whiteKingR][whiteKingC]);
    swap(temp, board[whiteKingR][whiteKingC]);
    delete temp;
    return false;
  }
}

bool Board::blackChecked(int blackKingR, int blackKingC) //black being checked
{
  if (this->blackKingR == blackKingR and this->blackKingC == blackKingC)
  {
    int size = whitePos.size();
    for (int i = 0; i < size; i++)
    {
      if (blackKingR == whitePos[i].endR and blackKingC == whitePos[i].endC)
      {
        return true;
      }
    }
    return false;
  }
  else
  {
    Chess *temp = new noChess{"white", this->blackKingR, this->blackKingC};
    swap(board[this->blackKingR][this->blackKingC], board[blackKingR][blackKingC]);
    swap(temp, board[this->blackKingR][this->blackKingC]);
    whitePos.clear();
    whitePos = generateMove(true);
    whitePos = castlingMove(whitePos, true);
    int size = whitePos.size();
    for (int i = 0; i < size; i++)
    {
      if (blackKingR == whitePos[i].endR and blackKingC == whitePos[i].endC)
      {
        swap(board[this->blackKingR][this->blackKingC], board[blackKingR][blackKingC]);
        swap(temp, board[blackKingR][blackKingC]);
        delete temp;
        return true;
      }
    }
    swap(board[this->blackKingR][this->blackKingC], board[blackKingR][blackKingC]);
    swap(temp, board[blackKingR][blackKingC]);
    delete temp;
    return false;
  }
}

bool Board::blackCheckmate()
{
  int size = blackPos.size();
  for (int i = 0; i < size; i++)
  {
    if (blackPos[i].startR == blackKingR and blackPos[i].startC == blackKingC)
    {
      if (!blackChecked(blackPos[i].endR, blackPos[i].endC))
      {
        return false;
      }
    }
    else
    {
      if (testmove(blackPos[i], false))
      {
        return false;
      }
    }
  }
  return true;
}
bool Board::whiteCheckmate()
{
  int size = whitePos.size();
  for (int i = 0; i < size; i++)
  {
    if (whitePos[i].startR == whiteKingR and whitePos[i].startC == whiteKingC)
    {
      if (!whiteChecked(whitePos[i].endR, whitePos[i].endC))
      {
        return false;
      }
    }
    else
    {
      if (testmove(whitePos[i], true))
      {
        return false;
      }
    }
  }
  return true;
}

bool Board::testCheckOpponent(Move this_move)
{
  int startR = this_move.startR;
  int startC = this_move.startC;
  int endR = this_move.endR;
  int endC = this_move.endC;
  char curr_type = board[startR][startC]->getType();
  bool black = islower(curr_type);
  char curr = tolower(curr_type);
  bool result;
  Chess *tempS = nullptr;

  // normal move
  if ((curr == 'p' and endC == startC) or (curr != 'k' and curr != 'p'))
  {
    tempS = new noChess{"black", startR, startC};
    swap(board[startR][startC], board[endR][endC]);
    swap(tempS, board[startR][startC]);
    if (black)
    {
      blackPos.clear();
      blackPos = generateMove(false);
      blackPos = legalizeMove(castlingMove(blackPos, false), false);
      if (whiteChecked(whiteKingR, whiteKingC))
      {
        result = true;
      }
      else
      {
        result = false;
      }
    }
    else
    {
      whitePos.clear();
      whitePos = generateMove(true);
      whitePos = legalizeMove(castlingMove(whitePos, true), true);
      if (blackChecked(blackKingR, blackKingC))
      {
        result = true;
      }
      else
      {
        result = false;
      }
    }
    swap(board[startR][startC], board[endR][endC]);
    swap(tempS, board[endR][endC]);
    delete tempS;
    if (black)
    {
      blackPos.clear();
      blackPos = generateMove(false);
      blackPos = legalizeMove(castlingMove(blackPos, false), false);
    }
    else
    {
      whitePos.clear();
      whitePos = generateMove(true);
      whitePos = legalizeMove(castlingMove(whitePos, true), true);
    }
    return result;
  }
  else if (curr == 'p')
  {
    if (board[endR][endC]->getType() != 'e' and board[endR][endC]->getType() != 'E')
    {
      tempS = new noChess{"black", startR, startC};
      swap(board[startR][startC], board[endR][endC]);
      swap(tempS, board[startR][startC]);
      if (black)
      {
        blackPos.clear();
        blackPos = generateMove(false);
        blackPos = legalizeMove(castlingMove(blackPos, false), false);
        if (whiteChecked(whiteKingR, whiteKingC))
        {
          result = true;
        }
        else
        {
          result = false;
        }
      }
      else
      {
        whitePos.clear();
        whitePos = generateMove(true);
        whitePos = legalizeMove(castlingMove(whitePos, true), true);
        if (blackChecked(blackKingR, blackKingC))
        {
          result = true;
        }
        else
        {
          result = false;
        }
      }
      swap(board[startR][startC], board[endR][endC]);
      swap(tempS, board[endR][endC]);
      delete tempS;
      if (black)
      {
        blackPos.clear();
        blackPos = generateMove(false);
        blackPos = legalizeMove(castlingMove(blackPos, false), false);
      }
      else
      {
        whitePos.clear();
        whitePos = generateMove(true);
        whitePos = legalizeMove(castlingMove(whitePos, true), true);
      }
      return result;
    }
    else
    { // enpassant
      tempS = new noChess{"black", startR, startC};
      swap(board[endR][endC], board[startR][startC]);
      swap(tempS, board[startR][endC]);
      if (black)
      {
        blackPos.clear();
        blackPos = generateMove(false);
        blackPos = legalizeMove(castlingMove(blackPos, false), false);
        if (whiteChecked(whiteKingR, whiteKingC))
        {
          result = true;
        }
        else
        {
          result = false;
        }
      }
      else
      {
        whitePos.clear();
        whitePos = generateMove(true);
        whitePos = legalizeMove(castlingMove(whitePos, true), true);
        if (blackChecked(blackKingR, blackKingC))
        {
          result = true;
        }
        else
        {
          result = false;
        }
      }
      swap(board[endR][endC], board[startR][startC]);
      swap(tempS, board[startR][endC]);
      delete tempS;
      if (black)
      {
        blackPos.clear();
        blackPos = generateMove(false);
        blackPos = legalizeMove(castlingMove(blackPos, false), false);
      }
      else
      {
        whitePos.clear();
        whitePos = generateMove(true);
        whitePos = legalizeMove(castlingMove(whitePos, true), true);
      }
      return result;
    }
  }
  else if (curr == 'k')
  {
    if (startR - endR == 1 or startR - endR == -1 or startC - endC == 1 or startC - endC == -1)
    {
      tempS = new noChess{"black", startR, startC};
      swap(board[startR][startC], board[endR][endC]);
      swap(tempS, board[startR][startC]);
      if (black)
      {
        blackPos.clear();
        blackPos = generateMove(false);
        blackPos = legalizeMove(castlingMove(blackPos, false), false);
        if (whiteChecked(whiteKingR, whiteKingC))
        {
          result = true;
        }
        else
        {
          result = false;
        }
      }
      else
      {
        whitePos.clear();
        whitePos = generateMove(true);
        whitePos = legalizeMove(castlingMove(whitePos, true), true);
        if (blackChecked(blackKingR, blackKingC))
        {
          result = true;
        }
        else
        {
          result = false;
        }
      }
      swap(board[startR][startC], board[endR][endC]);
      swap(tempS, board[endR][endC]);
      delete tempS;
      if (black)
      {
        blackPos.clear();
        blackPos = generateMove(false);
        blackPos = legalizeMove(castlingMove(blackPos, false), false);
      }
      else
      {
        whitePos.clear();
        whitePos = generateMove(true);
        whitePos = legalizeMove(castlingMove(whitePos, true), true);
      }
      return result;
    }
    else
    { // castling
      if (endC - startC == 2 and endR == startR)
      {
        swap(board[endR][endC], board[startR][startC]);
        // find rook
        for (int i = endC + 1; i < 8; i++)
        {
          if ((black and board[endR][i]->getType() == 'r') or (!black and board[endR][i]->getType() == 'R'))
          {
            swap(board[endR][endC - 1], board[endR][i]);
            if (black)
            {
              blackPos.clear();
              blackPos = generateMove(false);
              blackPos = legalizeMove(castlingMove(blackPos, false), false);
            }
            else
            {
              whitePos.clear();
              whitePos = generateMove(true);
              whitePos = legalizeMove(castlingMove(whitePos, true), true);
            }
            if ((!black and blackChecked(blackKingR, blackKingC)) or (black and whiteChecked(whiteKingR, whiteKingC)))
            {
              result = true;
            }
            else
            {
              result = false;
            }
            swap(board[endR][endC - 1], board[endR][i]);
            break;
          }
        }
        swap(board[endR][endC], board[startR][startC]);
        if (black)
        {
          blackPos.clear();
          blackPos = generateMove(false);
          blackPos = legalizeMove(castlingMove(blackPos, false), false);
        }
        else
        {
          whitePos.clear();
          whitePos = generateMove(true);
          whitePos = legalizeMove(castlingMove(whitePos, true), true);
        }
        return result;
      }
      else if (startC - endC == 2 and endR == startR)
      {
        swap(board[endR][endC], board[startR][startC]);
        // find rook
        for (int i = endC - 1; i >= 0; i--)
        {
          if ((black and board[endR][i]->getType() == 'r') or (!black and board[endR][i]->getType() == 'R'))
          {
            swap(board[endR][endC + 1], board[endR][i]);
            if (black)
            {
              blackPos.clear();
              blackPos = generateMove(false);
              blackPos = legalizeMove(castlingMove(blackPos, false), false);
            }
            else
            {
              whitePos.clear();
              whitePos = generateMove(true);
              whitePos = legalizeMove(castlingMove(whitePos, true), true);
            }
            if ((!black and blackChecked(blackKingR, blackKingC)) or (black and whiteChecked(whiteKingR, whiteKingC)))
            {
              result = true;
            }
            else
            {
              result = false;
            }
            swap(board[endR][endC + 1], board[endR][i]);
            break;
          }
        }
        swap(board[endR][endC], board[startR][startC]);
        if (black)
        {
          blackPos.clear();
          blackPos = generateMove(false);
          blackPos = legalizeMove(castlingMove(blackPos, false), false);
        }
        else
        {
          whitePos.clear();
          whitePos = generateMove(true);
          whitePos = legalizeMove(castlingMove(whitePos, true), true);
        }
        return result;
      }
      else if (startR - endR == 2 and endC == startC)
      {
        swap(board[endR][endC], board[startR][startC]);
        for (int i = endR - 1; i >= 0; i--)
        {
          if ((black and board[i][endC]->getType() == 'r') or (!black and board[i][endC]->getType() == 'R'))
          {
            swap(board[endR + 1][endC], board[endR][i]);
            if (black)
            {
              blackPos.clear();
              blackPos = generateMove(false);
              blackPos = legalizeMove(castlingMove(blackPos, false), false);
            }
            else
            {
              whitePos.clear();
              whitePos = generateMove(true);
              whitePos = legalizeMove(castlingMove(whitePos, true), true);
            }
            if ((!black and blackChecked(blackKingR, blackKingC)) or (black and whiteChecked(whiteKingR, whiteKingC)))
            {
              result = true;
            }
            else
            {
              result = false;
            }
            swap(board[endR + 1][endC], board[endR][i]);
            break;
          }
        }
        swap(board[endR][endC], board[startR][startC]);
        if (black)
        {
          blackPos.clear();
          blackPos = generateMove(false);
          blackPos = legalizeMove(castlingMove(blackPos, false), false);
        }
        else
        {
          whitePos.clear();
          whitePos = generateMove(true);
          whitePos = legalizeMove(castlingMove(whitePos, true), true);
        }
        return result;
      }
      else if (startR - endR == -2 and endC == startC)
      {
        swap(board[endR][endC], board[startR][startC]);
        for (int i = endR + 1; i < 8; i++)
        {
          if ((black and board[i][endC]->getType() == 'r') or (!black and board[i][endC]->getType() == 'R'))
          {
            swap(board[endR - 1][endC], board[endR][i]);
            if (black)
            {
              blackPos.clear();
              blackPos = generateMove(false);
              blackPos = legalizeMove(castlingMove(blackPos, false), false);
            }
            else
            {
              whitePos.clear();
              whitePos = generateMove(true);
              whitePos = legalizeMove(castlingMove(whitePos, true), true);
            }
            if ((!black and blackChecked(blackKingR, blackKingC)) or (black and whiteChecked(whiteKingR, whiteKingC)))
            {
              result = true;
            }
            else
            {
              result = false;
            }
            swap(board[endR - 1][endC], board[endR][i]);
            break;
          }
        }
        swap(board[endR][endC], board[startR][startC]);
        if (black)
        {
          blackPos.clear();
          blackPos = generateMove(false);
          blackPos = legalizeMove(castlingMove(blackPos, false), false);
        }
        else
        {
          whitePos.clear();
          whitePos = generateMove(true);
          whitePos = legalizeMove(castlingMove(whitePos, true), true);
        }
        return result;
      }
      else if (endC > startC and endR != startR)
      { //castling
        swap(board[endR][endC], board[startR][startC]);
        bool find = false;
        // find rook
        for (int i = endR - 1; i >= 0; i--)
        {
          for (int j = endC + 1; j < 8; j++)
          {
            if ((black and board[i][j]->getType() == 'r') or (!black and board[i][j]->getType() == 'R'))
            {
              swap(board[endR + 1][endC - 1], board[i][j]);
              if (black)
              {
                blackPos.clear();
                blackPos = generateMove(false);
                blackPos = legalizeMove(castlingMove(blackPos, false), false);
              }
              else
              {
                whitePos.clear();
                whitePos = generateMove(true);
                whitePos = legalizeMove(castlingMove(whitePos, true), true);
              }
              find = true;
              if ((!black and blackChecked(blackKingR, blackKingC)) or (black and whiteChecked(whiteKingR, whiteKingC)))
              {
                result = true;
              }
              else
              {
                result = false;
              }
              swap(board[endR][endC], board[startR][startC]);
              swap(board[endR + 1][endC - 1], board[i][j]);
              if (black)
              {
                blackPos.clear();
                blackPos = generateMove(false);
                blackPos = legalizeMove(castlingMove(blackPos, false), false);
              }
              else
              {
                whitePos.clear();
                whitePos = generateMove(true);
                whitePos = legalizeMove(castlingMove(whitePos, true), true);
              }
              return result;
            }
          }
        }
        for (int i = endR + 1; i < 8; i++)
        {
          for (int j = endC + 1; j < 8; j++)
          {
            if ((black and board[i][j]->getType() == 'r') or (!black and board[i][j]->getType() == 'R'))
            {
              swap(board[endR - 1][endC - 1], board[i][j]);
              if (black)
              {
                blackPos.clear();
                blackPos = generateMove(false);
                blackPos = legalizeMove(castlingMove(blackPos, false), false);
              }
              else
              {
                whitePos.clear();
                whitePos = generateMove(true);
                whitePos = legalizeMove(castlingMove(whitePos, true), true);
              }
              find = true;
              if ((!black and blackChecked(blackKingR, blackKingC)) or (black and whiteChecked(whiteKingR, whiteKingC)))
              {
                result = true;
              }
              else
              {
                result = false;
              }
              swap(board[endR][endC], board[startR][startC]);
              swap(board[endR - 1][endC - 1], board[i][j]);
              if (black)
              {
                blackPos.clear();
                blackPos = generateMove(false);
                blackPos = legalizeMove(castlingMove(blackPos, false), false);
              }
              else
              {
                whitePos.clear();
                whitePos = generateMove(true);
                whitePos = legalizeMove(castlingMove(whitePos, true), true);
              }
              break;
            }
          }
          if (find)
          {
            break;
          }
        }
        if (find)
        {
          return result;
        }
        else
        {
          swap(board[endR][endC], board[startR][startC]);
          return false;
        }
      }
      else if (endC < startC and endR != startR)
      { //castling
        swap(board[endR][endC], board[startR][startC]);
        bool find = false;
        // find rook
        for (int i = endR + 1; i < 8; i++)
        {
          for (int j = endC - 1; j >= 0; j--)
          {
            if ((black and board[i][j]->getType() == 'r') or (!black and board[i][j]->getType() == 'R'))
            {
              swap(board[endR - 1][endC + 1], board[i][j]);
              if (black)
              {
                blackPos.clear();
                blackPos = generateMove(false);
                blackPos = legalizeMove(castlingMove(blackPos, false), false);
              }
              else
              {
                whitePos.clear();
                whitePos = generateMove(true);
                whitePos = legalizeMove(castlingMove(whitePos, true), true);
              }
              find = true;
              if ((!black and blackChecked(blackKingR, blackKingC)) or (black and whiteChecked(whiteKingR, whiteKingC)))
              {
                result = true;
              }
              else
              {
                result = false;
              }
              swap(board[endR][endC], board[startR][startC]);
              swap(board[endR - 1][endC + 1], board[i][j]);
              if (black)
              {
                blackPos.clear();
                blackPos = generateMove(false);
                blackPos = legalizeMove(castlingMove(blackPos, false), false);
              }
              else
              {
                whitePos.clear();
                whitePos = generateMove(true);
                whitePos = legalizeMove(castlingMove(whitePos, true), true);
              }
              return result;
            }
          }
        }
        for (int i = endR - 1; i < 8; i++)
        {
          for (int j = endC - 1; j < 8; j++)
          {
            if ((black and board[i][j]->getType() == 'r') or (!black and board[i][j]->getType() == 'R'))
            {
              swap(board[endR + 1][endC + 1], board[i][j]);
              if (black)
              {
                blackPos.clear();
                blackPos = generateMove(false);
                blackPos = legalizeMove(castlingMove(blackPos, false), false);
              }
              else
              {
                whitePos.clear();
                whitePos = generateMove(true);
                whitePos = legalizeMove(castlingMove(whitePos, true), true);
              }
              find = true;
              if ((!black and blackChecked(blackKingR, blackKingC)) or (black and whiteChecked(whiteKingR, whiteKingC)))
              {
                result = true;
              }
              else
              {
                result = false;
              }
              swap(board[endR][endC], board[startR][startC]);
              swap(board[endR + 1][endC + 1], board[i][j]);
              if (black)
              {
                blackPos.clear();
                blackPos = generateMove(false);
                blackPos = legalizeMove(castlingMove(blackPos, false), false);
              }
              else
              {
                whitePos.clear();
                whitePos = generateMove(true);
                whitePos = legalizeMove(castlingMove(whitePos, true), true);
              }
              break;
            }
          }
          if (find)
          {
            break;
          }
        }
        if (find)
        {
          return result;
        }
        else
        {
          swap(board[endR][endC], board[startR][startC]);
          return false;
        }
      }
      else
      {
        return false;
      }
    }
  }
  else
  {
    return false;
  }
}

bool Board::testmove(Move this_move, bool checkWhite)
{
  int startR = this_move.startR;
  int startC = this_move.startC;
  int endR = this_move.endR;
  int endC = this_move.endC;
  char curr_type = board[startR][startC]->getType();
  bool black = islower(curr_type);
  char curr = tolower(curr_type);
  bool result;
  Chess *tempS = nullptr;

  if ((checkWhite and black) or (!checkWhite and !black)){
    return false;
  }

  // normal move
  if ((curr == 'p' and endC == startC) or (curr != 'k' and curr != 'p'))
  {
    tempS = new noChess{"black", startR, startC};
    swap(board[startR][startC], board[endR][endC]);
    swap(tempS, board[startR][startC]);
    if (black)
    {
      whitePos.clear();
      whitePos = generateMove(true);
      whitePos = castlingMove(whitePos, true);
      if (blackChecked(blackKingR, blackKingC))
      {
        result = false;
      }
      else
      {
        result = true;
      }
    }
    else
    {
      blackPos.clear();
      blackPos = generateMove(false);
      blackPos = castlingMove(blackPos, false);
      if (whiteChecked(whiteKingR, whiteKingC))
      {
        result = false;
      }

      else
      {
        result = true;
      }
    }
    swap(board[startR][startC], board[endR][endC]);
    swap(tempS, board[endR][endC]);
    delete tempS;
    if (black)
    {
      whitePos.clear();
      whitePos = generateMove(true);
      whitePos = castlingMove(whitePos, true);
    }
    else
    {
      blackPos.clear();
      blackPos = generateMove(false);
      blackPos = castlingMove(blackPos, false);
    }
    return result;
  }
  else if (curr == 'p')
  {
    if (board[endR][endC]->getType() != 'e' and board[endR][endC]->getType() != 'E')
    {
      tempS = new noChess{"black", startR, startC};
      swap(board[startR][startC], board[endR][endC]);
      swap(tempS, board[startR][startC]);
      if (black)
      {
        whitePos.clear();
        whitePos = generateMove(true);
        whitePos = castlingMove(whitePos, true);
        if (blackChecked(blackKingR, blackKingC))
        {
          result = false;
        }
        else
        {
          result = true;
        }
      }
      else
      {
        blackPos.clear();
        blackPos = generateMove(false);
        blackPos = castlingMove(blackPos, false);
        if (whiteChecked(whiteKingR, whiteKingC))
        {
          result = false;
        }
        else
        {
          result = true;
        }
      }
      swap(board[startR][startC], board[endR][endC]);
      swap(tempS, board[endR][endC]);
      delete tempS;
      if (black)
      {
        whitePos.clear();
        whitePos = generateMove(true);
        whitePos = castlingMove(whitePos, true);
      }
      else
      {
        blackPos.clear();
        blackPos = generateMove(false);
        blackPos = castlingMove(blackPos, false);
      }
      return result;
    }
    else
    { // enpassant
      tempS = new noChess{"black", startR, startC};
      swap(board[endR][endC], board[startR][startC]);
      swap(tempS, board[startR][endC]);
      if (black)
      {
        whitePos.clear();
        whitePos = generateMove(true);
        whitePos = castlingMove(whitePos, true);
        if (blackChecked(blackKingR, blackKingC))
        {
          result = false;
        }
        else
        {
          result = true;
        }
      }
      else
      {
        if (whiteChecked(whiteKingR, whiteKingC))
        {
          blackPos.clear();
          blackPos = generateMove(false);
          blackPos = castlingMove(blackPos, false);
          result = false;
        }
        else
        {
          result = true;
        }
      }
      swap(board[endR][endC], board[startR][startC]);
      swap(tempS, board[startR][endC]);
      delete tempS;
      if (black)
      {
        whitePos.clear();
        whitePos = generateMove(true);
        whitePos = castlingMove(whitePos, true);
      }
      else
      {
        blackPos.clear();
        blackPos = generateMove(false);
        blackPos = castlingMove(blackPos, false);
      }
      return result;
    }
  }
  else if (curr == 'k')
  {
    if (startR - endR == 1 or startR - endR == -1 or startC - endC == 1 or startC - endC == -1)
    {
      tempS = new noChess{"black", startR, startC};
      swap(board[startR][startC], board[endR][endC]);
      swap(tempS, board[startR][startC]);
      if (black)
      {
        whitePos.clear();
        whitePos = generateMove(true);
        whitePos = castlingMove(whitePos, true);
        if (blackChecked(endR, endC))
        {
          result = false;
        }
        else
        {
          //printpossiblemove();
          result = true;
        }
      }
      else
      {
        blackPos.clear();
        blackPos = generateMove(false);
        blackPos = castlingMove(blackPos, false);
        if (whiteChecked(endR, endC))
        {
          result = false;
        }
        else
        {
          result = true;
        }
      }
      swap(board[startR][startC], board[endR][endC]);
      swap(tempS, board[endR][endC]);
      delete tempS;
      if (black)
      {
        whitePos.clear();
        whitePos = generateMove(true);
        whitePos = castlingMove(whitePos, true);
      }
      else
      {
        blackPos.clear();
        blackPos = generateMove(false);
        blackPos = castlingMove(blackPos, false);
      }
      return result;
    }
    else
    { // castling
      if (endC - startC == 2 and endR == startR)
      {
        swap(board[endR][endC], board[startR][startC]);
        // find rook
        for (int i = endC + 1; i < 8; i++)
        {
          if ((black and board[endR][i]->getType() == 'r') or (!black and board[endR][i]->getType() == 'R'))
          {
            swap(board[endR][endC - 1], board[endR][i]);
            if (black)
            {
              whitePos.clear();
              whitePos = generateMove(true);
              whitePos = castlingMove(whitePos, true);
            }
            else
            {
              blackPos.clear();
              blackPos = generateMove(false);
              blackPos = castlingMove(blackPos, false);
            }
            if ((black and blackChecked(endR, endC)) or (!black and whiteChecked(endR, endC)))
            {
              result = false;
            }
            else
            {
              result = true;
            }
            swap(board[endR][endC - 1], board[endR][i]);
            break;
          }
        }
        swap(board[endR][endC], board[startR][startC]);
        if (black)
        {
          whitePos.clear();
          whitePos = generateMove(true);
          whitePos = castlingMove(whitePos, true);
        }
        else
        {
          blackPos.clear();
          blackPos = generateMove(false);
          blackPos = castlingMove(blackPos, false);
        }
        return result;
      }
      else if (startC - endC == 2 and endR == startR)
      {
        swap(board[endR][endC], board[startR][startC]);
        // find rook
        for (int i = endC - 1; i >= 0; i--)
        {
          if ((black and board[endR][i]->getType() == 'r') or (!black and board[endR][i]->getType() == 'R'))
          {
            swap(board[endR][endC + 1], board[endR][i]);
            if (black)
            {
              whitePos.clear();
              whitePos = generateMove(true);
              whitePos = castlingMove(whitePos, true);
            }
            else
            {
              blackPos.clear();
              blackPos = generateMove(false);
              blackPos = castlingMove(blackPos, false);
            }
            if ((black and blackChecked(endR, endC)) or (!black and whiteChecked(endR, endC)))
            {
              result = false;
            }
            else
            {
              result = true;
            }
            swap(board[endR][endC + 1], board[endR][i]);
            break;
          }
        }
        swap(board[endR][endC], board[startR][startC]);
        if (black)
        {
          whitePos.clear();
          whitePos = generateMove(true);
          whitePos = castlingMove(whitePos, true);
        }
        else
        {
          blackPos.clear();
          blackPos = generateMove(false);
          blackPos = castlingMove(blackPos, false);
        }
        return result;
      }
      else if (startR - endR == 2 and endC == startC)
      {
        swap(board[endR][endC], board[startR][startC]);
        for (int i = endR - 1; i >= 0; i--)
        {
          if ((black and board[i][endC]->getType() == 'r') or (!black and board[i][endC]->getType() == 'R'))
          {
            swap(board[endR + 1][endC], board[endR][i]);
            if (black)
            {
              whitePos.clear();
              whitePos = generateMove(true);
              whitePos = castlingMove(whitePos, true);
            }
            else
            {
              blackPos.clear();
              blackPos = generateMove(false);
              blackPos = castlingMove(blackPos, false);
            }
            if ((black and blackChecked(endR, endC)) or (!black and whiteChecked(endR, endC)))
            {
              result = false;
            }
            else
            {
              result = true;
            }
            swap(board[endR + 1][endC], board[endR][i]);
            break;
          }
        }
        swap(board[endR][endC], board[startR][startC]);
        if (black)
        {
          whitePos.clear();
          whitePos = generateMove(true);
          whitePos = castlingMove(whitePos, true);
        }
        else
        {
          blackPos.clear();
          blackPos = generateMove(false);
          blackPos = castlingMove(blackPos, false);
        }
        return result;
      }
      else if (startR - endR == -2 and endC == startC)
      {
        swap(board[endR][endC], board[startR][startC]);
        for (int i = endR + 1; i < 8; i++)
        {
          if ((black and board[i][endC]->getType() == 'r') or (!black and board[i][endC]->getType() == 'R'))
          {
            swap(board[endR - 1][endC], board[endR][i]);
            if (black)
            {
              whitePos.clear();
              whitePos = generateMove(true);
              whitePos = castlingMove(whitePos, true);
            }
            else
            {
              blackPos.clear();
              blackPos = generateMove(false);
              blackPos = castlingMove(blackPos, false);
            }
            if ((black and blackChecked(endR, endC)) or (!black and whiteChecked(endR, endC)))
            {
              result = false;
            }
            else
            {
              result = true;
            }
            swap(board[endR - 1][endC], board[endR][i]);
            break;
          }
        }
        swap(board[endR][endC], board[startR][startC]);
        if (black)
        {
          whitePos.clear();
          whitePos = generateMove(true);
          whitePos = castlingMove(whitePos, true);
        }
        else
        {
          blackPos.clear();
          blackPos = generateMove(false);
          blackPos = castlingMove(blackPos, false);
        }
        return result;
      }
      else if (endC > startC and endR != startR)
      { //castling
        swap(board[endR][endC], board[startR][startC]);
        bool find = false;
        // find rook
        for (int i = endR - 1; i >= 0; i--)
        {
          for (int j = endC + 1; j < 8; j++)
          {
            if ((black and board[i][j]->getType() == 'r') or (!black and board[i][j]->getType() == 'R'))
            {
              swap(board[endR + 1][endC - 1], board[i][j]);
              if (black)
              {
                whitePos.clear();
                whitePos = generateMove(true);
                whitePos = castlingMove(whitePos, true);
              }
              else
              {
                blackPos.clear();
                blackPos = generateMove(false);
                blackPos = castlingMove(blackPos, false);
              }
              find = true;
              if ((black and blackChecked(endR, endC)) or (!black and whiteChecked(endR, endC)))
              {
                result = false;
              }
              else
              {
                result = true;
              }
              swap(board[endR][endC], board[startR][startC]);
              swap(board[endR + 1][endC - 1], board[i][j]);
              if (black)
              {
                whitePos.clear();
                whitePos = generateMove(true);
                whitePos = castlingMove(whitePos, true);
              }
              else
              {
                blackPos.clear();
                blackPos = generateMove(false);
                blackPos = castlingMove(blackPos, false);
              }
              return result;
            }
          }
        }
        for (int i = endR + 1; i < 8; i++)
        {
          for (int j = endC + 1; j < 8; j++)
          {
            if ((black and board[i][j]->getType() == 'r') or (!black and board[i][j]->getType() == 'R'))
            {
              swap(board[endR - 1][endC - 1], board[i][j]);
              if (black)
              {
                whitePos.clear();
                whitePos = generateMove(true);
                whitePos = castlingMove(whitePos, true);
              }
              else
              {
                blackPos.clear();
                blackPos = generateMove(false);
                blackPos = castlingMove(blackPos, false);
              }
              find = true;
              if ((black and blackChecked(endR, endC)) or (!black and whiteChecked(endR, endC)))
              {
                result = false;
              }
              else
              {
                result = true;
              }
              swap(board[endR][endC], board[startR][startC]);
              swap(board[endR - 1][endC - 1], board[i][j]);
              if (black)
              {
                whitePos.clear();
                whitePos = generateMove(true);
                whitePos = castlingMove(whitePos, true);
              }
              else
              {
                blackPos.clear();
                blackPos = generateMove(false);
                blackPos = castlingMove(blackPos, false);
              }
              break;
            }
          }
          if (find)
          {
            break;
          }
        }
        if (find)
        {
          return result;
        }
        else
        {
          swap(board[endR][endC], board[startR][startC]);
          return false;
        }
      }
      else if (endC < startC and endR != startR)
      { //castling
        swap(board[endR][endC], board[startR][startC]);
        bool find = false;
        // find rook
        for (int i = endR + 1; i < 8; i++)
        {
          for (int j = endC - 1; j >= 0; j--)
          {
            if ((black and board[i][j]->getType() == 'r') or (!black and board[i][j]->getType() == 'R'))
            {
              swap(board[endR - 1][endC + 1], board[i][j]);
              if (black)
              {
                whitePos.clear();
                whitePos = generateMove(true);
                whitePos = castlingMove(whitePos, true);
              }
              else
              {
                blackPos.clear();
                blackPos = generateMove(false);
                blackPos = castlingMove(blackPos, false);
              }
              find = true;
              if ((black and blackChecked(endR, endC)) or (!black and whiteChecked(endR, endC)))
              {
                result = false;
              }
              else
              {
                result = true;
              }
              swap(board[endR][endC], board[startR][startC]);
              swap(board[endR - 1][endC + 1], board[i][j]);
              if (black)
              {
                whitePos.clear();
                whitePos = generateMove(true);
                whitePos = castlingMove(whitePos, true);
              }
              else
              {
                blackPos.clear();
                blackPos = generateMove(false);
                blackPos = castlingMove(blackPos, false);
              }
              return result;
            }
          }
        }
        for (int i = endR - 1; i < 8; i++)
        {
          for (int j = endC - 1; j < 8; j++)
          {
            if ((black and board[i][j]->getType() == 'r') or (!black and board[i][j]->getType() == 'R'))
            {
              swap(board[endR + 1][endC + 1], board[i][j]);
              if (black)
              {
                whitePos.clear();
                whitePos = generateMove(true);
                whitePos = castlingMove(whitePos, true);
              }
              else
              {
                blackPos.clear();
                blackPos = generateMove(false);
                blackPos = castlingMove(blackPos, false);
              }
              find = true;
              if ((black and blackChecked(endR, endC)) or (!black and whiteChecked(endR, endC)))
              {
                result = false;
              }
              else
              {
                result = true;
              }
              swap(board[endR][endC], board[startR][startC]);
              swap(board[endR + 1][endC + 1], board[i][j]);
              if (black)
              {
                whitePos.clear();
                whitePos = generateMove(true);
                whitePos = castlingMove(whitePos, true);
              }
              else
              {
                blackPos.clear();
                blackPos = generateMove(false);
                blackPos = castlingMove(blackPos, false);
              }
              break;
            }
          }
          if (find)
          {
            break;
          }
        }
        if (find)
        {
          return result;
        }
        else
        {
          swap(board[endR][endC], board[startR][startC]);
          return false;
        }
      }
      else
      {
        return false;
      }
    }
  }
  else
  {
    return false;
  }
}

vector<Move> &Board::legalizeMove(vector<Move> &possibleMoves, bool white)
{
  for (int i = possibleMoves.size() - 1; i >= 0; i--)
  {
    // cout << i << " " << possibleMoves[i].startR << " " << possibleMoves[i].startC 
    // << " " << possibleMoves[i].endR << " " << possibleMoves[i].endC << endl;
    if (possibleMoves[i].startR < 0 or possibleMoves[i].startR >= 8 or possibleMoves[i].startC < 0
      or possibleMoves[i].startC >= 8 or possibleMoves[i].endR < 0 or possibleMoves[i].endR >= 8
      or possibleMoves[i].endC < 0 or possibleMoves[i].endC >= 8){
      continue;
    }
    else if (!testmove(possibleMoves[i], white))
    {
      possibleMoves.erase(possibleMoves.begin() + i);
    }
  }
  return possibleMoves;
}

bool Board::valid()
{
  whitePos.clear();
  whitePos = generateMove(true);
  whitePos = legalizeMove(castlingMove(whitePos, true), true);
  blackPos.clear();
  blackPos = generateMove(false);
  blackPos = legalizeMove(castlingMove(blackPos, false), false);
  if (whiteChecked(whiteKingR, whiteKingC))
  {
    return false;
  }
  if (blackChecked(blackKingR, blackKingC))
  {
    return false;
  }
  return td->valid();
}

void Board::movePiece(int startR, int startC, int endR, int endC)
{
  char piece = board[startR][startC]->getType();
  Chess *tempS = board[startR][startC];
  Chess *tempE = board[endR][endC];
  Chess *enpassant = nullptr;
  bool enPassant = false;
  bool castling = false;
  int casSR = 0;
  int casSC = 0;
  int casER = 0;
  int casEC = 0;
  if (piece == 'B')
  { // white
    board[endR][endC] = new Bishop{"white", endR, endC};
  }
  else if (piece == 'K')
  {
    if (endC - startC == 1 or endR - startR == 1 or startC - endC == 1 or startR - endR == 1)
    {
      board[endR][endC] = new King{"white", endR, endC};
    }
    else
    {
      castling = true;
      if (endC - startC == 2 and endR == startR)
      {
        swap(board[endR][endC], board[startR][startC]);
        // find rook
        for (int i = endC + 1; i < 8; i++)
        {
          if (board[endR][i]->getType() == 'R')
          {
            swap(board[endR][endC - 1], board[endR][i]);
            casSR = endR;
            casSC = i;
            casER = endR;
            casEC = endC - 1;
            break;
          }
        }
      }
      else if (startC - endC == 2 and endR == startR)
      {
        swap(board[endR][endC], board[startR][startC]);
        // find rook
        for (int i = endC - 1; i >= 0; i--)
        {
          if (board[endR][i]->getType() == 'R')
          {
            swap(board[endR][endC + 1], board[endR][i]);
            casSR = endR;
            casSC = i;
            casER = endR;
            casEC = endC + 1;
            break;
          }
        }
      }
      else if (startR - endR == 2 and endC == startC)
      {
        swap(board[endR][endC], board[startR][startC]);
        for (int i = endR - 1; i >= 0; i--)
        {
          if (board[i][endC]->getType() == 'R')
          {
            swap(board[endR + 1][endC], board[i][endC]);
            casSR = i;
            casSC = endC;
            casER = endR + 1;
            casEC = endC;
            break;
          }
        }
      }
      else if (startR - endR == -2 and endC == startC)
      {
        swap(board[endR][endC], board[startR][startC]);
        for (int i = endR + 1; i < 8; i++)
        {
          if (board[i][endC]->getType() == 'R')
          {
            swap(board[endR - 1][endC], board[i][endC]);
            casSR = i;
            casSC = endC;
            casER = endR - 1;
            casEC = endC;
            break;
          }
        }
      }
      else if (endC > startC and endR != startR)
      { //castling
        swap(board[endR][endC], board[startR][startC]);
        bool find = false;
        // find rook
        for (int i = endR - 1; i >= 0; i--)
        {
          for (int j = endC + 1; j < 8; j++)
          {
            if (board[i][j]->getType() == 'R')
            {
              swap(board[endR + 1][endC - 1], board[i][j]);
              casSR = i;
              casSC = j;
              casER = endR + 1;
              casEC = endC - 1;
              find = true;
              break;
            }
          }
        }
        if (!find)
        {
          for (int i = endR + 1; i < 8; i++)
          {
            for (int j = endC + 1; j < 8; j++)
            {
              if (board[i][j]->getType() == 'R')
              {
                swap(board[endR - 1][endC - 1], board[i][j]);
                casSR = i;
                casSC = j;
                casER = endR - 1;
                casEC = endC - 1;
                find = true;
                break;
              }
            }
          }
        }
      }
      else if (endC < startC and endR != startR)
      { //castling
        swap(board[endR][endC], board[startR][startC]);
        bool find = false;
        // find rook
        for (int i = endR + 1; i < 8; i++)
        {
          for (int j = endC - 1; j >= 0; j--)
          {
            if (board[i][j]->getType() == 'R')
            {
              swap(board[endR - 1][endC + 1], board[i][j]);
              casSR = i;
              casSC = j;
              casER = endR - 1;
              casEC = endC + 1;
              find = true;
              break;
            }
          }
        }
        if (!find)
        {
          for (int i = endR - 1; i < 8; i++)
          {
            for (int j = endC - 1; j < 8; j++)
            {
              if (board[i][j]->getType() == 'R')
              {
                swap(board[endR + 1][endC + 1], board[i][j]);
                casSR = i;
                casSC = j;
                casER = endR + 1;
                casEC = endC + 1;
                find = true;
                break;
              }
            }
          }
        }
      }
    }
  }
  else if (piece == 'N')
  {
    board[endR][endC] = new Knight{"white", endR, endC};
  }
  else if (piece == 'P')
  {
    //todo: 变棋, en passant logic
    if (startR - endR == 2)
    { //enpassant
      board[endR][endC] = new Pawn{"white", endR, endC};
      if (endC - 1 >= 0)
      {
        wEnPassant.emplace_back(Move{endR, endC - 1, endR + 1, endC});
      }
      if (endC + 1 < 8)
      {
        wEnPassant.emplace_back(Move{endR, endC + 1, endR + 1, endC});
      } // where the en passant should land
    }
    if (startR - endR == 1)
    {
      board[endR][endC] = new Pawn{"white", endR, endC};
      int size = bEnPassant.size();
      for (int i = 0; i < size; i++)
      {
        if (bEnPassant[i].endR == endR and bEnPassant[i].endC == endC)
        {
          enpassant = board[startR][endC];
          if ((startR % 2 == 0 and endC % 2 == 0) or
              (startR % 2 != 0 and endC % 2 != 0))
          {
            board[startR][endC] = new noChess{"white", startR, endC};
          }
          else
          {
            board[startR][endC] = new noChess{"black", startR, endC};
          }
          enPassant = true;
        }
      }
      if (endR == 0)
      {
        while (true)
        {
          try
          {
            cout << "which type do you want to promote to? R(rook), B(bishop), N(knight) or Q(queen):" << endl;
            char promotion;
            cin >> promotion;
            if (cin.fail())
            {
              throw(out_of_range("i"));
            }
            if (islower(promotion) or (promotion != 'R' and
                                       promotion != 'B' and promotion != 'N' and promotion != 'Q'))
            {
              throw(out_of_range("i"));
            }
            set(promotion, endR, endC);
            break;
          }
          catch (out_of_range)
          {
            cout << "pawn promotion must be either R(rook), B(bishop), N(knight) or Q(queen)" << endl;
          }
        }
      }
    }
  }
  else if (piece == 'Q')
  {
    board[endR][endC] = new Queen{"white", endR, endC};
  }
  else if (piece == 'R')
  {
    board[endR][endC] = new Rook{"white", endR, endC};
  }

  if (!islower(piece) and !castling)
  {
    if ((startR % 2 == 0 and startC % 2 == 0) or
        (startR % 2 != 0 and startC % 2 != 0))
    {
      board[startR][startC] = new noChess{"white", startR, startC};
    }
    else
    {
      board[startR][startC] = new noChess{"black", startR, startC};
    }
  }
  if (!islower(piece) and castling)
  {
    InfoType info{"castling", board[endR][endC]->getType(), startR, startC, endR, endC,
                  casSR, casSC, casER, casEC};
    setState(info);
    board[endR][endC]->setFirstMove();
  }
  else if (!islower(piece) and !enPassant)
  {
    delete tempS;
    delete tempE;
    InfoType info{"move", board[endR][endC]->getType(), startR, startC, endR, endC,
                  0, 0, 0, 0};
    setState(info);
    board[endR][endC]->setFirstMove();
  }
  else if (!islower(piece) and enPassant)
  {
    delete tempS;
    delete tempE;
    delete enpassant;
    InfoType info{"enPassant", board[endR][endC]->getType(), startR, startC, endR, endC,
                  0, 0, 0, 0};
    setState(info);
    board[endR][endC]->setFirstMove();
  }

  if (!islower(piece))
  {
    bEnPassant.clear();
  }

  if (piece == 'b')
  { // black
    board[endR][endC] = new Bishop{"black", endR, endC};
  }
  else if (piece == 'k')
  {
    if (endC - startC == 1 or endR - startR == 1 or startC - endC == 1 or startR - endR == 1)
    {
      board[endR][endC] = new King{"black", endR, endC};
    }
    else
    {
      castling = true;
      if (endC - startC == 2 and endR == startR)
      {
        swap(board[endR][endC], board[startR][startC]);
        // find rook
        for (int i = endC + 1; i < 8; i++)
        {
          if (board[endR][i]->getType() == 'r')
          {
            swap(board[endR][endC - 1], board[endR][i]);
            casSR = endR;
            casSC = i;
            casER = endR;
            casEC = endC - 1;
            break;
          }
        }
      }
      else if (startC - endC == 2 and endR == startR)
      {
        swap(board[endR][endC], board[startR][startC]);
        // find rook
        for (int i = endC - 1; i >= 0; i--)
        {
          if (board[endR][i]->getType() == 'r')
          {
            swap(board[endR][endC + 1], board[endR][i]);
            casSR = endR;
            casSC = i;
            casER = endR;
            casEC = endC + 1;
            break;
          }
        }
      }
      else if (startR - endR == 2 and endC == startC)
      {
        swap(board[endR][endC], board[startR][startC]);
        for (int i = endR - 1; i >= 0; i--)
        {
          if (board[i][endC]->getType() == 'r')
          {
            swap(board[endR + 1][endC], board[i][endC]);
            casSR = i;
            casSC = endC;
            casER = endR + 1;
            casEC = endC;
            break;
          }
        }
      }
      else if (startR - endR == -2 and endC == startC)
      {
        swap(board[endR][endC], board[startR][startC]);
        for (int i = endR + 1; i < 8; i++)
        {
          if (board[i][endC]->getType() == 'r')
          {
            swap(board[endR - 1][endC], board[i][endC]);
            casSR = i;
            casSC = endC;
            casER = endR - 1;
            casEC = endC;
            break;
          }
        }
      }
      else if (endC > startC and endR != startR)
      { //castling
        swap(board[endR][endC], board[startR][startC]);
        bool find = false;
        // find rook
        for (int i = endR - 1; i >= 0; i--)
        {
          for (int j = endC + 1; j < 8; j++)
          {
            if (board[i][j]->getType() == 'r')
            {
              swap(board[endR + 1][endC - 1], board[i][j]);
              casSR = i;
              casSC = j;
              casER = endR + 1;
              casEC = endC - 1;
              find = true;
              break;
            }
          }
        }
        if (!find)
        {
          for (int i = endR + 1; i < 8; i++)
          {
            for (int j = endC + 1; j < 8; j++)
            {
              if (board[i][j]->getType() == 'r')
              {
                swap(board[endR - 1][endC - 1], board[i][j]);
                casSR = i;
                casSC = j;
                casER = endR - 1;
                casEC = endC - 1;
                find = true;
                break;
              }
            }
          }
        }
      }
      else if (endC < startC and endR != startR)
      { //castling
        swap(board[endR][endC], board[startR][startC]);
        bool find = false;
        // find rook
        for (int i = endR + 1; i < 8; i++)
        {
          for (int j = endC - 1; j >= 0; j--)
          {
            if (board[i][j]->getType() == 'r')
            {
              swap(board[endR - 1][endC + 1], board[i][j]);
              casSR = i;
              casSC = j;
              casER = endR - 1;
              casEC = endC + 1;
              find = true;
              break;
            }
          }
        }
        if (!find)
        {
          for (int i = endR - 1; i < 8; i++)
          {
            for (int j = endC - 1; j < 8; j++)
            {
              if (board[i][j]->getType() == 'r')
              {
                swap(board[endR + 1][endC + 1], board[i][j]);
                casSR = i;
                casSC = j;
                casER = endR + 1;
                casEC = endC + 1;
                find = true;
                break;
              }
            }
          }
        }
      }
    }
  }
  else if (piece == 'n')
  {
    board[endR][endC] = new Knight{"black", endR, endC};
  }
  else if (piece == 'p')
  {
    //变棋的logic
    board[endR][endC] = new Pawn{"black", endR, endC};
    if (endR - startR == 2)
    { //enpassant
      if (endC - 1 >= 0)
      {
        bEnPassant.emplace_back(Move{endR, endC - 1, endR - 1, endC});
      }
      if (endC + 1 < 8)
      {
        bEnPassant.emplace_back(Move{endR, endC + 1, endR - 1, endC});
      }
    }
    if (endR - startR == 1)
    {
      int size = wEnPassant.size();
      for (int i = 0; i < size; i++)
      {
        if (wEnPassant[i].endR == endR and wEnPassant[i].endC == endC)
        {
          enpassant = board[startR][endC];
          if ((startR % 2 == 0 and endC % 2 == 0) or
              (startR % 2 != 0 and endC % 2 != 0))
          {
            board[startR][endC] = new noChess{"white", startR, endC};
          }
          else
          {
            board[startR][endC] = new noChess{"black", startR, endC};
          }
          enPassant = true;
          break;
        }
      }
    }
    if (endR == 7)
    {
      while (true)
      {
        try
        {
          char promotion;
          cout << "which type do you want to promote to? r(rook), b(bishop), n(knight) or q(queen):" << endl;
          cin >> promotion;
          if (cin.fail())
          {
            throw(out_of_range("i"));
          }
          if (!islower(promotion) or (promotion != 'r' and
                                      promotion != 'b' and promotion != 'n' and promotion != 'q'))
          {
            throw(out_of_range("i"));
          }
          set(promotion, endR, endC);
          break;
        }
        catch (out_of_range)
        {
          cout << "pawn promotion must be either r(rook), b(bishop), n(knight) or q(queen)" << endl;
        }
      }
    }
  }
  else if (piece == 'q')
  {
    board[endR][endC] = new Queen{"black", endR, endC};
  }
  else if (piece == 'r')
  {
    board[endR][endC] = new Rook{"black", endR, endC};
  }

  if (islower(piece) and !castling)
  {
    if ((startR % 2 == 0 and startC % 2 == 0) or
        (startR % 2 != 0 and startC % 2 != 0))
    {
      board[startR][startC] = new noChess{"white", startR, startC};
    }
    else
    {
      board[startR][startC] = new noChess{"black", startR, startC};
    }
  }
  if (islower(piece) and castling)
  {
    InfoType info{"castling", board[endR][endC]->getType(), startR, startC, endR, endC,
                  casSR, casSC, casER, casEC};
    setState(info);
    board[endR][endC]->setFirstMove();
  }
  else if (islower(piece) and !enPassant)
  {
    delete tempS;
    delete tempE;
    InfoType info{"move", board[endR][endC]->getType(), startR, startC, endR, endC,
                  0, 0, 0, 0};
    setState(info);
    board[endR][endC]->setFirstMove();
  }
  else if (islower(piece) and enPassant)
  {
    delete tempS;
    delete tempE;
    delete enpassant;
    InfoType info{"enPassant", board[endR][endC]->getType(), startR, startC, endR, endC,
                  0, 0, 0, 0};
    setState(info);
    board[endR][endC]->setFirstMove();
  }

  wEnPassant.clear();
  return;

}

void Board::makeMove(char currentPlayer, int startR, int startC, int endR, int endC)
{
  if (currentPlayer == 'w')
  {
    if (firstPlay)
    {
      blackPos.clear();
      blackPos = generateMove(false);
      blackPos = castlingMove(blackPos, false);
      whitePos.clear();
      whitePos = generateMove(true);
      whitePos = legalizeMove(castlingMove(whitePos, true), true);
      firstPlay = false;
    }
    else
    {
      int enSize = bEnPassant.size();
      for (int i = 0; i < enSize; i++)
      {
        if (board[bEnPassant[i].startR][bEnPassant[i].startC]->getType() == 'P')
        {
          whitePos.emplace_back(bEnPassant[i]);
        }
      }
      whitePos = legalizeMove(whitePos, true);
    }
    int size = whitePos.size();
    if (size == 0)
    {
      if (whiteChecked(whiteKingR, whiteKingC))
      {
        throw string("whiteCheckmate");
      }
      else
      {
        throw string("no moves");
      }
    }
    for (int i = 0; i < size; i++)
    {
      if (whitePos[i].startR == startR and whitePos[i].startC == startC and
          whitePos[i].endR == endR and whitePos[i].endC == endC)
      {
        if (board[endR][endC]->getType() == 'k')
        {
          throw string("white wins");
        }
        movePiece(startR, startC, endR, endC);
        notifyObservers();
        if (board[endR][endC]->getType() == 'K')
        {
          whiteKingR = endR;
          whiteKingC = endC;
        }
        whitePos.clear();
        whitePos = generateMove(true);
        whitePos = castlingMove(whitePos, true);
        blackPos.clear();
        blackPos = generateMove(false);
        blackPos = legalizeMove(castlingMove(blackPos, false), false);
        //printpossiblemove();
        int bSize = blackPos.size();
        if (bSize == 0)
        {
          if (blackChecked(blackKingR, blackKingC))
          {
            throw string("blackCheckmate");
          }
          else
          {
            throw string("no moves");
          }
        }
        if (blackChecked(blackKingR, blackKingC))
        {
          if (blackCheckmate())
          {
            throw string("blackCheckmate");
          }
          throw string("blackChecked");
        }
        return;
      }
    }
    throw(out_of_range("i"));
  }
  else
  {
    if (firstPlay)
    {
      whitePos.clear();
      whitePos = generateMove(true);
      whitePos = castlingMove(whitePos, true);
      blackPos.clear();
      blackPos = generateMove(false);
      blackPos = legalizeMove(castlingMove(blackPos, false), false);
      firstPlay = false;
    }
    else
    {
      int enSize = wEnPassant.size();
      for (int i = 0; i < enSize; i++)
      {
        if (board[wEnPassant[i].startR][wEnPassant[i].startC]->getType() == 'p')
        {
          blackPos.emplace_back(wEnPassant[i]);
        }
      }
      blackPos = legalizeMove(blackPos, false);
    }

    int size = blackPos.size();
    if (size == 0)
    {
      if (blackChecked(blackKingR, blackKingC))
      {
        throw string("blackCheckmate");
      }
      else
      {
        throw string("no moves");
      }
    }
    for (int i = 0; i < size; i++)
    {
      if (blackPos[i].startR == startR and blackPos[i].startC == startC and
          blackPos[i].endR == endR and blackPos[i].endC == endC)
      {
        if (board[endR][endC]->getType() == 'K')
        {
          throw string("black wins");
        }
        movePiece(startR, startC, endR, endC);
        notifyObservers();
        if (board[endR][endC]->getType() == 'k')
        {
          blackKingR = endR;
          blackKingC = endC;
        }
        blackPos.clear();
        blackPos = generateMove(false);
        blackPos = castlingMove(blackPos, false);
        whitePos.clear();
        whitePos = generateMove(true);
        whitePos = castlingMove(whitePos, true);
        whitePos = legalizeMove(castlingMove(whitePos, true), true);
        //printpossiblemove();
        int wSize = whitePos.size();
        if (wSize == 0)
        {
          if (whiteChecked(whiteKingR, whiteKingC))
          {
            throw string("whiteCheckmate");
          }
          else
          {
            throw string("no moves");
          }
        }
        if (whiteChecked(whiteKingR, whiteKingC))
        {
          if (whiteCheckmate())
          {
            throw string("whiteCheckmate");
          }
          throw string("whiteChecked");
        }
        return;
      }
    }
    throw(out_of_range("i"));
  }
}

void Board::set(char piece, int row, int col)
{
  if (row >= 0 and row < 8 and col >= 0 and col < 8)
  {
    if (piece == 'k')
    {
      blackKingR = row;
      blackKingC = col;
    }
    else if (piece == 'K')
    {
      whiteKingR = row;
      whiteKingC = col;
    }

    if (piece == '-')
    {
      Chess *temp = board[row][col];
      if ((row % 2 == 0 and col % 2 == 0) or
          (row % 2 != 0 and col % 2 != 0))
      {
        board[row][col] = new noChess{"white", row, col};
      }
      else
      {
        board[row][col] = new noChess{"black", row, col};
      }
      delete temp;
    }
    else
    {
      Chess *temp = board[row][col];
      bool black;
      if (islower(piece))
      {
        black = true;
      }
      else
      {
        black = false;
      }
      char p = tolower(piece);
      if (p == 'b')
      {
        if (black)
        {
          board[row][col] = new Bishop{"black", row, col};
        }
        else
        {
          board[row][col] = new Bishop{"white", row, col};
        }
        delete temp;
      }
      else if (p == 'k')
      {
        if (black)
        {
          board[row][col] = new King{"black", row, col};
        }
        else
        {
          board[row][col] = new King{"white", row, col};
        }
        delete temp;
      }
      else if (p == 'n')
      {
        if (black)
        {
          board[row][col] = new Knight{"black", row, col};
        }
        else
        {
          board[row][col] = new Knight{"white", row, col};
        }
        delete temp;
      }
      else if (p == 'p')
      {
        if (black)
        {
          board[row][col] = new Pawn{"black", row, col};
        }
        else
        {
          board[row][col] = new Pawn{"white", row, col};
        }
        delete temp;
      }
      else if (p == 'q')
      {
        if (black)
        {
          board[row][col] = new Queen{"black", row, col};
        }
        else
        {
          board[row][col] = new Queen{"white", row, col};
        }
        delete temp;
      }
      else if (p == 'r')
      {
        if (black)
        {
          board[row][col] = new Rook{"black", row, col};
        }
        else
        {
          board[row][col] = new Rook{"white", row, col};
        }
        delete temp;
      }
    }
    InfoType i{"set", piece, row, col, 0, 0, 0, 0};
    setState(i);
    notifyObservers();
  }
}

std::vector<Move> &Board::castlingMove(std::vector<Move> &possible_move, bool color) //white 是大写 white 是true
{
  std::vector<int> find_king;
  std::vector<int> find_rook;
  int dis = 1;
  int posr;
  int posc;
  for (int find = 0; find < 64; find++)
  {
    char curr;
    curr = board[find / 8][find % 8]->getType();
    if (color == false)
    { //black

      if (curr == 'k')
      {
        if (board[find / 8][find % 8]->if_firstmv())
        {
          if (!blackChecked(find / 8, find % 8))
          {
            find_king.emplace_back(find);
          }
        }
      }
      else if (curr == 'r')
      {
        if (board[find / 8][find % 8]->if_firstmv())
        {
          find_rook.emplace_back(find);
        }
      }
    }
    if (color == true)
    { //white
      if (curr == 'K')
      {
        if (board[find / 8][find % 8]->if_firstmv())
        {
          if (!whiteChecked(find / 8, find % 8))
          {
            find_king.emplace_back(find);
          }
        }
      }

      else if (curr == 'R')
      {
        if (board[find / 8][find % 8]->if_firstmv())
        {
          find_rook.emplace_back(find);
        }
      }
    }
  }
  int king_num = find_king.size();
  int rook_num = find_rook.size();
  for (int k = 0; k < king_num; k++)
  {
    int i = find_king[k];
    for (int r = 0; r < rook_num; r++)
    {
      int horizontal;
      int vertical;
      int distance;
      int j = find_rook[r];
      if (i / 8 == j / 8)
      { //水平
        vertical = 0;
        if (j % 8 > i % 8)
        {
          horizontal = 1;
          distance = j % 8 - i % 8;
        }
        else
        {
          horizontal = -1;
          distance = i % 8 - j % 8;
        }
      }
      else if (i % 8 == j % 8)
      { //竖直
        horizontal = 0;
        if (j / 8 > i / 8)
        {
          vertical = 1;
          distance = j / 8 - i / 8;
        }
        else
        {
          vertical = -1;
          distance = i / 8 - j / 8;
        }
      }
      else if (i / 8 - j / 8 == i % 8 - j % 8)
      {
        if (j / 8 > i / 8)
        {
          vertical = 1;
          horizontal = 1;
          distance = j / 8 - i / 8;
        }
        else
        {
          vertical = -1;
          horizontal = -1;
          distance = i / 8 - j / 8;
        }
      }
      else if (j / 8 - i / 8 == i % 8 - j % 8)
      {
        if (j / 8 > i / 8)
        {
          vertical = 1;
          horizontal = -1;
          distance = j / 8 - i / 8;
        }
        else
        {
          vertical = -1;
          horizontal = 1;
          distance = i / 8 - j / 8;
        }
      }
      else
      {
        continue;
      }
      dis = 1;
      while (1)
      {
        posr = find_king[k] / 8 + dis * vertical;
        posc = find_king[k] % 8 + dis * horizontal;
        char curr = board[posr][posc]->getType();
        if (curr == 'e' or curr == 'E')
        {
          dis++;
          continue;
        }
        if (curr == 'r')
        {
          if (dis != distance)
          {
            break;
          }
          if (dis > 2)
          {
            if (!blackChecked(find_king[k] / 8 + vertical,
                              find_king[k] % 8 + horizontal) and
                !blackChecked(find_king[k] / 8 + 2 * vertical,
                              find_king[k] % 8 + 2 * horizontal) and
                !color)
            {
              possible_move.emplace_back(Move{find_king[k] / 8,
                                              find_king[k] % 8,
                                              find_king[k] / 8 + 2 * vertical,
                                              find_king[k] % 8 + 2 * horizontal});
            }
          }
        }
        else if (curr == 'R')
        {
          if (dis != distance)
          {
            break;
          }
          if (dis > 2)
          {
            if (!whiteChecked(find_king[k] / 8 + vertical,
                              find_king[k] % 8 + horizontal) and
                !whiteChecked(find_king[k] / 8 + 2 * vertical,
                              find_king[k] % 8 + 2 * horizontal) and
                color)
            {
              possible_move.emplace_back(Move{find_king[k] / 8,
                                              find_king[k] % 8,
                                              find_king[k] / 8 + 2 * vertical,
                                              find_king[k] % 8 + 2 * horizontal});
            }
          }
        }
        break;
      }
    }
  }
  return possible_move;
}

std::vector<Move> Board::generateMove(bool generateWhite)
{
  std::vector<Move> whitePos_in_generate;
  std::vector<Move> blackPos_in_generate;
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      char type = board[i][j]->getType();
      bool black = false;
      char t = tolower(type);
      if (islower(type))
      {
        black = true;
      }
      if (t != 'e' and ((generateWhite and !black) or (!generateWhite and black)))
      {
        if (t == 'r')
        { //rook
          for (int r = i - 1; r >= 0; r--)
          {
            char ty = board[r][j]->getType();
            if (!(ty == 'e' or ty == 'E'))
            {
              if (islower(ty) and !black)
              {
                whitePos_in_generate.emplace_back(Move{i, j, r, j});
              }
              else if (!islower(ty) and black)
              {
                blackPos_in_generate.emplace_back(Move{i, j, r, j});
              }
              break;
            }
            else
            {
              if (!black)
              {
                whitePos_in_generate.emplace_back(Move{i, j, r, j});
              }
              else
              {
                blackPos_in_generate.emplace_back(Move{i, j, r, j});
              }
            }
          }
          for (int r = i + 1; r < 8; r++)
          {
            char ty = board[r][j]->getType();
            if (!(ty == 'e' or ty == 'E'))
            {
              if (islower(ty) and !black)
              {
                whitePos_in_generate.emplace_back(Move{i, j, r, j});
              }
              else if (!islower(ty) and black)
              {
                blackPos_in_generate.emplace_back(Move{i, j, r, j});
              }
              break;
            }
            else
            {
              if (!black)
              {
                whitePos_in_generate.emplace_back(Move{i, j, r, j});
              }
              else
              {
                blackPos_in_generate.emplace_back(Move{i, j, r, j});
              }
            }
          }
          for (int c = j - 1; c >= 0; c--)
          {
            char ty = board[i][c]->getType();
            if (!(ty == 'e' or ty == 'E'))
            {
              if (islower(ty) and !black)
              {
                whitePos_in_generate.emplace_back(Move{i, j, i, c});
              }
              else if (!islower(ty) and black)
              {
                blackPos_in_generate.emplace_back(Move{i, j, i, c});
              }
              break;
            }
            else
            {
              if (!black)
              {
                whitePos_in_generate.emplace_back(Move{i, j, i, c});
              }
              else
              {
                blackPos_in_generate.emplace_back(Move{i, j, i, c});
              }
            }
          }
          for (int c = j + 1; c < 8; c++)
          {
            char ty = board[i][c]->getType();
            if (!(ty == 'e' or ty == 'E'))
            {
              if (islower(ty) and !black)
              {
                whitePos_in_generate.emplace_back(Move{i, j, i, c});
              }
              else if (!islower(ty) and black)
              {
                blackPos_in_generate.emplace_back(Move{i, j, i, c});
              }
              break;
            }
            else
            {
              if (!black)
              {
                whitePos_in_generate.emplace_back(Move{i, j, i, c});
              }
              else
              {
                blackPos_in_generate.emplace_back(Move{i, j, i, c});
              }
            }
          }
        }
        else if (t == 'k')
        { //king
          if (i - 1 >= 0)
          {
            if (j - 1 >= 0)
            {
              char ty = board[i - 1][j - 1]->getType();
              if (ty == 'e' or ty == 'E')
              {
                if (!black)
                {
                  whitePos_in_generate.emplace_back(Move{i, j, i - 1, j - 1});
                }
                else
                {
                  blackPos_in_generate.emplace_back(Move{i, j, i - 1, j - 1});
                }
              }
              else if (!black and islower(ty))
              {
                whitePos_in_generate.emplace_back(Move{i, j, i - 1, j - 1});
              }
              else if (!islower(ty) and black)
              {
                blackPos_in_generate.emplace_back(Move{i, j, i - 1, j - 1});
              }
            }
            if (j + 1 < 8)
            {
              char ty = board[i - 1][j + 1]->getType();
              if (ty == 'e' or ty == 'E')
              {
                if (!black)
                {
                  whitePos_in_generate.emplace_back(Move{i, j, i - 1, j + 1});
                }
                else
                {
                  blackPos_in_generate.emplace_back(Move{i, j, i - 1, j + 1});
                }
              }
              else if (!black and islower(ty))
              {
                whitePos_in_generate.emplace_back(Move{i, j, i - 1, j + 1});
              }
              else if (!islower(ty) and black)
              {
                blackPos_in_generate.emplace_back(Move{i, j, i - 1, j + 1});
              }
            }
            char ty = board[i - 1][j]->getType();
            if (ty == 'e' or ty == 'E')
            {
              if (!black)
              {
                whitePos_in_generate.emplace_back(Move{i, j, i - 1, j});
              }
              else
              {
                blackPos_in_generate.emplace_back(Move{i, j, i - 1, j});
              }
            }
            else if (!black and islower(ty))
            {
              whitePos_in_generate.emplace_back(Move{i, j, i - 1, j});
            }
            else if (!islower(ty) and black)
            {
              blackPos_in_generate.emplace_back(Move{i, j, i - 1, j});
            }
          }
          if (i + 1 < 8)
          {
            if (j - 1 >= 0)
            {
              char ty = board[i + 1][j - 1]->getType();
              if (ty == 'e' or ty == 'E')
              {
                if (!black)
                {
                  whitePos_in_generate.emplace_back(Move{i, j, i + 1, j - 1});
                }
                else
                {
                  blackPos_in_generate.emplace_back(Move{i, j, i + 1, j - 1});
                }
              }
              else if (!black and islower(ty))
              {
                whitePos_in_generate.emplace_back(Move{i, j, i + 1, j - 1});
              }
              else if (!islower(ty) and black)
              {
                blackPos_in_generate.emplace_back(Move{i, j, i + 1, j - 1});
              }
            }
            if (j + 1 < 8)
            {
              char ty = board[i + 1][j + 1]->getType();
              if (ty == 'e' or ty == 'E')
              {
                if (!black)
                {
                  whitePos_in_generate.emplace_back(Move{i, j, i + 1, j + 1});
                }
                else
                {
                  blackPos_in_generate.emplace_back(Move{i, j, i + 1, j + 1});
                }
              }
              else if (!black and islower(ty))
              {
                whitePos_in_generate.emplace_back(Move{i, j, i + 1, j + 1});
              }
              else if (!islower(ty) and black)
              {
                blackPos_in_generate.emplace_back(Move{i, j, i + 1, j + 1});
              }
            }
            char ty = board[i + 1][j]->getType();
            if (ty == 'e' or ty == 'E')
            {
              if (!black)
              {
                whitePos_in_generate.emplace_back(Move{i, j, i + 1, j});
              }
              else
              {
                blackPos_in_generate.emplace_back(Move{i, j, i + 1, j});
              }
            }
            else if (!black and islower(ty))
            {
              whitePos_in_generate.emplace_back(Move{i, j, i + 1, j});
            }
            else if (!islower(ty) and black)
            {
              blackPos_in_generate.emplace_back(Move{i, j, i + 1, j});
            }
          }
          if (j - 1 >= 0)
          {
            char ty = board[i][j - 1]->getType();
            if (ty == 'e' or ty == 'E')
            {
              if (!black)
              {
                whitePos_in_generate.emplace_back(Move{i, j, i, j - 1});
              }
              else
              {
                blackPos_in_generate.emplace_back(Move{i, j, i, j - 1});
              }
            }
            else if (!black and islower(ty))
            {
              whitePos_in_generate.emplace_back(Move{i, j, i, j - 1});
            }
            else if (!islower(ty) and black)
            {
              blackPos_in_generate.emplace_back(Move{i, j, i, j - 1});
            }
          }
          if (j + 1 < 8)
          {
            char ty = board[i][j + 1]->getType();
            if (ty == 'e' or ty == 'E')
            {
              if (!black)
              {
                whitePos_in_generate.emplace_back(Move{i, j, i, j + 1});
              }
              else
              {
                blackPos_in_generate.emplace_back(Move{i, j, i, j + 1});
              }
            }
            else if (!black and islower(ty))
            {
              whitePos_in_generate.emplace_back(Move{i, j, i, j + 1});
            }
            else if (!islower(ty) and black)
            {
              blackPos_in_generate.emplace_back(Move{i, j, i, j + 1});
            }
          }
        }
        else if (t == 'n')
        { //knight
          char a;
          if (i - 2 >= 0)
          {
            if (j - 1 >= 0)
            {
              a = board[i - 2][j - 1]->getType();
              if (!black and (a == 'e' or a == 'E' or islower(a)))
              {
                whitePos_in_generate.emplace_back(Move{i, j, i - 2, j - 1});
              }
              else if (black and (a == 'e' or a == 'E' or !islower(a)))
              {
                blackPos_in_generate.emplace_back(Move{i, j, i - 2, j - 1});
              }
            }

            if (j + 1 < 8)
            {
              a = board[i - 2][j + 1]->getType();
              if (!black and (a == 'e' or a == 'E' or islower(a)))
              {
                whitePos_in_generate.emplace_back(Move{i, j, i - 2, j + 1});
              }
              else if (black and (a == 'e' or a == 'E' or !islower(a)))
              {
                blackPos_in_generate.emplace_back(Move{i, j, i - 2, j + 1});
              }
            }
          }
          if (i + 2 < 8)
          {
            if (j - 1 >= 0)
            {
              a = board[i + 2][j - 1]->getType();
              if (!black and (a == 'e' or a == 'E' or islower(a)))
              {
                whitePos_in_generate.emplace_back(Move{i, j, i + 2, j - 1});
              }
              else if (black and (a == 'e' or a == 'E' or !islower(a)))
              {
                blackPos_in_generate.emplace_back(Move{i, j, i + 2, j - 1});
              }
            }
            if (j + 1 < 8)
            {
              a = board[i + 2][j + 1]->getType();
              if (!black and (a == 'e' or a == 'E' or islower(a)))
              {
                whitePos_in_generate.emplace_back(Move{i, j, i + 2, j + 1});
              }
              else if (black and (a == 'e' or a == 'E' or !islower(a)))
              {
                blackPos_in_generate.emplace_back(Move{i, j, i + 2, j + 1});
              }
            }
          }
          if (i - 1 >= 0)
          {
            if (j - 2 >= 0)
            {
              a = board[i - 1][j - 2]->getType();
              if (!black and (a == 'e' or a == 'E' or islower(a)))
              {
                whitePos_in_generate.emplace_back(Move{i, j, i - 1, j - 2});
              }
              else if (black and (a == 'e' or a == 'E' or !islower(a)))
              {
                blackPos_in_generate.emplace_back(Move{i, j, i - 1, j - 2});
              }
            }
            if (j + 2 < 8)
            {
              a = board[i - 1][j + 2]->getType();
              if (!black and (a == 'e' or a == 'E' or islower(a)))
              {
                whitePos_in_generate.emplace_back(Move{i, j, i - 1, j + 2});
              }
              else if (black and (a == 'e' or a == 'E' or !islower(a)))
              {
                blackPos_in_generate.emplace_back(Move{i, j, i - 1, j + 2});
              }
            }
          }
          if (i + 1 < 8)
          {
            if (j - 2 >= 0)
            {
              a = board[i + 1][j - 2]->getType();
              if (!black and (a == 'e' or a == 'E' or islower(a)))
              {
                whitePos_in_generate.emplace_back(Move{i, j, i + 1, j - 2});
              }
              else if (black and (a == 'e' or a == 'E' or !islower(a)))
              {
                blackPos_in_generate.emplace_back(Move{i, j, i + 1, j - 2});
              }
            }
            if (j + 2 < 8)
            {
              a = board[i + 1][j + 2]->getType();
              if (!black and (a == 'e' or a == 'E' or islower(a)))
              {
                whitePos_in_generate.emplace_back(Move{i, j, i + 1, j + 2});
              }
              else if (black and (a == 'e' or a == 'E' or !islower(a)))
              {
                blackPos_in_generate.emplace_back(Move{i, j, i + 1, j + 2});
              }
            }
          }
        }
        else if (t == 'p')
        { // pawn
          //记得第一次move可以move两格，你看看咋写，因为我pawn里的firstMove是
          //private的。。你可以看看直接用pawn里面的legalMove()或者别的
          //------------------------------------------------------

          if (type == 'P')
          { //white 大写
            if (i - 1 >= 0)
            {
              char onebefore = board[i - 1][j]->getType();
              if (onebefore == 'e' or onebefore == 'E')
              {
                whitePos_in_generate.emplace_back(Move{i, j, i - 1, j});
              }
              if (j - 1 >= 0)
              {
                char left_diag_forward = board[i - 1][j - 1]->getType();
                if (islower(left_diag_forward) and left_diag_forward != 'E' and left_diag_forward != 'e')
                {
                  whitePos_in_generate.emplace_back(Move{i, j, i - 1, j - 1});
                }
              }
              if (j + 1 < 8)
              {
                char right_diag_forward = board[i - 1][j + 1]->getType();
                if (islower(right_diag_forward) and right_diag_forward != 'E' and right_diag_forward != 'e')
                {
                  whitePos_in_generate.emplace_back(Move{i, j, i - 1, j + 1});
                }
              }
            }
            if (i - 2 >= 0)
            {
              char onebefore = board[i - 1][j]->getType();
              char twobefore = board[i - 2][j]->getType(); //check 是不是第一步
              if (board[i][j]->legalMove(i - 2, j))
              {
                if (onebefore == 'e' or onebefore == 'E')
                {
                  if (twobefore == 'e' or twobefore == 'E')
                  {
                    whitePos_in_generate.emplace_back(Move{i, j, i - 2, j});
                  }
                }
              }
            }
          }
          else
          { //black

            if (i + 1 < 8)
            {
              char onebefore = board[i + 1][j]->getType();
              if (onebefore == 'e' or onebefore == 'E')
              {
                blackPos_in_generate.emplace_back(Move{i, j, i + 1, j});
              }
              if (j - 1 >= 0)
              {
                char left_diag_forward = board[i + 1][j - 1]->getType();
                if (!islower(left_diag_forward) and left_diag_forward != 'E' and left_diag_forward != 'e')
                {
                  blackPos_in_generate.emplace_back(Move{i, j, i + 1, j - 1});
                }
              }
              if (j + 1 < 8)
              {
                char right_diag_forward = board[i + 1][j + 1]->getType();
                if (!islower(right_diag_forward) and right_diag_forward != 'E' and right_diag_forward != 'e')
                {
                  blackPos_in_generate.emplace_back(Move{i, j, i + 1, j + 1});
                }
              }
            }
            if (i + 2 < 8)
            {
              char onebefore = board[i + 1][j]->getType();
              char twobefore = board[i + 2][j]->getType(); //check 是不是第一步
              if (board[i][j]->legalMove(i + 2, j))
              {
                if (onebefore == 'e' or onebefore == 'E')
                {
                  if (twobefore == 'E' or twobefore == 'e')
                  {
                    blackPos_in_generate.emplace_back(Move{i, j, i + 2, j});
                  }
                }
              }
            }
          }
        }
        else if (t == 'q')
        { //queen
          //queen 这儿我就把横竖r的和斜着的b给直接合起来了
          for (int r = i - 1; r >= 0; r--)
          {
            char ty = board[r][j]->getType();
            if (!(ty == 'e' or ty == 'E'))
            {
              if (islower(ty) and !black)
              {
                whitePos_in_generate.emplace_back(Move{i, j, r, j});
              }
              else if (!islower(ty) and black)
              {
                blackPos_in_generate.emplace_back(Move{i, j, r, j});
              }
              break;
            }
            else
            {
              if (!black)
              {
                whitePos_in_generate.emplace_back(Move{i, j, r, j});
              }
              else
              {
                blackPos_in_generate.emplace_back(Move{i, j, r, j});
              }
            }
          }
          for (int r = i + 1; r < 8; r++)
          {
            char ty = board[r][j]->getType();
            if (!(ty == 'e' or ty == 'E'))
            {
              if (islower(ty) and !black)
              {
                whitePos_in_generate.emplace_back(Move{i, j, r, j});
              }
              else if (!islower(ty) and black)
              {
                blackPos_in_generate.emplace_back(Move{i, j, r, j});
              }
              break;
            }
            else
            {
              if (!black)
              {
                whitePos_in_generate.emplace_back(Move{i, j, r, j});
              }
              else
              {
                blackPos_in_generate.emplace_back(Move{i, j, r, j});
              }
            }
          }
          for (int c = j - 1; c >= 0; c--)
          {
            char ty = board[i][c]->getType();
            if (!(ty == 'e' or ty == 'E'))
            {
              if (islower(ty) and !black)
              {
                whitePos_in_generate.emplace_back(Move{i, j, i, c});
              }
              else if (!islower(ty) and black)
              {
                blackPos_in_generate.emplace_back(Move{i, j, i, c});
              }
              break;
            }
            else
            {
              if (!black)
              {
                whitePos_in_generate.emplace_back(Move{i, j, i, c});
              }
              else
              {
                blackPos_in_generate.emplace_back(Move{i, j, i, c});
              }
            }
          }
          for (int c = j + 1; c < 8; c++)
          {
            char ty = board[i][c]->getType();
            if (!(ty == 'e' or ty == 'E'))
            {
              if (islower(ty) and !black)
              {
                whitePos_in_generate.emplace_back(Move{i, j, i, c});
              }
              else if (!islower(ty) and black)
              {
                blackPos_in_generate.emplace_back(Move{i, j, i, c});
              }
              break;
            }
            else
            {
              if (!black)
              {
                whitePos_in_generate.emplace_back(Move{i, j, i, c});
              }
              else
              {
                blackPos_in_generate.emplace_back(Move{i, j, i, c});
              }
            }
          }

          //下面的是斜着的
          int do1 = 1; //
          int do2 = 1;
          int do3 = 1;
          int do4 = 1;
          for (int a = 1; a < 8; a++)
          {

            if (do1)
            {
              if (i + a < 8 and j + a < 8)
              {
                char ty = board[i + a][j + a]->getType();
                if ((islower(ty) or ty == 'E') and type == 'Q')
                {
                  whitePos_in_generate.emplace_back(Move{i, j, i + a, j + a});
                }
                if ((!islower(ty) or ty == 'e') and type == 'q')
                {
                  blackPos_in_generate.emplace_back(Move{i, j, i + a, j + a});
                }
                if (!(ty == 'e' or ty == 'E'))
                {
                  do1 = 0;
                }
              }
              else
              {
                do1 = 0;
              }
            }
            if (do2)
            {
              if (i + a < 8 and j - a >= 0)
              {
                char ty = board[i + a][j - a]->getType();
                if ((islower(ty) or ty == 'E') and type == 'Q')
                {
                  whitePos_in_generate.emplace_back(Move{i, j, i + a, j - a});
                }
                if ((!islower(ty) or ty == 'e') and type == 'q')
                {
                  blackPos_in_generate.emplace_back(Move{i, j, i + a, j - a});
                }
                if (!(ty == 'e' or ty == 'E'))
                {
                  do2 = 0;
                }
              }
              else
              {
                do2 = 0;
              }
            }
            if (do3)
            {
              if (i - a >= 0 and j - a >= 0)
              {
                char ty = board[i - a][j - a]->getType();
                if ((islower(ty) or ty == 'E') and type == 'Q')
                {
                  whitePos_in_generate.emplace_back(Move{i, j, i - a, j - a});
                }
                if ((!islower(ty) or ty == 'e') and type == 'q')
                {
                  blackPos_in_generate.emplace_back(Move{i, j, i - a, j - a});
                }
                if (!(ty == 'e' or ty == 'E'))
                {
                  do3 = 0;
                }
              }
              else
              {
                do3 = 0;
              }
            }
            if (do4)
            {
              if (i - a >= 0 and j + a < 8)
              {
                char ty = board[i - a][j + a]->getType();
                if ((islower(ty) or ty == 'E') and type == 'Q')
                {
                  whitePos_in_generate.emplace_back(Move{i, j, i - a, j + a});
                }
                if ((!islower(ty) or ty == 'e') and type == 'q')
                {
                  blackPos_in_generate.emplace_back(Move{i, j, i - a, j + a});
                }
                if (!(ty == 'e' or ty == 'E'))
                {
                  do4 = 0;
                }
              }
              else
              {
                do4 = 0;
              }
            }
          }
        }

        else if (t == 'b')
        { // bishop
          //记得check castle, 我觉得可以check同时king和Rook的legalMove都是true然后中间
          //两个中间没有棋子，King的位置我是有存的，你看board.h

          int do1 = 1;
          int do2 = 1;
          int do3 = 1;
          int do4 = 1;
          for (int a = 1; a < 8; a++)
          {

            if (do1)
            {
              if (i + a < 8 and j + a < 8)
              {
                char ty = board[i + a][j + a]->getType();
                if ((islower(ty) or ty == 'E') and type == 'B')
                {
                  whitePos_in_generate.emplace_back(Move{i, j, i + a, j + a});
                }
                if ((!islower(ty) or ty == 'e') and type == 'b')
                {
                  blackPos_in_generate.emplace_back(Move{i, j, i + a, j + a});
                }
                if (ty != 'e' and ty != 'E')
                {
                  do1 = 0;
                }
              }
              else
              {
                do1 = 0;
              }
            }
            if (do2)
            {
              if (i + a < 8 and j - a >= 0)
              {
                char ty = board[i + a][j - a]->getType();
                if ((islower(ty) or ty == 'E') and type == 'B')
                {
                  whitePos_in_generate.emplace_back(Move{i, j, i + a, j - a});
                }
                if ((!islower(ty) or ty == 'e') and type == 'b')
                {
                  blackPos_in_generate.emplace_back(Move{i, j, i + a, j - a});
                }
                if (ty != 'e' and ty != 'E')
                {
                  do2 = 0;
                }
              }
              else
              {
                do2 = 0;
              }
            }
            if (do3)
            {
              if (i - a >= 0 and j - a >= 0)
              {
                char ty = board[i - a][j - a]->getType();
                if ((islower(ty) or ty == 'E') and type == 'B')
                {
                  whitePos_in_generate.emplace_back(Move{i, j, i - a, j - a});
                }
                if ((!islower(ty) or ty == 'e') and type == 'b')
                {
                  blackPos_in_generate.emplace_back(Move{i, j, i - a, j - a});
                }
                if (ty != 'e' and ty != 'E')
                {
                  do3 = 0;
                }
              }
              else
              {
                do3 = 0;
              }
            }
            if (do4)
            {
              if (i - a >= 0 and j + a < 8)
              {
                char ty = board[i - a][j + a]->getType();
                if ((islower(ty) or ty == 'E') and type == 'B')
                {
                  whitePos_in_generate.emplace_back(Move{i, j, i - a, j + a});
                }
                if ((!islower(ty) or ty == 'e') and type == 'b')
                {
                  blackPos_in_generate.emplace_back(Move{i, j, i - a, j + a});
                }
                if (ty != 'e' and ty != 'E')
                {
                  do4 = 0;
                }
              }
              else
              {
                do4 = 0;
              }
            }
          }
        }
      }
    }
  }
  if (generateWhite)
  {
    return whitePos_in_generate;
  }
  else
  {
    return blackPos_in_generate;
  }
}

Board::~Board()
{
  for (int i = 0; i < 8; i++)
  {
    for (int j = 0; j < 8; j++)
    {
      delete board[i][j];
    }
  }
  board.clear();
  delete td;
  whitePos.clear();
  blackPos.clear();
  bEnPassant.clear();
  wEnPassant.clear();
}

std::ostream &operator<<(std::ostream &out, const Board &b)
{
  out << *(b.td);
  return out;
}

void Board::printpossiblemove()
{
  int size = blackPos.size();
  cout << "black" << endl;
  for (int i = 0; i < size; i++)
  {
   cout << board[blackPos[i].startR][blackPos[i].startC]->getType() << " ";
   cout << blackPos[i].startR << "/" << blackPos[i].startC << "--->" << blackPos[i].endR << "/" << blackPos[i].endC << endl;
  }
  cout << "white" << endl;
  size = whitePos.size();
  for (int i = 0; i < size; i++)
  {
    //cout << board[whitePos[i].startR][whitePos[i].startC]->getType();
    //cout << whitePos[i].startR << "/" << whitePos[i].startC << "--->" << whitePos[i].endR << "/" << whitePos[i].endC << endl;
  }
}

