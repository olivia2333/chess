#include <iostream>
#include <string>
// You may include other allowed headers, as needed
#include "game.h"
#include "GraphicsDisplay.h"
#include <sstream>
#include "scoreBoard.h"
using namespace std;

int main(int argc, char *argv[])
{
	cin.exceptions(ios::eofbit | ios::failbit);
	string cmd;
	ScoreBoard s;
	GraphicsDisplay *graphics;

	cout << "Do you want the game in text mode or graphic mode?" << endl;
	cout << "1 for text, 2 for graphic: ";
	int text;
	while (1)
	{
		try
		{
			cin >> text;
			if (cin.fail())
			{
				cin.clear();
				cin.ignore();
				throw(1);
			}
			if (text != 1 and text != 2)
			{
				throw 2;
			}
			break;
		}
		catch (ios::failure &)
		{
			cin.clear();
			cin.ignore();
			cout << "please input a number (1 text, 2 graphic):";
		}
		catch (int i)
		{
			if (i == 1)
			{
				cout << "please input a number (1 text, 2 graphic):";
			}
			else
			{
				cout << "please enter 1(text) or 2(graphic): ";
			}
		}
	}

	Game g;

	try
	{
		if (text == 1)
		{
			cout << "                       CHESS          " << endl;
			cout << "1. to customize board, enter 'setup'" << endl;
			cout << "2. to start the game, enter game (whiteplayer) (blackplayer)" << endl;
			cout << "   each player should be human or computer[i] (i = 1, 2 or 3)" << endl;
			while (1)
			{
				cin >> cmd;
				if (cmd == "setup")
				{
					cout << endl;
					cout << "          	  SETUP MODE  " << endl;
					cout << "*note: uppercase is white side, lower case is black side" << endl;
					cout << "1. to place a new piece, enter + (chesstype) (location)" << endl;
					cout << "   e.g. '+ K e2'" << endl;
					cout << "2. to delete a piece, enter - (location)" << endl;
					cout << "   e.g. '- e7'" << endl;
					cout << "3. to change the start side, enter = (color)" << endl;
					cout << "   e.g. '= black'" << endl;
					cout << "3. when finish setup, enter  done" << endl;
					cout << endl;
					cout << g;
					g.setStatus("setup");
					while (true)
					{
						cin >> cmd;
						if (cmd == "+")
						{
							char piece;
							cin >> piece;
							string cell;
							cin >> cell;
							g.set(piece, cell);
							cout << g;
						}
						else if (cmd == "-")
						{
							string cell;
							cin >> cell;
							g.set('-', cell);
							cout << g;
						}
						else if (cmd == "=")
						{
							string color;
							cin >> color;
							if (color == "black")
							{
								g.setPlayers('c', 1);
							}
							else if (color == "white")
							{
								g.setPlayers('c', 0);
							}
						}
						else if (cmd == "done")
						{
							if (g.valid())
							{
								cout << endl;
								cout << "valid board! game is about to start!" << endl;
								cout << "** to start the game, enter game (whiteplayer) (blackplayer)" << endl;
								cout << "   each player should be human or computer[i] (i = 1, 2 or 3)" << endl;
								cout << endl;
								break;
							}
							else
							{
								cout << "board is not valid" << endl;
								cout << "1. there must be exactly one white king and one black king" << endl;
								cout << "2. pawns cannot be in the first and last row" << endl;
								cout << "3. neither king can be checked" << endl;
								cout << endl;
							}
						}
					}
				}
				else if (cmd == "game")
				{
					try
					{
						while (true)
						{
							while (true)
							{
								string player;

								cin >> player;
								if (!cin.fail() and player == "human")
								{
									g.setPlayers('w', 0);
								}
								else if (!cin.fail() and player.substr(0, 8) == "computer")
								{
									string l = player.substr(9, 1);
									istringstream iss(l);
									int level;
									iss >> level;
									cout << level << endl;
									if (iss.fail())
									{
										iss.clear();
										throw(1);
									}
									g.setPlayers('w', level);
								}
								else
								{
									throw(1);
								}
								cin >> player;
								if (!cin.fail() and player == "human")
								{
									g.setPlayers('b', 0);
								}
								else if (!cin.fail() and player.substr(0, 8) == "computer")
								{
									string l = player.substr(9, 1);
									istringstream iss(l);
									int level;
									iss >> level;
									if (iss.fail())
									{
										iss.clear();
										throw(2);
									} else if (player.substr(8, 1) != "[" or player.substr(10, 1) != "]"){
										throw(2);
									}
									g.setPlayers('b', level);
								}
								else
								{
									throw(2);
								}
								break;
							}

							cout << endl;
							cout << "			BASIC RULES       " << endl;
							cout << "1. move in a human player turn, enter: 'move (start) (end)'" << endl;
							cout << "  e.g. move e7 e5" << endl;
							cout << "2. move in a computer player turn, enter: 'move'" << endl;
							cout << "3. to resign in your turn, enter: 'resign'" << endl;
							cout << endl;
							cout << g;
							g.setStatus("active");
							while (g.getStatus() == "active" or g.getStatus() == "blackChecked" or
								   g.getStatus() == "whiteChecked")
							{
								if (!g.canMove())
								{
									g.setStatus("draw");
									break;
								}
								cin >> cmd;
								if (cmd == "resign")
								{
									if (g.currentWhite())
									{
										cout << endl;
										cout << "Black wins!" << endl;
										cout << endl;
										s.changeScore("whiteCheckmate");
									}
									else
									{
										cout << endl;
										cout << "White wins!" << endl;
										cout << endl;
										s.changeScore("blackCheckmate");
									}
									throw(3);
								}
								if (cmd == "move")
								{
									if (!g.currentAI())
									{
										try
										{
											string start;
											string end;
											cin >> start;
											cin >> end;
											g.setStatus("active");
											g.makeMove(start, end);
											if (g.getStatus() == "blackChecked")
											{
												cout << endl;
												cout << "Black is in check." << endl;
												cout << endl;
											}
											else if (g.getStatus() == "whiteChecked")
											{
												cout << endl;
												cout << "White is in check." << endl;
												cout << endl;
											}
											g.setPlayers('c', 2);
											cout << g;
										}
										catch (out_of_range)
										{
											cout << endl;
											cout << "invalid move" << endl;
											cout << endl;
										}
									}
									else
									{
										g.setStatus("active");
										while (true){
											try{
												g.AImove();
												break;
											} catch (out_of_range){}
										} 

										if (g.getStatus() == "blackChecked")
										{
											cout << endl;
											cout << "Black is in check." << endl;
											cout << endl;
										}
										else if (g.getStatus() == "whiteChecked")
										{
											cout << endl;
											cout << "White is in check." << endl;
											cout << endl;
										}
										g.setPlayers('c', 2);
										cout << g;
									}
								}
							}
							if (g.getStatus() == "blackCheckmate")
							{
								cout << endl;
								cout << "checkmate! White wins!" << endl;
								cout << endl;
								s.changeScore("blackCheckmate");
								break;
							}
							else if (g.getStatus() == "whiteCheckmate")
							{
								cout << endl;
								cout << "checkmate! Black wins!" << endl;
								cout << endl;
								s.changeScore("whiteCheckmate");
								break;
							}
							else if (g.getStatus() == "draw")
							{
								cout << endl;
								cout << "Stalemate!" << endl;
								cout << endl;
								s.changeScore("draw");
								break;
							}
							else if (g.getStatus() == "black wins")
							{
								cout << endl;
								cout << "Black wins!" << endl;
								cout << endl;
								s.changeScore("whiteCheckmate");
								break;
							}
							else if (g.getStatus() == "white wins")
							{
								cout << endl;
								cout << "White wins" << endl;
								cout << endl;
								s.changeScore("blackCheckmate");
								break;
							}
						}
					}
					catch (int n)
					{
						if (n == 1 or n == 2)
						{
							cout << "please enter the information for players again:" << endl;
							cout << "	'game (whiteplayer) (blackplayer)'" << endl;
						}
						if (n == 3)
						{
							cout << endl;
							cout << "1. To start a new game with the previous board, " << endl;
							cout << "enter 'game (whiteplayer) (blackplayer)" << endl;
							cout << "2. To check your score, enter 'score'" << endl;
							cout << "3. To exit the game and check score, press ctrl D" << endl;
							cout << "4. To setup based on the previous board before new game, enter 'setup'" << endl;
							cout << endl;
							g.reset();
						}
					}
				}
				else if (cmd == "score")
				{
					cout << s;
					cout << endl;
					cout << "1. To start a new game with the previous board, " << endl;
					cout << "enter 'game (whiteplayer) (blackplayer)" << endl;
					cout << "2. To check your score, enter 'score'" << endl;
					cout << "3. To exit the game and check score, press ctrl D" << endl;
					cout << "4. To setup based on the previous board before new game, enter 'setup'" << endl;
					cout << endl;
				}
				else
				{
					cout << "invalid command, please enter valid command" << endl;
				}
			}
		}
		else
		{
			graphics = new GraphicsDisplay{600, 8};
			g.setObserver(graphics);
			graphics->drawNotice("Start");
			while (1)
			{
				cin >> cmd;
				if (cmd == "setup")
				{
					graphics->drawNotice("Setup");
					g.setStatus("setup");
					while (true)
					{
						cin >> cmd;
						if (cmd == "+")
						{
							char piece;
							cin >> piece;
							string cell;
							cin >> cell;
							g.set(piece, cell);
						}
						else if (cmd == "-")
						{
							string cell;
							cin >> cell;
							g.set('-', cell);
						}
						else if (cmd == "=")
						{
							string color;
							cin >> color;
							if (color == "black")
							{
								g.setPlayers('c', 1);
							}
							else if (color == "white")
							{
								g.setPlayers('c', 0);
							}
						}
						else if (cmd == "done")
						{
							if (g.valid())
							{
								graphics->drawNotice("boardValid");
								break;
							}
							else
							{
								graphics->drawNotice("boardInvalid");
							}
						}
					}
				}
				else if (cmd == "game")
				{
					try
					{
						while (true)
						{
							while (true)
							{
								string player;

								cin >> player;
								if (!cin.fail() and player == "human")
								{
									g.setPlayers('w', 0);
								}
								else if (!cin.fail() and player.substr(0, 8) == "computer")
								{
									string l = player.substr(9, 1);
									istringstream iss(l);
									int level;
									iss >> level;
									if (iss.fail())
									{
										iss.clear();
										throw(1);
									} else if (player.substr(8, 1) != "[" or player.substr(10, 1) != "]"){
										throw(2);
									}
									g.setPlayers('w', level);
								}
								else
								{
									throw(1);
								}
								cin >> player;
								if (!cin.fail() and player == "human")
								{
									g.setPlayers('b', 0);
								}
								else if (!cin.fail() and player.substr(0, 8) == "computer")
								{
									string l = player.substr(9, 1);
									istringstream iss(l);
									int level;
									iss >> level;
									if (iss.fail())
									{
										iss.clear();
										throw(2);
									} else if (player.substr(8, 1) != "[" or player.substr(10, 1) != "]"){
										throw(2);
									}
									g.setPlayers('b', level);
								}
								else
								{
									throw(2);
								}
								break;
							}
							graphics->drawNotice("Basic");
							g.setStatus("active");
							while (g.getStatus() == "active" or g.getStatus() == "blackChecked" or
								   g.getStatus() == "whiteChecked")
							{
								if (!g.canMove())
								{
									g.setStatus("draw");
									break;
								}
								cin >> cmd;
								if (cmd == "resign")
								{
									if (g.currentWhite())
									{
										graphics->drawNotice("blackWin");
										s.changeScore("whiteCheckmate");
									}
									else
									{
										graphics->drawNotice("whiteWin");
										s.changeScore("blackCheckmate");
									}
									throw(3);
								}
								if (cmd == "move")
								{
									if (!g.currentAI())
									{
										try
										{
											string start;
											string end;
											cin >> start;
											cin >> end;
											g.setStatus("active");
											g.makeMove(start, end);
											if (g.getStatus() == "blackChecked")
											{
												graphics->drawNotice("checkBlack");
											}
											else if (g.getStatus() == "whiteChecked")
											{
												graphics->drawNotice("checkWhite");
											}
											g.setPlayers('c', 2);
										}
										catch (out_of_range)
										{
											graphics->drawNotice("invalidMove");
										}
									}
									else
									{
										g.setStatus("active");
										while (true){
											try{
												g.AImove();
												break;
											} catch (out_of_range){}
										} 
										if (g.getStatus() == "blackChecked")
										{
											graphics->drawNotice("checkBlack");
										}
										else if (g.getStatus() == "whiteChecked")
										{
											graphics->drawNotice("checkWhite");
										}
										g.setPlayers('c', 2);
									}
								}
							}
							if (g.getStatus() == "blackCheckmate")
							{
								graphics->drawNotice("blackCheckmate");
								s.changeScore("blackCheckmate");
							}
							else if (g.getStatus() == "whiteCheckmate")
							{
								graphics->drawNotice("whiteCheckmate");
								s.changeScore("whiteCheckmate");
							}
							else if (g.getStatus() == "draw")
							{
								graphics->drawNotice("Stalemate");
								s.changeScore("draw");
							}
							else if (g.getStatus() == "black wins")
							{
								graphics->drawNotice("blackWin");
								s.changeScore("whiteCheckmate");
							}
							else if (g.getStatus() == "white wins")
							{
								graphics->drawNotice("whiteWin");
								s.changeScore("blackCheckmate");
							}
						}
						graphics->displayScore(s);
					}
					catch (int n)
					{
						if (n == 1 or n == 2)
						{
							graphics->drawNotice("playerInvalid");
						}
						if (n == 3)
						{
							g.reset();
							g.setObserver(graphics);
							graphics->reset();
							graphics->drawNotice("oneRound");
						}
					}
				}
				else if (cmd == "score")
				{
					graphics->displayScore(s);
				}
				else
				{
					graphics->drawNotice("commandInvalid");
				}
			}
		}
	}
	catch (ios::failure &)
	{
		if (text == 1)
		{
			cout << s;
		}
		else
		{
			graphics->displayScore(s);
			delete graphics;
		}
	}
}

