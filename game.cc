#include "game.h"
#include <sstream>
using namespace std;

Game::Game(){
	board = new Board{};
	players[0] = new Player{true, false};
	players[1] = new Player{false, false};
	current = players[0];
}

void Game::setPlayers(char type, int level){
	bool curr = false;
	if (type == 'w'){
		if (current == players[0]){curr = true;}
		if (level == 0){
			delete players[0];
			players[0] = new Player{true, false};
		} else {
			delete players[0];
			players[0] = new AIplayer{true, true, level};
		}
		if (curr == true){
			current = players[0];
		}
	} else if (type == 'b') {
		if (current == players[1]){curr = true;}
		if (level == 0){
			delete players[1];
			players[1] = new Player{false, false};
		} else {
			delete players[1];
			players[1] = new AIplayer{false, true, level};
		} 
		if (curr == true){
			current = players[1];
		}
	} else if(type == 'c' and level == 0){
		current = players[0];
	} else if (type == 'c' and level == 1) {
		current = players[1];
	} else if (type == 'c'){
		if (current == players[1]){
			current = players[0];
		} else{
			current = players[1];
		}
	}
}

void Game::reset(){
	delete board;
	board = new Board{};
	delete players[0];
	delete players[1];
	players[0] = new Player{true, false};
	players[1] = new Player{false, false};
	current = players[0];
}

bool Game::currentAI(){
	return current->isAI;
}

void Game::AImove(){
	Move m = current->makeMove(*board);
	makeMove(m.startR, m.startC, m.endR, m.endC);
}

bool Game::currentWhite(){
	if(current->isWhite){
		return true;
	} else {
		return false;
	}
}

string Game::getStatus(){
	return status;
}

void Game::setStatus(string s){
	status = s;
}

void Game::set(char piece, std::string cell){
	char column;
    int col;
    int row;
    istringstream iss(cell);
    iss >> column;
    iss >> row;
    row = 8 - row;
    col = column - 'a';

	board->set(piece, row, col);
}

void Game::setObserver(Observer* ob){
	board->setObserver(ob);
}

bool Game::valid() {
	return board->valid();
}

void Game::kingChecked(){
	if (board->whiteCheckmate()){
		setStatus("whiteCheckmate");
	} else if (board->blackCheckmate()){
		setStatus("blackCheckmate");
	}
}

void Game::makeMove(int startR, int startC, int endR, int endC){
	try{
		if (current->isWhite){
			board->makeMove('w', startR, startC, endR, endC);
		} else {
			board->makeMove('b', startR, startC, endR, endC);
		}
	} catch(string s){
		if(s == "no moves"){
			setStatus("draw");
		} else if(s == "blackCheckmate"){
			setStatus("blackCheckmate");
		} else if(s == "blackChecked"){
			setStatus("blackChecked");
		} else if(s =="whiteCheckmate"){
			setStatus("whiteCheckmate");
		} else if(s == "whiteChecked"){
			setStatus("whiteChecked");
		} else if(s == "black wins"){
			setStatus("blackWin");
		} else if(s == "white wins"){
			setStatus("whiteWin");
		}
	}
}

void Game::makeMove(string start, string end){
	char sC;
	int startR;
	int startC;
	char eC;
	int endC;
	int endR;
	istringstream iss(start);
	iss >> sC;
	startC = sC - 'a';
	iss >> startR;
	startR = 8-startR;

	istringstream iss1(end);
	iss1 >> eC;
	endC = eC - 'a';
	iss1 >> endR;
	endR = 8-endR;

	try{
		if (current->isWhite){
			board->makeMove('w', startR, startC, endR, endC);
		} else {
			board->makeMove('b', startR, startC, endR, endC);
		}
	} catch(string s){
		if(s == "no moves"){
			setStatus("draw");
		} else if(s == "blackCheckmate"){
			setStatus("blackCheckmate");
		} else if(s == "blackChecked"){
			setStatus("blackChecked");
		} else if(s =="whiteCheckmate"){
			setStatus("whiteCheckmate");
		} else if(s == "whiteChecked"){
			setStatus("whiteChecked");
		}
	}
}

bool Game::canMove(){
	if (current == players[0]){
		vector<Move> testBlack = board->generateMove(false);
		testBlack = board->castlingMove(testBlack, false);
		vector<Move> testWhite = board->generateMove(true);
		testWhite = board->legalizeMove(board->castlingMove(testWhite, true), true);
		if (testWhite.size() == 0){
			return false;
		} else {
			return true;
		}
	} else {
		vector<Move> testWhite = board->generateMove(true);
		testWhite = board->castlingMove(testWhite, true);
		vector<Move> testBlack = board->generateMove(false);
		testBlack = board->legalizeMove(board->castlingMove(testBlack, false), false);
		if (testBlack.size() == 0){
			return false;
		} else {
			return true;
		}
	}
}

ostream &operator<<(std::ostream &out, const Game &g) {
	out << *(g.board);
	return out;
}

Game::~Game(){
	delete board;
	delete players[0];
	delete players[1];
}

/*
void Game::printPos(){
	board->printpossiblemove();
}*/

