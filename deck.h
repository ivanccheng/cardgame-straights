#ifndef _DECK_H_
#define _DECK_H_

#include <memory>
#include <vector>
#include <random>

class Card;

class Deck {
	private: 
		std::vector<std::shared_ptr<Card>> cards;
		unsigned seed;
		std::shared_ptr<std::default_random_engine> rng;
	public:
		Deck(unsigned seed); // Initializes Deck, does not shuffle on creation
		void createDeck(); // Generates all the cards
		void shuffle(); // Shuffles Cards based on seed
		void setSeed(int s);
		int getSeed() const;
		std::shared_ptr<Card> getCard(int n) const;
};

std::ostream& operator<< (std::ostream& out, const Deck &d) ;

#endif

