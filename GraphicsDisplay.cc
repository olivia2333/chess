#include "GraphicsDisplay.h"
#include <sstream>
#include <unistd.h>

using namespace std;

// ctor
GraphicsDisplay::GraphicsDisplay(int windowLen, int gridSize):
windowLen{windowLen}, cellLen{500/8}{
    reset();
}

void GraphicsDisplay::reset(){
    for(int i = 0; i < 8; i++){
            for (int j = 0; j < 8; j++){
                if ((i % 2 == 0 and j % 2 == 0) or 
                    (i % 2 != 0 and j % 2 != 0)){
                    win.fillRectangle(j * cellLen, i * cellLen, cellLen, cellLen, Xwindow::White);
                } else {
                    win.fillRectangle(j * cellLen, i * cellLen, cellLen, cellLen, Xwindow::Gray);
                }
            }
        }

    for (int i = 1; i < 9; i++){
            for (int j = 0; j < 8; j++) {
                    if (i == 1){
                            if (j == 0 or j == 7){
                                    win.drawString((j+0.5)*cellLen, (i-0.5)*cellLen, "r", Xwindow::Black);
                            } else if (j == 1 or j == 6){
                                    win.drawString((j+0.5)*cellLen, (i-0.5)*cellLen, "n", Xwindow::Black);
                            } else if (j == 2 or j == 5){
                                    win.drawString((j+0.5)*cellLen, (i-0.5)*cellLen, "b", Xwindow::Black);
                            } else if (j == 3) {
                                    win.drawString((j+0.5)*cellLen, (i-0.5)*cellLen, "q", Xwindow::Black);
                            } else {
                                    win.drawString((j+0.5)*cellLen, (i-0.5)*cellLen, "k", Xwindow::Black);
                            }
                    } else if (i == 2){
                            win.drawString((j+0.5)*cellLen, (i-0.5)*cellLen, "p", Xwindow::Black);
                    } else if (i == 7){
                            win.drawString((j+0.5)*cellLen, (i-0.5)*cellLen, "P", Xwindow::Wheat);
                    } else if (i == 8){
                            if (j == 0 or j == 7){
                                    win.drawString((j+0.5)*cellLen, (i-0.5)*cellLen, "R", Xwindow::Wheat);
                            } else if (j == 1 or j == 6){
                                    win.drawString((j+0.5)*cellLen, (i-0.5)*cellLen, "N", Xwindow::Wheat);
                            } else if (j == 2 or j == 5){
                                    win.drawString((j+0.5)*cellLen, (i-0.5)*cellLen, "B", Xwindow::Wheat);
                            } else if (j == 3) {
                                    win.drawString((j+0.5)*cellLen, (i-0.5)*cellLen, "Q", Xwindow::Wheat);
                            } else {
                                    win.drawString((j+0.5)*cellLen, (i-0.5)*cellLen, "K", Xwindow::Wheat);
                            }
                    } 
            }
    }
    win.fillRectangle(0, 500, 500, 100, Xwindow::White);

}

// notify(whoNotified) changes the display color according to the information
//      of whoNotified
void GraphicsDisplay::notify(Subject &board){
    win.fillRectangle(0, 500, 500, 100, Xwindow::White);
    InfoType i = board.getState();
    string type = i.type;
    char piece = i.piece;
    string s(1, piece); 
    int startR = i.startR;
    int startC = i.startC;
    int endR = i.endR;
    int endC = i.endC;

    if (type == "set"){
        if (startC < 8 and startC >= 0 and startR >= 0 and startR < 8){
            if ((startC % 2 == 0 and startR % 2 == 0) or
                (startC % 2 != 0 and startR % 2 != 0)) {
                win.fillRectangle(startC*cellLen, startR*cellLen, cellLen, cellLen, Xwindow::White);
            } else {
                win.fillRectangle(startC*cellLen, startR*cellLen, cellLen, cellLen, Xwindow::Gray);
            }
            if(piece == '-') {
               if ((startC % 2 == 0 and startR % 2 == 0) or
                    (startC % 2 != 0 and startR % 2 != 0)) {
                    win.fillRectangle(startC*cellLen, startR*cellLen, cellLen, cellLen, Xwindow::White);
                } else {
                    win.fillRectangle(startC*cellLen, startR*cellLen, cellLen, cellLen, Xwindow::Gray);
                }           
            }else if(islower(piece)){
                win.drawString((startC+0.5)*cellLen, (startR+0.5)*cellLen, s, Xwindow::Black);
            } else{
                win.drawString((startC+0.5)*cellLen, (startR+0.5)*cellLen, s, Xwindow::Wheat);
            }
        }
    } else if (type == "move"){
        if ((startC % 2 == 0 and startR % 2 == 0) or
            (startC % 2 != 0 and startR % 2 != 0)) {
            win.fillRectangle(startC*cellLen, startR*cellLen, cellLen, cellLen, Xwindow::White);
        } else {
            win.fillRectangle(startC*cellLen, startR*cellLen, cellLen, cellLen, Xwindow::Gray);
        }
        if ((endC % 2 == 0 and endR % 2 == 0) or
            (endC % 2 != 0 and endR % 2 != 0)) {
            win.fillRectangle(endC*cellLen, endR*cellLen, cellLen, cellLen, Xwindow::White);
        } else {
            win.fillRectangle(endC*cellLen, endR*cellLen, cellLen, cellLen, Xwindow::Gray);
        }
        if(islower(piece)){
            win.drawString((endC+0.5)*cellLen, (endR+0.5)*cellLen, s, Xwindow::Black);
        } else{
            win.drawString((endC+0.5)*cellLen, (endR+0.5)*cellLen, s, Xwindow::Wheat);
        }
    } else if (type == "enPassant"){
        if ((startC % 2 == 0 and startR % 2 == 0) or
            (startC % 2 != 0 and startR % 2 != 0)) {
            win.fillRectangle(startC*cellLen, startR*cellLen, cellLen, cellLen, Xwindow::White);
        } else {
            win.fillRectangle(startC*cellLen, startR*cellLen, cellLen, cellLen, Xwindow::Gray);
        }
        if ((endC % 2 == 0 and startR % 2 == 0) or
            (endC % 2 != 0 and startR % 2 != 0)) {
            win.fillRectangle(endC*cellLen, startR*cellLen, cellLen, cellLen, Xwindow::White);
        } else {
            win.fillRectangle(endC*cellLen, startR*cellLen, cellLen, cellLen, Xwindow::Gray);
        }
        if ((endC % 2 == 0 and endR % 2 == 0) or
            (endC % 2 != 0 and endR % 2 != 0)) {
            win.fillRectangle(endC*cellLen, endR*cellLen, cellLen, cellLen, Xwindow::White);
        } else {
            win.fillRectangle(endC*cellLen, endR*cellLen, cellLen, cellLen, Xwindow::Gray);
        }
        if(islower(piece)){
            win.drawString((endC+0.5)*cellLen, (endR+0.5)*cellLen, s, Xwindow::Black);
        } else{
            win.drawString((endC+0.5)*cellLen, (endR+0.5)*cellLen, s, Xwindow::Wheat);
        }
    } else if (type == "castling"){
        int casSR = i.casSR;
        int casSC = i.casSC;
        int casER = i.casER;
        int casEC = i.casEC;
        if ((startC % 2 == 0 and startR % 2 == 0) or
            (startC % 2 != 0 and startR % 2 != 0)) {
            win.fillRectangle(startC*cellLen, startR*cellLen, cellLen, cellLen, Xwindow::White);
        } else {
            win.fillRectangle(startC*cellLen, startR*cellLen, cellLen, cellLen, Xwindow::Gray);
        }
        if ((casSC % 2 == 0 and casSR % 2 == 0) or
            (casSC % 2 != 0 and casSR % 2 != 0)) {
            win.fillRectangle(casSC*cellLen, casSR*cellLen, cellLen, cellLen, Xwindow::White);
        } else {
            win.fillRectangle(casSC*cellLen, casSR*cellLen, cellLen, cellLen, Xwindow::Gray);
        }
        if(islower(piece)){
            string r(1, 'r');
            win.drawString((casEC+0.5)*cellLen, (casER+0.5)*cellLen, r, Xwindow::Black);
            win.drawString((endC+0.5)*cellLen, (endR+0.5)*cellLen, s, Xwindow::Black);
        } else {
            string r(1, 'R');
            win.drawString((casEC+0.5)*cellLen, (casER+0.5)*cellLen, r, Xwindow::Wheat);
            win.drawString((endC+0.5)*cellLen, (endR+0.5)*cellLen, s, Xwindow::Wheat);
        }
    }
        
}

void GraphicsDisplay::drawNotice(std::string step){
    win.fillRectangle(0, 500, 500, 100, Xwindow::White);
    if(step == "Start"){
        win.drawString(75, 525, "                       CHESS          ", Xwindow::Black);
        win.drawString(75, 540, "1. to customize board, enter 'setup'", Xwindow::Black);
        win.drawString(75, 555, "2. to start the game, enter game (whiteplayer) (blackplayer)", Xwindow::Black);
        win.drawString(75, 570, "   each player should be human or computer[i] (i = 1, 2 or 3)", Xwindow::Black);
    } else if(step == "Setup"){
        win.drawString(75, 510, "                SETUP MODE  ", Xwindow::Black);
        win.drawString(75, 520, "*note: uppercase is white side, lower case is black side", Xwindow::Black);
        win.drawString(75, 530, "1. to place a new piece, enter + (chesstype) (location)", Xwindow::Black);
        win.drawString(75, 540, "   e.g. '+ K e2'", Xwindow::Black);
        win.drawString(75, 550, "2. to delete a piece, enter - (location)", Xwindow::Black);
        win.drawString(75, 560, "   e.g. '- e7'", Xwindow::Black);
        win.drawString(75, 570, "3. to change the start side, enter = (color)", Xwindow::Black);
        win.drawString(75, 580, "   e.g. '= black'", Xwindow::Black);
    } else if(step == "boardInvalid"){
        win.drawString(75, 525, "board is not valid", Xwindow::Black);
        win.drawString(75, 540, "1. there must be exactly one white king and one black king", Xwindow::Black);
        win.drawString(75, 555, "2. pawns cannot be in the first and last row", Xwindow::Black);
        win.drawString(75, 570, "3. neither king can be checked", Xwindow::Black);
    } else if(step == "boardValid"){
        win.drawString(75, 525, "valid board! game is about to start!", Xwindow::Black);
        win.drawString(75, 540, "** to start the game, enter game (whiteplayer) (blackplayer)", Xwindow::Black);
        win.drawString(75, 555, "   each player should be human or computer[i] (i = 1, 2 or 3)", Xwindow::Black);
        win.drawString(75, 585, "** black side is blue pieces, white side is red pieces", Xwindow::Black);
    } else if(step == "Basic"){
        win.drawString(75, 525, "               BASIC RULES       ", Xwindow::Black);
        win.drawString(75, 540, "1. move in a human player turn, enter: 'move (start) (end)'", Xwindow::Black);
        win.drawString(75, 555, "  e.g. move e7 e5", Xwindow::Black);
        win.drawString(75, 570, "2. move in a computer player turn, enter: 'move'" , Xwindow::Black);
        win.drawString(75, 585, "3. to resign in your turn, enter: 'resign'", Xwindow::Black);
    } else if(step == "blackWin"){
        win.drawString(200, 550, "Black wins!" , Xwindow::Black);
        usleep(1000000);
    } else if(step == "whiteWin"){
        win.drawString(200, 550, "White wins!" , Xwindow::Black);
        usleep(1000000);
    } else if(step == "checkBlack"){
        win.drawString(200, 550, "Black is in check." , Xwindow::Black);
    } else if(step == "checkWhite"){
        win.drawString(200, 550, "White is in check." , Xwindow::Black);
    } else if(step == "invalidMove"){
        win.drawString(200, 550, "invalid move" , Xwindow::Black);
    } else if(step == "blackCheckmate"){
        win.drawString(200, 550, "checkmate! White wins!" , Xwindow::Black);
        usleep(1000000);
    } else if(step == "whiteCheckmate"){
        win.drawString(200, 550, "checkmate! Black wins!" , Xwindow::Black);
        usleep(1000000);
    } else if(step == "Stalemate"){
        win.drawString(200, 550, "Stalemate!" , Xwindow::Black);
    } else if(step == "playerInvalid"){
        win.drawString(75, 545, "please enter the information for players again:" , Xwindow::Black);
        win.drawString(75, 555, "  'game (whiteplayer) (blackplayer)'" , Xwindow::Black);
    } else if(step == "oneRound"){
        win.drawString(75, 525, "1. To start a new game, enter 'game (whiteplayer) (blackplayer)" , Xwindow::Black);
        win.drawString(75, 540, "2. To check your score, enter 'score'", Xwindow::Black);
        win.drawString(75, 555, "3. To exit the game and check score, press ctrl D" , Xwindow::Black);
        win.drawString(75, 570, "4. To setup before new game, enter 'setup'", Xwindow::Black);
    } else if(step == "commandInvalid"){
        win.drawString(75, 550, "invalid command, please enter valid command" , Xwindow::Black);
    }
}

void GraphicsDisplay::displayScore(ScoreBoard &s){
    win.fillRectangle(0, 500, 500, 100, Xwindow::White);
    win.drawString(220, 540, "Final Score:" , Xwindow::Black);
    ostringstream os1;
    os1 << "White: " << s.whiteScore;
    string white = os1.str();
    ostringstream os2;
    os2 << "Black: " << s.blackScore;
    string black = os2.str();
    win.drawString(220, 555, white, Xwindow::Black);
    win.drawString(220, 570, black, Xwindow::Black);
    usleep(2500000);
}
