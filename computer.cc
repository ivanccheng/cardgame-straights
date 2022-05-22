#include "computer.h"
#include "table.h"
#include "card.h"



Computer::Computer(std::shared_ptr<Table> t, int id, char type) : Player{t, id, type} {
}

void Computer::playTurn() {
	if (hasLegalMoves()) {
		playCard(*legalMoves().at(0));
	} else {
		discard(*getHand().at(0));
	}
}
