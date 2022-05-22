#ifndef _PLAYER_H_
#define _PLAYER_H_


#include <vector> 
#include <string> 
#include <memory>

class Card;
class Table;


class Player {
	private:
		int score;
		std::vector<std::shared_ptr<Card>> discards;
		std::vector<std::shared_ptr<Card>> hand;
		std::shared_ptr<Table> table;
		int id;
		char type;
		
	public: 
		Player(std::shared_ptr<Table> t, int id, char type);

		virtual void playTurn() = 0; 

		std::vector<std::shared_ptr<Card>> getHand() const; 
		// returns a vector of cards that in current hand
		
		std::vector<std::shared_ptr<Card>> getDiscards() const;

		std::vector<std::shared_ptr<Card>> legalMoves() const;
	       	// returns a vector of legal moves based on the table
		
		void discard(Card c); 
		// Discards a Card from hand into the discard pile, modifies player

		void playCard(Card c);
	       	// Plays Card from hand into Table, modifies player and table
		
		void addCard(std::shared_ptr<Card> c); 
		// Used for dealing cards, Modifies Player

		void clearPiles(); 
		// Used when the round is over, Clears discard and hand, Modifies Player
		
		void updateScore(); 
		// Used when the round is over, updates player score based on discards
	
		int getScore() const;

		std::shared_ptr<Table> getTable() const;


		

		void setScore(int n);

		void setHand(std::vector<std::shared_ptr<Card>> c);

		void setDiscards(std::vector<std::shared_ptr<Card>> c);
		
		bool hasLegalMoves() const;	
			 		       			
		char getType() const;
};

std::ostream &operator<< (std::ostream &out, const Player &p);




#endif
