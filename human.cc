#include "human.h"
#include "player.h"
#include "table.h"

#include <iostream>
#include <vector>
#include <string> 
#include <stdlib.h>

void Human::playTurn() {};

Human::Human(std::shared_ptr<Table> t, int id, char type) : Player{t, id, type} {
}







