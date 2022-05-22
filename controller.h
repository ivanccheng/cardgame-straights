#ifndef _CONTROLLER_H_
#define _CONTROLLER_H_

#include <vector>
#include <memory> 

class Deck;
class Player;
class Table;

class Controller { 
	private: 
		std::shared_ptr<Deck> deck;
		std::vector<std::shared_ptr<Player>> players;
		std::shared_ptr<Table> table;
		int turn;
		unsigned seed;
	public: 
		Controller(std::shared_ptr<Deck> deck, unsigned seed);
		//Creates a deck with the seed and stores the seed

		std::shared_ptr<Table> getTable() const;
		
		void dealCards();
		// Distrubutes cards to each player

		void initGame();

		void initRound();

		void firstPlayer();
		// update turn with the id of the first player

		int getFirst() const;
		// returns first player's turn

		int getTurn() const;

		bool gameIsOver() const;
		void nextPlayer();
		bool roundIsOver() const;
		int playTurn(int n);
		void updateScores();
		void getWinners();
		std::shared_ptr<Player> getPlayer(int n);
						
};

#endif
