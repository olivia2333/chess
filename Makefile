CXX = g++
CXXFLAGS = -std=c++14 -Wall -MMD -Werror=vla -g
EXEC = chess -lX11
OBJECTS = main.o textdisplay.o board.o game.o chess.o bishop.o king.o knight.o noChess.o\
pawn.o queen.o rook.o subject.o player.o AIplayer.o scoreBoard.o GraphicsDisplay.o\
window.o
DEPENDS = ${OBJECTS:.o=.d}

${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}
