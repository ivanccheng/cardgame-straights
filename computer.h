#ifndef _COMPUTER_H_
#define _COMPUTER_H_

#include "player.h"

class Computer : public Player {
	public:
		Computer(std::shared_ptr<Table> t, int id, char type);
		void playTurn();
};


#endif
