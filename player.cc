#include "player.h"
#include <iostream>

Player::Player():isWhite{true}, isAI{false}{}

Player::Player(bool isWhite, bool isAI):isWhite{isWhite}, isAI{isAI}{}

Move Player::makeMove(Board& b){return Move{0, 0, 0, 0};}

Player::~Player(){}
