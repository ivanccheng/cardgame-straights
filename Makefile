CXX = g++
CXXFLAGS = -std=c++14 -g -Werror=vla -Wall -MMD
OBJECTS = card.o computer.o deck.o game.o human.o player.o table.o exception.o controller.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = straights

${EXEC} : ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

clean :
	del ${DEPENDS} ${OBJECTS} ${EXEC}

-include ${DEPENDS} # reads the .d files and reruns dependencies

