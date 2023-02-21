CXX=g++
CXXFLAGS=-std=c++14 -MMD
OBJECTS=main.o Game.o Player.o Head_deck.o Deck.o Card.o
DEPENDS=${OBJECTS:.o=.d}
EXEC=hydra

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${DEPENDS}
