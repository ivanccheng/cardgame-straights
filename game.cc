#include "card.h"  
#include "computer.h"
#include "controller.h"
#include "deck.h"
#include "human.h" 
#include "player.h"
#include "table.h"

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <random>
#include <chrono>
#include <stdexcept>



int main(int argc, char *argv[]) {
	//code used from shuffle.cc
	unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
	if ( argc > 1 ) {
		try {
			seed = std::stoi( std::string{ argv[1] } );
		} catch( std::invalid_argument & e ) {
			std::cerr << e.what() << std::endl;
			return 1;
		} catch( std::out_of_range & e ) {
			std::cerr << e.what() << std::endl;
			return -1;
		} // catch
	} // if
	
	auto d = std::make_shared<Deck>(seed);
	auto game = std::make_shared<Controller>(d, seed);
	
	try {
		game->initGame();
	} catch (...) {
		std::cout << "Init Failed" << std::endl;
		return 2;
	}
	while (!(game->gameIsOver())) {
		std::cout << "A new round begins. It's Player" << game->getFirst() + 1 << "'s turn to play." << std::endl;
		while (!(game->roundIsOver())) {
			if (game->playTurn(game->getTurn()) == -1) {
				return 0;
			}
		}
		game->updateScores();
		game->initRound();
	}
	game->getWinners();
	return 0;
}
