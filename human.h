#ifndef _HUMAN_H_
#define _HUMAN_H_


#include "player.h"



class Human : public Player {
	public: 
		void playTurn();
		Human(std::shared_ptr<Table> t, int id, char type);
};



#endif
